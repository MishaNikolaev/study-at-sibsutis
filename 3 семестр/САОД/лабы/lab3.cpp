#include <graphics.h>

#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>

using namespace std;

const int NODE_RADIUS = 30;
const int VERTICAL_SPACING = 100;

struct vertex {
  int data;
  vertex *L = NULL;
  vertex *R = NULL;
};
struct Tree1{
	string zn;
	int chast=1;
	Tree1* right=NULL;
	Tree1* left=NULL;
};
Tree1* initTree1(string zn) {
	Tree1* newTree=new Tree1;
	newTree->zn=zn;
	return newTree; 
}

void RekAddToSDP_4p(Tree1*& root,string zn) {
	if(root==NULL) {
		root=initTree1(zn);
		return;
	}
	if(root->zn==zn) {
		root->chast+=1;
	}
	else if(zn>root->zn) {
		RekAddToSDP_4p(root->right,zn);
	}
	else {
		RekAddToSDP_4p(root->left,zn);
	}
}
void printTreeLeftToRight_4p(Tree1 *root) {
	if(root==NULL) 
		return;
	printTreeLeftToRight_4p(root->left);
	cout<<root->zn;
	cout<<" "<<root->chast<<endl;
	printTreeLeftToRight_4p(root->right);
}
void punkt4() {
	cout<<endl;
	string uf;
	getline(cin,uf);
	string temp="";
	Tree1* root=NULL;
	//cout<<temp.length();
	for(int i=0;i<(int)uf.length();i++){
		//cout<<uf[i];
		if(uf[i]==' ') {
			//cout<<"uf";
			RekAddToSDP_4p(root,temp);
			temp="";
		}
		else {
		
			temp.append(uf,i,1);
			//cout<<temp;
		}
	}
	RekAddToSDP_4p(root,temp);
	printTreeLeftToRight_4p(root);
	
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


void outTree_LefttoRight(vertex *p, bool root = true) {
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

bool addRST_R(vertex *&p, int data) {
  if (p == NULL) {
    p = new vertex;
    p->data = data;
    return true;
  }
  if (data < p->data) return addRST_R(p->L, data);
  if (data > p->data) return addRST_R(p->R, data);
  return false;
}

vertex *createRST_R(int *dataArray, int n) {
  vertex *root = NULL;
  for (int i = 0; i < n; i++) {
    addRST_R(root, dataArray[i]);
  }
  return root;
}

bool deleteVertexWithKey(vertex *&root, int key) {
  vertex **p = &root;
  while (*p != NULL) {
    if ((*p)->data < key)
      p = (&((*p)->R));
    else if ((*p)->data > key)
      p = (&((*p)->L));
    else
      break;
  }
  if (*p != NULL) {
    vertex *q = *p;
    if (q->L == NULL)
      *p = q->R;
    else if (q->R == NULL)
      *p = q->L;
    else { 
      vertex *r = q->L;
      vertex *s = q;
      if (r->R == NULL) {
        r->R = q->R;
      	  *p = r;
      } else {
        while (r->R != NULL) {
          s = r;
          r = r->R;
        }
        s->R = r->L;
        r->L = q->L;
        r->R = q->R;
        *p = r;
      }
    }
    delete (q);
  } else
    return false;
  return true;
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
  
  initwindow(width, height, "Tree delete vertex");
  
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
    char buffer[5];
    int i = 0;

    while (true) {
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

    int key = atoi(buffer);
    if (key == -1) break;

    bool deleted = deleteVertexWithKey(root, key);
    if (deleted) {
      cleardevice();
      drawTree(root, startX, startY, screenWidth / 4, minX);
    } else {
      setcolor(RED);
      outtextxy(10, screenHeight - 60, "Key not found!");
    }
  }

  closegraph();
}

int main() {
  srand(time(NULL));
  int n = 10, key;
  int dataArray[n];
  punkt4();
  FillRand(dataArray, n);
  vertex *root = createRST_R(dataArray, n);

  displayTreeGraphically(root);
  return 0;
}
