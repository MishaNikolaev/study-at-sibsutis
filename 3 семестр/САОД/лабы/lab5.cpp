#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <graphics.h>

using namespace std;

const int NODE_RADIUS = 30;
const int VERTICAL_SPACING = 100;
int num_of_vrash=0;
struct vertex{			
    vertex *L = NULL;
    vertex *R = NULL;
    short int balance = 0;
    int data;
};
     
bool addToAVL(vertex *&p, int data, bool &rost);
void rotateLR(vertex *&p);
void rotateRL(vertex *&p);

vertex *createAVL(int n) {
    vertex *root = NULL;
    int i = 0;
    bool rost;
    while (i < n) {
        int data = rand() % n;

        if (addToAVL(root, data, rost))
            i++;
    }
    return root;
}

void rotateLL1(vertex *&p, bool &decrease) {
  vertex *q = p->L;

  if (q->balance == 0) {
    p->balance = -1;
    q->balance = 1;
    decrease = false;
  } else {
    p->balance = 0;
    q->balance = 0;
  }
  p->L = q->R;
  q->R = p;
  p = q;
  num_of_vrash++;
}
void rotateRR1(vertex *&p, bool &decrease) {
  vertex *q = p->R;
  if (q->balance == 0) {
    p->balance = 1;
    q->balance = -1;
    decrease = false;
  } else {
    p->balance = 0;
    q->balance = 0;
  }
  p->R = q->L;
  q->L = p;
  p = q;
  num_of_vrash++;
}

void BL(vertex *&p, bool &decrease) {
  if (p->balance == -1){
    p->balance = 0;
}
  else if (p->balance == 0) {
    p->balance = 1;
    decrease = false;
  } else if (p->balance == 1) {
    if (p->R->balance >= 0)
      rotateRR1(p, decrease);
    else
      rotateRL(p);
  }
}
void BR(vertex *&p, bool &decrease) {
  if (p->balance == 1)
    p->balance = 0;
  else if (p->balance == 0) {
    p->balance = -1;
    decrease = false;
  } else if (p->balance == -1) {
    if (p->L->balance <= 0)
      rotateLL1(p, decrease);
    else
      rotateLR(p);
  }
}
vertex* DeleteVou(vertex *&r,vertex *&q,bool &decrease) {
	if(r->R!=NULL) {
		DeleteVou(r->R,q,decrease);
		if(decrease) {
			BR(r,decrease);
		}
	}
	else {
		q->data=r->data;
		q=r;
		r=r->L;
		decrease=true;
	}
}
bool del(int x, vertex *&p, bool &decrease) {
    if (p == NULL) {
        return false;
    }
    bool vou=true;
    if (x < p->data) {
        vou=del(x, p->L, decrease);
        if (decrease) BL(p, decrease);  
    } else if (x > p->data) {
        vou=del(x, p->R, decrease);
        if (decrease) BR(p, decrease); 
    } else {
        vertex *q = p;
        if (q->L == NULL) {
            p = q->R; 
            decrease = true; 
        } else if (q->R == NULL) {
            p = q->L; 
            decrease = true; 
        } else {
            DeleteVou(q->L, q, decrease); 
            if(decrease) {
            	BL(p,decrease);
			}
        }
        delete(q); 
    }
    return true && vou;
}


void rotateLL(vertex *&p){
    vertex *q = p->L;
    p->balance = 0;
    q->balance = 0;
    p->L = q->R; 
    q->R = p;
    p=q;
    num_of_vrash++;
}

void rotateRR(vertex *&p){
    vertex *q = p->R;
    p->balance = 0;
    q->balance = 0;
    p->R = q->L; 
    q->L = p;
    p=q;
    num_of_vrash++;
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
    num_of_vrash++;
}

void rotateRL(vertex *&p){
    vertex *q = p->R;
    vertex *r = q->L;
    if(r->balance >0)
        p->balance = -1;
    else
        p->balance = 0;
    if(r->balance<0)
        q->balance = 1;
    else
        q->balance = 0;
    r->balance = 0;
    q->L = r->R;
    p->R = r->L;
    r->R = q;
    r->L = p;
    p = r;
    num_of_vrash++;
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
void outTree_LefttoRight1(vertex* p, bool root = true) {
    static int counter = 0;
    if (root) {
        cout << endl << "Left to right: " << endl;
        counter = 0;
    }
    if (p != NULL) {
        outTree_LefttoRight1(p->L, false);
        if (counter > 0 && counter % 10 == 0) {
            cout << endl;
        }
        cout <<p->data<<","<<p->balance<<" ";
        counter++;
        outTree_LefttoRight1(p->R, false);
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

void drawTree(vertex *root, int x, int y, int offset, int &minX) {
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
void displayTreeGraphically(vertex *root) {
  int width = 700;
  int height = 700;
  
  initwindow(width, height, "AVL Tree delete vertex");
  
  setbkcolor(DARKGRAY);
  cleardevice();

  int screenWidth = getmaxx();
  int screenHeight = getmaxy();

  int startX = screenWidth / 2;
  int startY = 50;
  int minX = startX;

  drawTree(root, startX, startY, screenWidth / 4, minX);

  while (true) {
    setbkcolor(DARKGRAY);
    setcolor(WHITE);
    outtextxy(10, screenHeight - 30,
              "Choice vertex to delete (type -1 to exit): ");
    int i = 0;
	char buffer[5];
    while (true) {
    	//char buffer[5];
      char ch = getch();
      if (ch == '\r') {  
        buffer[i] = '\0';
        break;
      } else if (ch == '\b' && i > 0) {  
        --i;
        outtextxy(300 + i * 10, screenHeight - 30, " ");
      } else if (isdigit(ch) ||
                 (ch == '-' &&
                  i == 0)) {  
        buffer[i++] = ch;
        char str[2] = {ch, '\0'};
        outtextxy(300 + (i - 1) * 10, screenHeight - 30, str);
      }
    }
	//cout<<key;
    int key = atoi(buffer);
    if (key == -1) break;
    bool deleted = del(key, root, deleted); 
    if (deleted) {
    	outTree_LefttoRight1(root,true);
      cleardevice();
      drawTree(root, startX, startY, screenWidth / 4, minX);
    } else {
      setcolor(RED);
      outtextxy(10, screenHeight - 60, "Key not found!");
    }
  }

  closegraph();
}
void deleteAVL(vertex* root,int n) {
    int i = 0;
    bool rost;
    while (i < n) {
        int data = rand() % n;
		bool rost=false;
        if (del(data, root, rost))
            i++;
    }
}
int main() {
    srand((time(0)));
    int n = 1000;
    int key;
    vertex* root = createAVL(n); 
    outTree_LefttoRight(root); 
	/*
    for (int i = 0; i < 10; ) {
        int key; 
        cout << "Enter key to delete: "; 
        cin >> key; 
        bool vou = false; 
        del(key, root, vou); 
        if (vou) { 
            i++;
        }
        outTree_LefttoRight(root); 
    }
    */
    int tries=1250;
    float sum1=0,sum2=0;
    num_of_vrash=0;
    for(int i=0;i<tries;i++) {
    	num_of_vrash=0;
		vertex* root=createAVL(n);
    	sum1+=num_of_vrash;
    	
    	num_of_vrash=0;
    	deleteAVL(root,n);
    	sum2+=num_of_vrash;
	}
	cout<<endl<<sum1/(float)n/tries<<endl<<sum2/(float)n/tries;
    displayTreeGraphically(root);
    //cout<<endl<<sum1/(float)n/tries<<endl<<sum2/(float)n/tries;
    return 0;
}
