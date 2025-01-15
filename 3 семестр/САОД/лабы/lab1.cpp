#include <iostream>
#include <iomanip>
#include <ctime>
#include <cstdlib>
#include <graphics.h>  
#include <cmath>


using namespace std;

const int NODE_RADIUS = 15;
const int HORIZONTAL_SPACING = 100;  
const int VERTICAL_SPACING = 110;   

struct vertex {
    int data;
    vertex* L = NULL;
    vertex* R = NULL;
};

vertex* ISDP(int L, int R, int *MyArray) {
    if (L > R) return NULL;
    else {
        int m = ((L + R + 1) / 2);
        vertex *p = new vertex;
        p->data = MyArray[m];
        p->L = ISDP(L, m - 1, MyArray);
        p->R = ISDP(m + 1, R, MyArray);
        return p;
    }
}

void FillRand(int *MyArray, int n) {
    bool *table = new bool[n](); 
    int x;
    for (int i = 0; i < n; i++) {
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
                int temp = MyArray[i];
                MyArray[i] = MyArray[j];
                MyArray[j] = temp;
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
    cout<<5;
    QuickSortV2(MyArray, 0, n - 1);
    return ISDP(0, n - 1, MyArray);
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
    initwindow(1920, 1080, "ISDP Tree");
    
    setbkcolor(DARKGRAY); 
    cleardevice();

    int screenWidth = getmaxx();  
    int screenHeight = getmaxy();

    int startX = screenWidth / 2;
    int startY = 50;
    int minX = startX;
    
    drawTree(root, startX, startY, screenWidth / 4, minX);

    int currentOffsetX = 0;
    while (true) {
        char key = getch();
        if (key == KEY_RIGHT) {
            currentOffsetX -= 100; 
        } else if (key == KEY_LEFT) {
            currentOffsetX += 100;  
        } else if (key == 27) {  
            break;
        }
        
        setbkcolor(DARKGRAY); 
        cleardevice();
        drawTree(root, startX + currentOffsetX, startY, screenWidth / 4, minX);
    }

    closegraph();
}


void outTree_LefttoRight(vertex* p, bool root) {
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
        return float(summaLenghtofPaths(p, 1)) / size;
    } else {
        return 0;
    }
}

int main() {
    srand(time(NULL));
    int n = 1000,key;

    vertex *root = createISDP(n);
    outTree_LefttoRight(root, 1);
    cout << endl << "_____________________";
    cout << endl << "Size of tree: " << sizeTree(root);
    cout << endl << "Height tree: " << heightTree(root);
    cout << endl << "Summa lenght routes tree: " << summaLenghtofPaths(root, 1);
    cout << endl << "Average height tree: " << fixed << setprecision(2) << averageHeightTree(root);
    cout << endl << "Control sum tree: " << checkSumTree(root);
	cout << endl << "Input element to search: ";
	cin >> key;
	cout << endl;
	if (searchInTree(root,key)) {
		cout << "element was found "<<searchInTree(root,key)->data;
	}
	else {
		cout << "element wasn't found";
	}
    displayTreeGraphically(root);

    return 0;
}
