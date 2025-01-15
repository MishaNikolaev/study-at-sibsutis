#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <graphics.h>

using namespace std;

const int NODE_RADIUS = 30;
const int VERTICAL_SPACING = 100;

struct vertex{
    vertex *L = NULL;
    vertex *R = NULL;
    short int balance = 0;
    int data;
};

bool addToAVL(vertex *&p, int data, bool &rost);

vertex *createAVL(int n) {
    vertex *root = NULL;
    int i = 0;
    bool rost;
    while (i < n) {
        int data = rand() % 100;

        if (addToAVL(root, data, rost))
            i++;
    }
    return root;
}

void rotateLL(vertex *&p){
    vertex *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R; 
    q->R = p;
    p=q;
}

void rotateRR(vertex *&p){
    vertex *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L; 
    q->L = p;
    p=q;
}

void rotateLR(vertex *&p){
    vertex *q = p->L;
    vertex *r = q->R;
    if(r->balance <0)
        p->balance = 1;
    else
        p->balance = 0;
    if(r->balance>0)
        q->balance = -1;
    else
        q->balance = 0;
    r->balance = 0;
    q->R = r->L;  
    p->L = r->R;
    r->L = q;
    r->R = p;
    p = r;
}

void rotateRL(vertex *&p){
    vertex *q = p->R;
    vertex *r = q->L;
    if(r->balance <0)
        p->balance = 1;
    else
        p->balance = 0;
    if(r->balance>0)
        q->balance = -1;
    else
        q->balance = 0;
    r->balance = 0;
    q->L = r->R;
    p->R = r->L;
    r->R = q;
    r->L = p;
    p = r;
}

bool addToAVL(vertex *&p, int data, bool &rost) {
    if (p == NULL) {
        p = new vertex;
        p->data = data;
        p->L = NULL;
        p->R = NULL;
        rost = true;
    } else if (p->data > data) {
        if (addToAVL(p->L, data, rost)) {
            if (rost) {
                if (p->balance > 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = -1;
                    rost = true;
                } else if ((p->L)->balance < 0) {
                    rotateLL(p);
                    rost = false;
                } else {
                    rotateLR(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    }

    else if (p->data < data) {
        if (addToAVL(p->R, data, rost)) {
            if (rost) {
                if (p->balance < 0) {
                    p->balance = 0;
                    rost = false;
                } else if (p->balance == 0) {
                    p->balance = 1;
                    rost = true;
                } else if ((p->R)->balance > 0) {
                    rotateRR(p);
                    rost = false;
                } else {
                    rotateRL(p);
                    rost = false;
                }
            }
        } else {
            return false;
        }
    } else
        return false;
    return true;
}


void outTree_LefttoRight(vertex* p, bool root = true) {
    static int counter = 0;
    if (root) {
        cout << endl << "Left to right: " << endl;
        counter = 0;
    }
    if (p != NULL) {
        outTree_LefttoRight(p->L, false);
        if (counter > 0 && counter % 10 == 0) {
            cout << endl;
        }
        cout << p->data << ", ";
        counter++;
        outTree_LefttoRight(p->R, false);
    }
}


int sizeTree(vertex* p, bool root) {
    if (p == NULL) return 0;
    return 1 + sizeTree(p->L, 0) + sizeTree(p->R, 0);
}

int checkSumTree(vertex* p, bool root) {
    if (p == NULL) return 0;
    return p->data + checkSumTree(p->L, 0) + checkSumTree(p->R, 0);
}

int summaLenghtofPaths(vertex* p, int depth) {
    if (p == NULL) return 0;
    return depth + summaLenghtofPaths(p->L, depth + 1) + summaLenghtofPaths(p->R, depth + 1);
}

int heightTree(vertex* p, bool root) {
    if (p == NULL) return 0;
    return 1 + max(heightTree(p->L, 0), heightTree(p->R, 0));
}

float averageHeightTree(vertex* p, bool root) {
    int size = sizeTree(p, 0);
    if (size) {
        return static_cast<float>(summaLenghtofPaths(p, 1)) / size;
    }
    return 0;
}

vertex* searchInTree(vertex* root,int key) {
    if(!root)
        return NULL;
    if(root->data==key) {
        return root;}
    else if(root->data>key) {
        return searchInTree(root->L,key);}
    else {
        return searchInTree(root->R,key);
    }
}

void FillRand(int *MyArray, int n) {
    bool *table = new bool[n]();
    for (int i = 0; i < n; i++) {
        int x;
        do {
            x = rand() % n;
        } while (table[x]);
        table[x] = true;
        MyArray[i] = x;
    }
    delete[] table;
}
vertex* ISDP(int L, int R, int *MyArray) {
    if (L > R) return NULL;
    int m = (L + R) / 2;
    vertex *p = new vertex;
    p->data = MyArray[m];
    p->L = ISDP(L, m - 1, MyArray);
    p->R = ISDP(m + 1, R, MyArray);
    return p;
}
void QuickSortV2(int MyArray[], int L, int R) {
    while (L < R) {
        int i = L, j = R;
        int x = MyArray[(L + R) / 2];
        while (i <= j) {
            while (MyArray[i] < x) i++;
            while (MyArray[j] > x) j--;
            if (i <= j) {
                swap(MyArray[i], MyArray[j]);
                i++;
                j--;
            }
        }
        if ((j - L) < (R - i)) {
            QuickSortV2(MyArray, L, j);
            L = i;
        } else {
            QuickSortV2(MyArray, i, R);
            R = j;
        }
    }
}
vertex* createISDP(int n) {
    int *MyArray = new int[n];
    FillRand(MyArray, n);
    QuickSortV2(MyArray, 0, n - 1);
    vertex* root = ISDP(0, n - 1, MyArray);
    delete[] MyArray;
    return root;
}


void drawNode(int x, int y, int data) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, NODE_RADIUS, NODE_RADIUS);

    setbkcolor(YELLOW);
    setcolor(BLACK);
    char buffer[4];
    sprintf(buffer, "%d", data);
    outtextxy(x - 5, y - 5, buffer);
}

void drawTree(vertex* root, int x, int y, int offset, int &minX) {
    if (root == NULL) return;

    minX = min(minX, x);
    drawNode(x, y, root->data);

    if (root->L) {
        int newX = x - offset;
        int newY = y + VERTICAL_SPACING;
        line(x, y, newX, newY);
        drawTree(root->L, newX, newY, offset / 2, minX);
    }

    if (root->R) {
        int newX = x + offset;
        int newY = y + VERTICAL_SPACING;
        line(x, y, newX, newY);
        drawTree(root->R, newX, newY, offset / 2, minX);
    }
}
void displayTreeGraphically(vertex* root) {
    int gd = DETECT, gm;

    initwindow(1920, 1080);

    setbkcolor(DARKGRAY);
    cleardevice();

    int screenWidth = 1920;
    int screenHeight = 1080;

    int startX = screenWidth / 2;
    int startY = 50;
    int minX = startX;

    drawTree(root, startX, startY, screenWidth / 4, minX);

    int currentOffsetX = 0;
    int currentOffsetY = 0;
    while (true) {
        char key = getch();
        if (key == 77) {  
            currentOffsetX -= 200;
        } else if (key == 75) {  
            currentOffsetX += 200;
        } else if (key == 72) {  
            currentOffsetY += 200;
        } else if (key == 80) { 
            currentOffsetY -= 200;
        } else if (key == 27) {  
            break;
        }

        setbkcolor(DARKGRAY);
        cleardevice();
        drawTree(root, startX + currentOffsetX, startY + currentOffsetY, screenWidth / 4, minX);
    }

    closegraph();
}

int main(){

    int n = 100;

    vertex *root = createAVL(n);
    vertex *root2 = createISDP(n);

    outTree_LefttoRight(root, 1);
    cout << endl << "______________________________________";
    cout << endl;

    cout << endl << "Size of tree: " << sizeTree(root, 1);
    cout << endl << "Height tree: " << heightTree(root, 1);
    cout << endl << "Summa lenght routes tree: " << summaLenghtofPaths(root, 1);
    cout << endl << "Average height tree: " << averageHeightTree(root, 1);
    cout << endl << "Control sum tree: " << checkSumTree(root, 1);;


    cout << endl << "_______________________________________________________________________";
    cout << endl << "|  n=100    |  size      |  sum        | height   |    average height |";
    cout << endl << "|___________|____________|_____________|__________|___________________|";
    cout << endl << "| ISDP      | " << sizeTree(root2,0) << "        | " << checkSumTree(root2,0) << "        | " << heightTree(root2,0) << "        | " << averageHeightTree(root2,0) << "               |";
    cout << endl << "| AVL       | " << sizeTree(root,0) << "        | " << checkSumTree(root,0) << "        | " << heightTree(root,0) << "        | " << averageHeightTree(root,0) << "              |";
    cout << endl << "_______________________________________________________________________" <<endl;
    
    displayTreeGraphically(root);
    
    return 0;
}
