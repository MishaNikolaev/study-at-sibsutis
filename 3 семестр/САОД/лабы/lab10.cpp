#include <iostream>
#include <string>
#include <cmath>
#include <fstream>
#include <iomanip>
#include <locale>
#include <codecvt>
#include <cstdio>  
#include <cstdlib> 
#include <SFML/Graphics.hpp>


using namespace std;
using namespace sf;

const int num = 65536;

struct Symbol {
    wchar_t ch = 0;
    float chance = 0;
};

struct codeFano
{
    wchar_t ch = 0;
    float Pi = 0;
    unsigned short int Li = 0;
    char* word = nullptr;
};

struct Tree {

    wchar_t ch;
    float prob = 0;
    Tree* left = nullptr;
    Tree* right = nullptr;
};


void quickSortV2(Symbol*& A, int R, int L, unsigned short int field, bool reverse) {
    while (L < R) {
        float x;
        if (field == 0)
            x = A[L].ch;
        else if (field == 1)
            x = A[L].chance;

        int i = L;
        int j = R;
        while (i <= j) {
            if (field == 0) {
                if (reverse) {
                    while (A[i].ch > x)
                        i++;
                    while (A[j].ch < x)
                        j--;
                }
                else {
                    while (A[i].ch < x)
                        i++;
                    while (A[j].ch > x)
                        j--;
                }
            }
            else if (field == 1) {
                if (reverse) {
                    while (A[i].chance > x)
                        i++;
                    while (A[j].chance < x)
                        j--;
                }
                else {
                    while (A[i].chance < x)
                        i++;
                    while (A[j].chance > x)
                        j--;
                }
            }
            if (i <= j) {
                Symbol temp = A[i];
                A[i] = A[j];
                A[j] = temp;
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            quickSortV2(A, R, i, field, reverse);
            R = j;
        }
        else {
            quickSortV2(A, j, L, field, reverse);
            L = i;
        }
    }
}
int med(codeFano* fano, int borderL, int borderR) {

    float SumL = 0;
    for (int i = borderL; i < borderR; i++) {
        SumL = SumL + fano[i].Pi;
    }
    float SumR = fano[borderR].Pi;
    int m = borderR;
    while (SumL >= SumR) {
        m = m - 1;
        SumL = SumL - fano[m].Pi;
        SumR = SumR + fano[m].Pi;
    }
    return m;
}

void FanoCode(codeFano*& fano, int borderL, int borderR, int k) {

    if (borderL < borderR) {
        k = k + 1;
        int m = med(fano, borderL, borderR);
        for (int i = borderL; i <= borderR; i++) {
            if (fano[i].word != nullptr) {
                char* temp = new char[k];
                for (int j = 0; j < k - 1; j++)
                    temp[j] = fano[i].word[j];
                delete[] fano[i].word;
                fano[i].word = temp;
            }
            else {
                fano[i].word = new char[k];
            }
            if (i <= m) {
                fano[i].word[k - 1] = '0';
            }
            else {
                fano[i].word[k - 1] = '1';
            }
            fano[i].Li = fano[i].Li + 1;
        }
        FanoCode(fano, borderL, m, k);
        FanoCode(fano, m + 1, borderR, k);
    }

}

int A2mediana(codeFano* fano, int borderL, int borderR) {
    if (borderL > borderR) return -1;

    float totalProbability = 0;
    for (int i = borderL; i <= borderR; i++) {
        totalProbability += fano[i].Pi;
    }

    float halfTotal = totalProbability / 2;
    float cumulative = 0;
    for (int i = borderL; i <= borderR; i++) {
        cumulative += fano[i].Pi;
        if (cumulative >= halfTotal) {
            return i;
        }
    }

    return borderR;
}

void FanoCodeMediana(codeFano*& fano, int borderL, int borderR, int k) {
    if (borderL < borderR) {
        k++;
        int m = A2mediana(fano, borderL, borderR);
        for (int i = borderL; i <= borderR; i++) {
            if (fano[i].word != nullptr) {
                char* temp = new char[k];
                for (int j = 0; j < k - 1; j++)
                    temp[j] = fano[i].word[j];
                delete[] fano[i].word;
                fano[i].word = temp;
            }
            else {
                fano[i].word = new char[k];
            }

            if (i <= m) {
                fano[i].word[k - 1] = '0';
                fano[i].Li++;
            }
            else {
                fano[i].word[k - 1] = '1';
                fano[i].Li++;
            }
        }

        FanoCodeMediana(fano, borderL, m, k);
        FanoCodeMediana(fano, m + 1, borderR, k);
    }
}

codeFano* FanoCode(Symbol* chanceSymbols, short int numSymbols) {
    codeFano* fano = new codeFano[numSymbols];
    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);
    for (int i = 0; i < numSymbols; i++) {
        fano[i].ch = chanceSymbols[i].ch;
        fano[i].Pi = chanceSymbols[i].chance;
    }

    FanoCode(fano, 0, numSymbols - 1, 0);

    return fano;
}

codeFano* FanoCodeA2(Symbol* chanceSymbols, short int numSymbols) {
    codeFano* fano = new codeFano[numSymbols];
    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);

    for (int i = 0; i < numSymbols; i++) {
        fano[i].ch = chanceSymbols[i].ch;
        fano[i].Pi = chanceSymbols[i].chance;
    }
    FanoCodeMediana(fano, 0, numSymbols - 1, 0);
    return fano;
}


float calEntropy(Symbol* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += (A[i].chance * log2(A[i].chance));
    }
    return -result;
}

float calAVGLength(codeFano* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i].Li * A[i].Pi;
    }
    return result;
}



void printFanoCode(codeFano* C, int n) {
    wcout << L"\n??? ????:" << endl;
    wcout << L"---------------------------------------------------------" << endl;
    wcout << L"| ?????? | ??????????? | ????? | ??????? ?????           |" << endl;
    wcout << L"---------------------------------------------------------" << endl;
    for (int i = 0; i < n; i++) {
        wcout << L"| " << setw(6) << C[i].ch
            << L" | " << setw(10) << fixed << setprecision(4) << C[i].Pi
            << L" | " << setw(6) << C[i].Li
            << L" | ";
        for (int j = 0; j < C[i].Li; j++)
            wcout << C[i].word[j];
        wcout << setw(20 - C[i].Li) << L" |" << endl;
    }
    wcout << L"---------------------------------------------------------" << endl;
}

float checkKraft(codeFano* C, int n) {
    float kraftSum = 0;
    for (int i = 0; i < n; i++) {
        kraftSum += pow(2, -C[i].Li);
    }
    return kraftSum;
}

void printSummary(float entropy, float avgLength, float kraftCheck) {
    float redundancy = avgLength - entropy;
    wcout << L"\n??????????:" << endl;
    wcout << L"---------------------------------------------------------------------------------------------------------------" << endl;
    wcout << L"| ??????????? ??????   | ???????? ????????? ?????? | ??????? ????? ???????? ????? | ???????????? ???? ???? |" << endl;
    wcout << L"---------------------------------------------------------------------------------------------------------------" << endl;
    wcout << L"| " << setw(20) << kraftCheck << L" | "
        << setw(25) << fixed << setprecision(4) << entropy << L" | "
        << setw(27) << fixed << setprecision(4) << avgLength << L" | "
        << setw(25) << fixed << setprecision(4) << redundancy << L" |" << endl;
    wcout << L"---------------------------------------------------------------------------------------------------------------" << endl;
}

void drawTree(RenderWindow& window, Tree* root, float x, float y, float horizontalSpacing, Font& font, const string& path = "") {
    if (root == nullptr) return;

    float verticalSpacing = 70;
    float additionalSpacing = 30;
    if (root->left) {
        Vertex line[] = {
            Vertex(Vector2f(x, y), Color::Black),
            Vertex(Vector2f(x - horizontalSpacing, y + verticalSpacing), Color::Black)
        };
        window.draw(line, 2, Lines);

        drawTree(window, root->left, x - (horizontalSpacing + additionalSpacing), y + verticalSpacing, horizontalSpacing / 2, font, path + "0");
    }
    if (root->right) {
        Vertex line[] = {
            Vertex(Vector2f(x, y), Color::Black),
            Vertex(Vector2f(x + horizontalSpacing, y + verticalSpacing), Color::Black)
        };
        window.draw(line, 2, Lines);

        drawTree(window, root->right, x + (horizontalSpacing + additionalSpacing), y + verticalSpacing, horizontalSpacing / 2, font, path + "1");
    }

    CircleShape circle(19);
    circle.setPosition(x - circle.getRadius(), y - circle.getRadius());
    circle.setOutlineThickness(1);
    circle.setOutlineColor(Color::Red);
    window.draw(circle);

    if (root->ch != L'\0') {
        Text symbol(wstring(1, root->ch), font, 18);
        symbol.setFillColor(Color::Black);
        symbol.setPosition(x - symbol.getGlobalBounds().width / 2, y - symbol.getGlobalBounds().height / 2);
        window.draw(symbol);
    }

    if (!path.empty()) {
        Text codeText(path, font, 16);
        codeText.setFillColor(Color::Black);
        codeText.setPosition(x - codeText.getGlobalBounds().width / 2, y - circle.getRadius() - 20);
        window.draw(codeText);
    }
}



Tree* buildFanoTree(codeFano* codes, int n) {
    Tree* root = new Tree{ L'\0', 0 };

    for (int i = 0; i < n; ++i) {
        Tree* p = root;
        for (int j = 0; j < codes[i].Li; ++j) {
            if (codes[i].word[j] == '0') {
                if (!p->left) p->left = new Tree{ L'\0', 0 };
                p = p->left;
            }
            else {
                if (!p->right) p->right = new Tree{ L'\0', 0 };
                p = p->right;
            }
        }
        p->ch = codes[i].ch;
        p->prob = codes[i].Pi;
    }
    return root;
}

int main() {
    locale::global(locale("ru_RU.UTF-8"));
    wifstream file("C:/Users/HUAWEI/Downloads/test.txt");
    file.imbue(locale("ru_RU.UTF-8"));
    RenderWindow window(VideoMode(1900, 800), "Fano Coding Tree");
    Font font;
    font.loadFromFile("arial.ttf");

    int n = 0;
    int nUnique = 0;
    unsigned int words[num] = { 0 };

    wchar_t ch;
    wcout << L"\n??????? ?? ????? test.txt:" << endl;
    while (file.get(ch)) {
        wcout << ch;
        n++;
        words[(int)ch]++;
    }
    wcout << endl;

    for (int i = 0; i < num; i++) {
        if (words[i] != 0)
            nUnique++;
    }

    wcout << L"\n???-?? ????????: " << n << "\n" << L"???-?? ?????????? ????????: " << nUnique << "\n";
    file.close();

    Symbol* Symbols = new Symbol[nUnique];
    int temp = 0;
    for (int i = 0; i < num; i++) {
        if (words[i] != 0) {
            Symbols[temp].ch = (wchar_t)i;
            Symbols[temp].chance = (float)words[i] / n;
            temp++;
        }
    }

    float entropy = calEntropy(Symbols, nUnique);
    codeFano* C = FanoCode(Symbols, nUnique);
    float AVGLfano = calAVGLength(C, nUnique);

    printFanoCode(C, nUnique);

    float kraftCheck = checkKraft(C, nUnique);
    printSummary(entropy, AVGLfano, kraftCheck);

    locale::global(locale("ru_RU.UTF-8"));
    wifstream file2("C:/Users/HUAWEI/Downloads/test.txt");
    file2.imbue(locale("ru_RU.UTF-8"));
    n = 0;
    nUnique = 0;
    for (int i = 0; i < num; i++) {
        words[i] = 0;
    }

    wcout << L"\n??????? ??? ???? ???? ? ???????? ?? ????????? A2" << endl;
    while (file2.get(ch)) {
        n++;
        words[(int)ch]++;
    }
    for (int i = 0; i < num; i++) {
        if (words[i] != 0)
            nUnique++;
    }
    file2.close();

    delete[] Symbols;
    Symbols = new Symbol[nUnique];
    temp = 0;
    for (int i = 0; i < num; i++) {
        if (words[i] != 0) {
            Symbols[temp].ch = (wchar_t)i;
            Symbols[temp].chance = (float)words[i] / n;
            temp++;
        }
    }

    entropy = calEntropy(Symbols, nUnique);
    codeFano* CA2 = FanoCodeA2(Symbols, nUnique);
    float AVGLfanoA2 = calAVGLength(CA2, nUnique);

    printFanoCode(CA2, nUnique);
    float kraftCheckA2 = checkKraft(CA2, nUnique);
    printSummary(entropy, AVGLfanoA2, kraftCheckA2);

    float offsetX = 0;
    float offsetY = 0;

    Tree* root = buildFanoTree(C, nUnique);

    while (window.isOpen()) {
        Event event;
        while (window.pollEvent(event)) {
            if (event.type == Event::Closed)
                window.close();
            if (event.type == Event::KeyPressed) {
                if (event.key.code == Keyboard::Up) {
                    offsetY -= 10;
                }
                else if (event.key.code == Keyboard::Down) {
                    offsetY += 10;
                }
                else if (event.key.code == Keyboard::Left) {
                    offsetX -= 10;
                }
                else if (event.key.code == Keyboard::Right) {
                    offsetX += 10;
                }
            }
        }

        window.clear(Color::White);
        drawTree(window, root, 950 + offsetX, 25 + offsetY, 470, font);

        window.display();
    }


    delete[] Symbols;
    for (int i = 0; i < nUnique; i++) {
        delete[] C[i].word;
        delete[] CA2[i].word;
    }
    delete[] C;
    delete[] CA2;
    delete root;

    return 0;
}
