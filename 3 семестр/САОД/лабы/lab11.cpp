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

struct Shannon {
    wchar_t ch = 0;
    float P = 0;
    float Q = 0;
    unsigned short int L = 0;
    char* word = nullptr;
};

struct codeHuffman
{
    wchar_t ch = 0;
    float Pi = 0;
    unsigned short int Li = 0;
    char* word = nullptr;
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


unsigned short int Up(float*& Pi, unsigned int n, float x) {
    int j = 0;
    for (int i = n - 2; i > 0; i--) {
        if (Pi[i - 1] < x) {
            Pi[i] = Pi[i - 1];
        }
        else {
            j = i;
            break;
        }
    }
    Pi[j] = x;
    return j;
}

void Down(codeHuffman*& huffman, int n, int j) {
    char* S = new char[huffman[j].Li + 1];
    for (int i = 0; i < huffman[j].Li; i++)
        S[i] = huffman[j].word[i];

    int L = huffman[j].Li;

    for (int i = j; i <= n - 2; i++) {
        delete[] huffman[i].word;
        huffman[i].word = new char[huffman[i + 1].Li];
        for (int t = 0; t < huffman[i + 1].Li; t++)
            huffman[i].word[t] = huffman[i + 1].word[t];
        huffman[i].Li = huffman[i + 1].Li;
    }

    delete[] huffman[n - 1].word;
    delete[] huffman[n].word;

    huffman[n - 1].Li = L + 1;
    huffman[n].Li = L + 1;
    huffman[n - 1].word = new char[huffman[n - 1].Li];
    huffman[n].word = new char[huffman[n].Li];

    for (int i = 0; i < L; i++)
        huffman[n - 1].word[i] = huffman[n].word[i] = S[i];

    huffman[n - 1].word[L] = '0';
    huffman[n].word[L] = '1';
}
void HuffmanCode(codeHuffman*& huffman, float*& Pi, int n) {
    if (n == 2) {
        huffman[0].word = new char[1];
        huffman[0].word[0] = '0';
        huffman[0].Li = 1;
        huffman[1].word = new char[1];
        huffman[1].word[0] = '1';
        huffman[1].Li = 1;
    }
    else {
        float q = Pi[n - 2] + Pi[n - 1];
        int j = Up(Pi, n, q);
        HuffmanCode(huffman, Pi, n - 1);
        Down(huffman, n - 1, j);
    }
}

codeHuffman* HuffmanCode(Symbol* chanceSymbols, short int numSymbols) {
    codeHuffman* huffman = new codeHuffman[numSymbols];
    float* Pi = new float[numSymbols];

    quickSortV2(chanceSymbols, numSymbols - 1, 0, 1, 1);

    for (int i = 0; i < numSymbols; i++) {
        huffman[i].ch = chanceSymbols[i].ch;
        huffman[i].Pi = Pi[i] = chanceSymbols[i].chance;
    }

    HuffmanCode(huffman, Pi, numSymbols);

    return huffman;
}


Shannon* ShannonCode(Symbol* Symbols, int n) {
    quickSortV2(Symbols, n - 1, 0, 1, true);
    Shannon* C = new Shannon[n];

    C[0].ch = Symbols[0].ch;
    C[0].P = Symbols[0].chance;
    C[0].L = ceil(-log2(C[0].P));
    C[0].Q = 0;

    for (int i = 1; i < n; i++) {
        C[i].ch = Symbols[i].ch;
        C[i].P = Symbols[i].chance;
        C[i].L = ceil(-log2(C[i].P));
        C[i].Q = C[i - 1].Q + C[i - 1].P;
    }

    for (int i = 0; i < n; i++) {
        float Qtemp = C[i].Q;
        C[i].word = new char[C[i].L];
        for (int j = 0; j < C[i].L; j++) {
            Qtemp = Qtemp * 2;
            C[i].word[j] = (char)(floor(Qtemp) + 48);
            if (Qtemp >= 1) Qtemp = Qtemp - 1;
        }
    }

    return C;
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

float calEntropy(Symbol* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += (A[i].chance * log2(A[i].chance));
    }
    return -result;
}

float calAVGLength(codeHuffman* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i].Li * A[i].Pi;
    }
    return result;
}

float calAVGLength(Shannon* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i].L * A[i].P;
    }
    return result;
}

float calAVGLength(codeFano* A, int n) {
    float result = 0;
    for (int i = 0; i < n; i++) {
        result += A[i].Li * A[i].Pi;
    }
    return result;
}



void printHuffmanCode(codeHuffman* C, int n) {
    wcout << L"\n??? ????????:" << endl;
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

float checkKraft(codeHuffman* C, int n) {
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
    wcout << L"| ??????????? ??????   | ???????? ????????? ?????? |??????? ????? ???????? ????? | ???????????? ???? ???????? |" << endl;
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
        Text symbol(String(wstring(1, root->ch)), font, 16);
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




Tree* buildHuffmanTree(codeHuffman* codes, int n) {
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

wstring decode(Tree* root, const wstring& encoded) {
    wstring decoded;
    Tree* p = root;

    for (auto bit : encoded) {
        if (bit == L'0' && p->left) {
            p = p->left;
        }
        else if (bit == L'1' && p->right) {
            p = p->right;
        }

        if (!p->left && !p->right) {
            decoded += p->ch;
            p = root;
        }
    }

    return decoded;
}

int main() {

    locale::global(locale("ru_RU.UTF-8"));
    wifstream file("C:/Users/HUAWEI/Downloads/test.txt");
    file.imbue(locale("ru_RU.UTF-8"));
    RenderWindow window(VideoMode(1900, 800), "Huffman Coding Tree");
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
    codeHuffman* C = HuffmanCode(Symbols, nUnique);
    float AVGHuffman = calAVGLength(C, nUnique);

    Shannon* C1 = ShannonCode(Symbols, nUnique);
    float AVGShannon = calAVGLength(C1, nUnique);

    codeFano* C2 = FanoCode(Symbols, nUnique);
    float AVGFano = calAVGLength(C2, nUnique);

    printHuffmanCode(C, nUnique);

    float kraftCheck = checkKraft(C, nUnique);
    printSummary(entropy, AVGHuffman, kraftCheck);

    wcout << L"\n??????? ??????? ????? ???????? ?????:" << endl;
    wcout << L"--------------------------------------------" << endl;
    wcout << L"| ?????     | ??????? ????? ???????? ????? |" << endl;
    wcout << L"--------------------------------------------" << endl;
    wcout << L"| ???????   | " << fixed << setprecision(4) << AVGHuffman << L"                       |" << endl;
    wcout << L"| ????      | " << fixed << setprecision(4) << AVGFano << L"                       |" << endl;
    wcout << L"| ??????    | " << fixed << setprecision(4) << AVGShannon    << L"                       |" << endl;
    wcout << L"--------------------------------------------" << endl;

    wifstream file1("C:/Users/HUAWEI/Downloads/file1.txt");
    file1.imbue(locale("ru_RU.UTF-8"));
    wcout << L"??????? ????? ?? ????? file1.txt" << endl;
    int encodedLength = 0;
    int originalLength = 0;
    wstring encodedSequence;

    wcout << L"\n??????? ?? ????? file1.txt:" << endl;


    while (file1.get(ch)) {
        for (int i = 0; i < nUnique; i++) {
            if (C[i].ch == ch) {
                for (int j = 0; j < C[i].Li; j++) {
                    wcout << C[i].word[j];
                    encodedSequence += C[i].word[j];
                }
                wcout << L" ";
                encodedLength += C[i].Li;
                originalLength += 8;
                break;
            }
        }
    }
    file1.close();

    float compressionRatio = encodedLength / (float)originalLength;


    wcout << L"\n\n????? ?????????????? ??????????????????: " << encodedLength;
    wcout << L"\n???????? ????? ?????????????????? (? ?????): " << originalLength;
    wcout << L"\n??????????? ?????? ??????: " << compressionRatio << endl;

    float offsetX = 0;
    float offsetY = 0;

    Tree* huffmanTree = buildHuffmanTree(C, nUnique);

    wstring decodedSequence = decode(huffmanTree, encodedSequence);
    wcout << L"\n?????????????? ??????????????????: " << decodedSequence << endl;
    file1.imbue(locale("ru_RU.UTF-8"));
    int ind = 0;
    bool correct = true;
    while (file1.get(ch)) {
        if (decodedSequence[ind] != ch) {
            correct = false;
            break;
        }
        ind++;
    }
    if (correct) {
        cout << "THIS IS CORRECT!!! YEEAAAHH" << endl;
    }
    else {
        cout << "not right :(" << endl;
    }
    file1.close();
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
        drawTree(window, huffmanTree, 950 + offsetX, 25 + offsetY, 470, font);

        window.display();
    }

    delete[] Symbols;
    for (int i = 0; i < nUnique; i++) {
        delete[] C[i].word;
    }
    delete[] C;



    return 0;
}
