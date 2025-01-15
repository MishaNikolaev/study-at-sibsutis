#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <graphics.h>

using namespace std;

const int NODE_RADIUS = 30;
const int VERTICAL_SPACING = 100;
const int HORIZONTAL_SPACING = 50;

struct vertex{			
    vertex *L = NULL;
    vertex *R = NULL;
    short int balance = 0;
    int data;
};

struct vertexAVL{
    vertexAVL *L = NULL;
    vertexAVL *R = NULL;
    short int balance = 0;
    int data;
};
 
 
 bool AddToDBD(vertex *& p, int data , bool &VR,bool &HR){
  if (p == NULL){
    p = new vertex;
    p->data = data;
    p->L = p->R = NULL;
    p->balance = false;
    VR = true;
  }
  else if (p->data > data){
    if(AddToDBD(p->L, data, VR, HR)){
      if (VR){
        if (!p->balance){
          vertex * q = p->L;
          p->L = q->R;
          q->R = p;
          p = q;
          q->balance = true;
          VR = false;
          HR = true;
        }
        else{
          p->balance = false;
          VR = true;
          HR = false;
        }
      }
      else
        HR = false;
    }
    else 
      return false;
  }
  else if (p->data < data)
  {
    if(AddToDBD(p->R, data, VR, HR)){
      if (VR){
        p->balance = true;
        HR = true;
        VR = false;
      }
      else if (HR)
      {
        if (p->balance){
          vertex * q = p->R;
          p->balance = false;
          q->balance = false;
          p->R = q->L;
          q->L = p;
          p = q;
          VR = true;
          HR = false;
        }
        else
          HR = false;
      }
    }
    else 
      return false;
  }
  else 
    return false;
  return true;
}

vertex *createDBD(int n, bool &VR, bool &HR, bool log) {
  vertex *root = NULL;
  int i = 0;
  while (i < n) {
    int data = rand() % n;
    VR=1;
    HR=1;
    if (AddToDBD(root, data, VR, HR))
      i++;
  }
  return root;
}


void outTree_LefttoRight(vertex* p, bool root = true) {
    static int counter = 0;
    if (root) {
        cout << endl << "LR: " << endl;
        counter = 0;
    }
    if (p != NULL) {
        outTree_LefttoRight(p->L, false);
        if (counter > 0 && counter % 25 == 0) {
            cout << endl;
        }
        cout << p->data << ", ";
        counter++;
        outTree_LefttoRight(p->R, false);
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


bool addToAVL(vertexAVL *&p, int data, bool &rost);

vertexAVL *createAVL(int n) {
    vertexAVL *rootAVL = NULL;
    int i = 0;
    bool rost;
    while (i < n) {
        int data = rand() % n;

        if (addToAVL(rootAVL, data, rost))
            i++;
    }
    return rootAVL;
}

void rotateLL(vertexAVL *&p){
    vertexAVL *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R; 
    q->R = p;
    p=q;
}

void rotateRR(vertexAVL *&p){
    vertexAVL *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L; 
    q->L = p;
    p=q;
}

void rotateLR(vertexAVL *&p){
    vertexAVL *q = p->L;
    vertexAVL *r = q->R;
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

void rotateRL(vertexAVL *&p){
    vertexAVL *q = p->R;
    vertexAVL *r = q->L;
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

bool addToAVL(vertexAVL *&p, int data, bool &rost) {
    if (p == NULL) {
        p = new vertexAVL;
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

int sizeTree(vertexAVL* p, bool root) {
    if (p == NULL) return 0;
    return 1 + sizeTree(p->L, 0) + sizeTree(p->R, 0);
}

int checkSumTree(vertexAVL* p, bool root) {
    if (p == NULL) return 0;
    return p->data + checkSumTree(p->L, 0) + checkSumTree(p->R, 0);
}

int summaLenghtofPaths(vertexAVL* p, int depth) {
    if (p == NULL) return 0;
    return depth + summaLenghtofPaths(p->L, depth + 1) + summaLenghtofPaths(p->R, depth + 1);
}

int heightTree(vertexAVL* p, bool root) {
    if (p == NULL) return 0;
    return 1 + max(heightTree(p->L, 0), heightTree(p->R, 0));
}

float averageHeightTree(vertexAVL* p, bool root) {
    int size = sizeTree(p, 0);
    if (size) {
        return static_cast<float>(summaLenghtofPaths(p, 1)) / size;
    }
    return 0;
}

int countLevelsDBD(vertex *p) {
	if(!p)
		return 0;
	else {
        return 1 + countLevelsDBD(p->L);
    }
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
    	if (root->balance==1){
    		newY=y;
    		newX=x+HORIZONTAL_SPACING;
		}
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
    
    int startX = screenWidth /4;
    int startY = 50;
    int minX = startX;

    drawTree(root, startX, startY, screenWidth / 8, minX);
	
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
        drawTree(root, startX + currentOffsetX, startY + currentOffsetY, screenWidth / 8, minX);
    }

    closegraph();
}

int main(){
	srand(time(NULL));
	int n = 10;
	bool HR= true;
	bool VR= true; 
	vertexAVL *rootAVL  = createAVL(n);
	vertex *rootDBD = createDBD(n, VR, HR, 0);
	outTree_LefttoRight(rootDBD, 1);
	cout << endl;
	cout << "------------------------------------------------------------------------------------------------------" <<endl;
	cout << endl << "_______________________________________________________________________";
    cout << endl << "|  n=100    |  size      |  sum        | height   |    average height |";
    cout << endl << "|___________|____________|_____________|__________|___________________|";
    cout << endl << "| AVL       | " << sizeTree(rootAVL,0) << "        | " << checkSumTree(rootAVL,0) << "        | " << heightTree(rootAVL,0) << "        | " << averageHeightTree(rootAVL,0) << "              |";
    cout << endl << "| DBD       | " << sizeTree(rootDBD,0) << "        | " << checkSumTree(rootDBD,0) << "        | " << heightTree(rootDBD,0) << "        | " << averageHeightTree(rootDBD,0) << "              |";
    cout << endl << "_______________________________________________________________________" <<endl;
    cout << endl;
    cout << "Count levels DBD:";
    cout << countLevelsDBD(rootDBD); 
    displayTreeGraphically(rootDBD);
	return 0;
}
