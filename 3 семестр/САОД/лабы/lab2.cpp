#include <iostream>
#include <ctime>
#include <cstdlib>
#include <graphics.h>  
#include <algorithm>

using namespace std;

const int MAX_RAND = 100;
const int VERTICAL_SPACING = 100; 
const int NODE_RADIUS = 15;

struct vertex {
    int data;
    vertex* L = NULL;
    vertex* R = NULL;
};

vertex* ISDP(int L, int R, int *MyArray) {
    if (L > R) return NULL;
    int m = (L + R) / 2;
    vertex *p = new vertex;
    p->data = MyArray[m];
    p->L = ISDP(L, m - 1, MyArray);
    p->R = ISDP(m + 1, R, MyArray);
    return p;
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

int sizeTree(vertex* p) {
    if (p == NULL) return 0;
    return 1 + sizeTree(p->L) + sizeTree(p->R);
}

int checkSumTree(vertex* p) {
    if (p == NULL) return 0;
    return p->data + checkSumTree(p->L) + checkSumTree(p->R);
}

int summaLenghtofPaths(vertex* p, int depth) {
    if (p == NULL) return 0;
    return depth + summaLenghtofPaths(p->L, depth + 1) + summaLenghtofPaths(p->R, depth + 1);
}

int heightTree(vertex* p) {
    if (p == NULL) return 0;
    return 1 + max(heightTree(p->L), heightTree(p->R));
}

float averageHeightTree(vertex* p) {
    int size = sizeTree(p);
    if (size) {
        return static_cast<float>(summaLenghtofPaths(p, 1)) / size;
    }
    return 0;
}

bool addRST_DK(vertex *&p, int data) {
    vertex **q = &p;
    while (*q != NULL) {
        if (data < (*q)->data)
            q = &((*q)->L);
        else if (data > (*q)->data)
            q = &((*q)->R);
        else {
            return false;
        }
    }
    *q = new vertex;
    (*q)->data = data;
    return true;
}

vertex* createRST_DK(int *dataArray, int n) {
    vertex *root = NULL;
    for (int i = 0; i < n; i++) {
        addRST_DK(root, dataArray[i]);
    }
    return root;
}

bool addRST_R(vertex *&p, int data) {
    if (p == NULL) {
        p = new vertex;
        p->data = data;
        return true;
    }
    if (data < p->data)
        return addRST_R(p->L, data);
    if (data > p->data)
        return addRST_R(p->R, data);
    return false;
}

vertex* createRST_R(int *dataArray, int n) {
    vertex *root = NULL;
    for (int i = 0; i < n; i++) {
        addRST_R(root, dataArray[i]);
    }
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

int main() {
    srand(time(NULL));
    int n = 10, key;
    int dataArray[n];

    FillRand(dataArray, n);

    vertex *root1 = createRST_DK(dataArray, n);
    cout << endl;
    cout << "Random tree of search (double kosvennost) :" << endl;
    outTree_LefttoRight(root1, true);
    cout << endl << "__________________________________________" << endl;

    vertex *root2 = createRST_R(dataArray, n);
    cout << "Random tree of search (recursive) :" << endl;
    outTree_LefttoRight(root2, true);
    cout << endl << "__________________________________________" << endl;

    vertex *root3 = createISDP(n);

    cout << endl << "_______________________________________________________________________";
    cout << endl << "|  n=100    |  size      |  sum        | height   |    average height |";
    cout << endl << "|___________|____________|_____________|__________|___________________|";
    cout << endl << "| ISDP      | " << sizeTree(root3) << "        | " << checkSumTree(root3) << "        | " << heightTree(root3) << "        | " << averageHeightTree(root3) << "               |";
    cout << endl << "| SDP1      | " << sizeTree(root1) << "        | " << checkSumTree(root1) << "        | " << heightTree(root1) << "       | " << averageHeightTree(root1) << "              |";
    cout << endl << "| SDP2      | " << sizeTree(root2) << "        | " << checkSumTree(root2) << "        | " << heightTree(root2) << "       | " << averageHeightTree(root2) << "              |";
    cout << endl << "_______________________________________________________________________" <<endl;
    
    cout << "Search in SDP:" << endl;
    cin >> key;
    if (searchInTree(root1,key)) {
		cout << "element was found "<<searchInTree(root1,key)->data;
	}
	else {
		cout << "element wasn't found";
	}

    displayTreeGraphically(root1);
    return 0;
}
