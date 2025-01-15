#include <algorithm>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <graphics.h>

using namespace std;

const int NODE_RADIUS = 30;
const int VERTICAL_SPACING = 100;
const int HORIZONTAL_SPACING = 50;

struct vertex {
  int data;
  int weight;
  vertex *L = NULL;
  vertex *R = NULL;
};

void calculation_AW(int **AW, int *VW,int n){
	for(int i = 0; i < n; i++){
		for(int j = (i + 1); j < n; j++){
			AW[i][j] = AW[i][j-1] + VW[j];
		}
	}
}

void calculation_AP_and_AR(int **AP, int **AR, int **AW, int n){
	for(int i = 0; i < n - 1; i++){
		int j = i + 1;
		AP[i][j] = AW[i][j];
		AR[i][j] = j;
	}
	for(int h = 2; h < n; h++){
		for(int i = 0; i < n - h; i++){
			int j = i + h;
			int m = AR[i][j - 1];
			int min = AP[i][m - 1] + AP[m][j];
			for(int k = m + 1; k <= AR[i + 1][j]; k++){
				int x = AP[i][k - 1] + AP[k][j];
				if(x < min){
					m = k;
					min = x;
				}
			}
			AP[i][j] = min + AW[i][j];
			AR[i][j] = m;
		}
	}
}

void swap(int* a, int* b)
{
    int temp;
    temp = *a;
    *a = *b;
    *b = temp;
}

void QuickSortV2(int** A, int R, int L)
{
    while (L < R) {
        int x = A[1][L];
        int i = L;
        int j = R;
        while (i <= j) {
            while (A[1][i] > x)
                i++;
            while (A[1][j] < x)
                j--;
            if (i <= j) {
				swap(&A[0][i], &A[0][j]);
                swap(&A[1][i], &A[1][j]);
                i++;
                j--;
            }
        }
        if (j - L > R - i) {
            QuickSortV2(A, R, i);
            R = j;
        }
        else {
            QuickSortV2(A, j, L);
            L=i; 
        } 
    } 
}

void addRST_R(vertex *&p, int data, int weight) {
  if (p == NULL) {
    p = new vertex;
    p -> data = data;
    p -> weight = weight;
  } else if (data < p->data)
    addRST_R(p -> L, data, weight);
  else if (data > p -> data)
    addRST_R(p -> R, data, weight);
}

void createTree(vertex*& root, int lBorderV, int rBorderV, int **AR, int **VW){
	if(lBorderV < rBorderV){
		int k = AR[lBorderV][rBorderV];
    addRST_R(root, VW[0][k], VW[1][k]);
		createTree(root, lBorderV, k - 1, AR, VW);
		createTree(root, k, rBorderV, AR, VW);
	}
}

void A1(vertex *&p, int size, int **VW)
{
	QuickSortV2(VW,size-1, 0);
	short int tmp = 0;
	for (int i = 1; i < size; i++){ 
		cout << VW[0][i];
		cout << "[";
		cout << VW[1][i]; 
		cout << "]" <<"  ";
		tmp++;
		if(tmp == 10){
			cout << endl;
			tmp = 0;
		}
	}
	for(int i = 1; i < size; i++)
	{
		addRST_R(p, VW[0][i], VW[1][i]);
	}
}

void A2(vertex *&p, int L, int R, int **VW)
{
	int wes = 0, sum = 0;
	if(L <= R)
	{
		int i = 0;
		for(i = L; i < R; i++)
			wes = wes + VW[1][i];
		

		for(i = L; i < R; i++)
		{
			if((sum <= wes / 2) && (sum + VW[1][i] > wes / 2))
				break;
			sum = sum + VW[1][i];
		}
		
		addRST_R(p, VW[0][i], VW[1][i]);
		A2(p, L, i - 1, VW);
		A2(p, i + 1, R, VW);
	}
}

int sizeTree(vertex *p, bool root) {
  if (root)
    cout << std::endl << "The size of the tree: ";
  if (p == NULL)
    return 0;
  else
    return (1 + sizeTree(p->L, 0) + sizeTree(p->R, 0));
}

int checkSumTree(vertex *p, bool root) {
  if (root)
  cout << endl << "The checksum tree: ";
  if (p == NULL)
    return 0;
  else
    return (p->data + checkSumTree(p->L, 0) + checkSumTree(p->R, 0));
}

int sumOfPathLengths(vertex *p, int depth, bool root) {
  if (root)
  cout << endl
              << "The sum of the lengths of the paths of the tree: ";
  if (p == NULL)
    return 0;
  else
    return (depth + sumOfPathLengths(p->L, depth + 1, 0) +
            sumOfPathLengths(p->R, depth + 1, 0));
}


int heightTree(vertex *p, bool root) {
  if (root)
    cout << endl << "The height tree: ";
  if (p == NULL)
    return 0;
  else
    return (1 + max(heightTree(p->L, 0), heightTree(p->R, 0)));
}

int sumLengthWaysTreeDOP(vertex* root,int L){
	int S;
	if(root == NULL){
		S = 0;
	}else{
		S=root->weight * L + sumLengthWaysTreeDOP(root->L, L + 1) + sumLengthWaysTreeDOP(root->R, L + 1);
	}
	return S;
}

float averageHeightTree(vertex *p, bool root) {
  if (root)
    cout << endl << "The average height tree: ";
  return (float(sumOfPathLengths(p, 1, 0)) / sizeTree(p, 0));
}

int weightTree(vertex* root){
	if(root == NULL){
		return 0;
	}
	return  root->weight + weightTree(root->L) + weightTree(root->R);
}

float weightedAverageHeightTree(vertex* p, bool root){
	float h;
  if (root)
    cout << endl << "The weighted average height tree: ";
	h = (float)sumLengthWaysTreeDOP(p,1) / weightTree(p);
	return h;
	
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

void printSquareMatrix (int **arr, int n){
  for(int i = 0; i < n; i++){
    for(int j = 0; j < n; j++){
      cout << arr[i][j] << " ";
    }
    cout << endl;
  }
}


void QuickSortV2(int *MyArray, int L, int R)
{
    while (L < R)
    {
        int i = L, j = R;
        int x = MyArray[L];
        while (i < j)
        {
            while (MyArray[i] < x)
            {
                i++;
            }
            while (MyArray[j] > x)
            {
                j--;
            }
            if (i <= j)
            {
                int temp = MyArray[i];
                MyArray[i] = MyArray[j];
                MyArray[j] = temp;
                i++;
                j--;
            }
        }
        if ((j - L) < (R - i))
        {
            QuickSortV2(MyArray, L, j);
            L = i;
        }
        else
        {
            QuickSortV2(MyArray, i, R);
            R = j;
        }
    }
}
void FillInc(int* array,int start,int n) {
    for(int i=start;i<n;i++) {
        array[i]=i;
    }
}


void drawNode(int x, int y, int data, int weight) {
    setcolor(BLACK);
    setfillstyle(SOLID_FILL, YELLOW);
    fillellipse(x, y, NODE_RADIUS, NODE_RADIUS);

    setbkcolor(YELLOW);
    setcolor(BLACK);
    
    char dataBuffer[4];
    sprintf(dataBuffer, "%d", data);
    outtextxy(x - 5, y - 5, dataBuffer);

    char weightBuffer[4];
    sprintf(weightBuffer, "%d", weight);
    outtextxy(x - 5, y - NODE_RADIUS - 18, weightBuffer);  
}

void drawTree(vertex* root, int x, int y, int offset, int &minX) {
    if (root == NULL) return;

    minX = min(minX, x);
    drawNode(x, y, root->data, root->weight);  

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


int main() {
    int n = 100;
    srand(time(NULL));

        int **VandW = new int *[2];

        for (int i = 0; i < 2; i++) {
            VandW[i] = new int[n + 1];
        }
        FillInc(VandW[0], 1, n + 1);
        for (int i = 1; i < n + 1; i++) {
            VandW[1][i] = rand() % n + 1;
        }
        short int tmp = 0;
        for (int i = 1; i < n + 1; i++) {
            cout << VandW[0][i];
            cout << "[";
            cout << VandW[1][i];
            cout << "]" << "  ";
            tmp++;
            if (tmp == 10) {
                cout << endl;
                tmp = 0;
            }
        }

        cout << endl;
        int **AW = new int *[n + 1];
        int **AP = new int *[n + 1];
        int **AR = new int *[n + 1];
        for (int i = 0; i < n + 1; i++) {
            AW[i] = new int[n + 1];
            AP[i] = new int[n + 1];
            AR[i] = new int[n + 1];
            for (int j = 0; j < n + 1; j++)
                AW[i][j] = AP[i][j] = AR[i][j] = 0;
        }
        calculation_AW(AW, VandW[1], n + 1);
        calculation_AP_and_AR(AP, AR, AW, n + 1);
        if (n < 26) {
            cout << "Matrix AW:" << endl;
            printSquareMatrix(AW, n + 1);
            cout << "Matrix AP:" << endl;
            printSquareMatrix(AP, n + 1);
            cout << "Matrix AR:" << endl;
            printSquareMatrix(AR, n + 1);
        }

        vertex *OST = NULL;
        createTree(OST, 0, n, AR, VandW);
        cout << endl << "DOP" << endl;
        outTree_LefttoRight(OST, 1);
        cout << endl << "_____________________";
        cout << sizeTree(OST, 1);
        cout << checkSumTree(OST, 1);
        cout << weightedAverageHeightTree(OST, 1) << endl;
        cout << "AP[0,n] / AW[0,n] = " << (double) AP[0][n] / AW[0][n] << endl;
        cout << endl << endl;

        vertex *OST_A1 = NULL;
        vertex *OST_A2 = NULL;
        A2(OST_A2, 1, n, VandW);
        A1(OST_A1, n + 1, VandW);

        cout << endl << "A1" << endl;
        outTree_LefttoRight(OST_A1, 1);
        cout << endl << "_____________________";
        cout << sizeTree(OST_A1, 1);
        cout << checkSumTree(OST_A1, 1);
        cout << weightedAverageHeightTree(OST_A1, 1) << endl;
        cout << endl << endl;

        cout << endl << "A2)" << endl;
        outTree_LefttoRight(OST_A2, 1);
        cout << endl << "_____________________";
        cout << sizeTree(OST_A2, 1);
        cout << checkSumTree(OST_A2, 1);
        cout << weightedAverageHeightTree(OST_A2, 1) << endl;
        cout << endl << endl;

    cout << endl << "_______________________________________________________________________";
    cout << endl << "|  n=100    |  size      |  sum        | height   |    average height |";
    cout << endl << "|___________|____________|_____________|__________|___________________|";
    cout << endl << "| DOP       | " << sizeTree(OST,0) << "         | " << checkSumTree(OST,0) << "         | " << heightTree(OST,0) << "        | " << weightedAverageHeightTree(OST,0) << "            |"  << endl;
    cout << endl << "| A1        | " << sizeTree(OST_A1,0) << "         | " << checkSumTree(OST_A1,0) << "         | " << heightTree(OST_A1,0) << "        | " << weightedAverageHeightTree(OST_A1,0) << "         |"  << endl;
    cout << endl << "| A2        | " << sizeTree(OST_A2,0) << "         | " << checkSumTree(OST_A2,0) << "         | " << heightTree(OST_A2,0) << "        | " << weightedAverageHeightTree(OST_A2,0) << "             |"  << endl;
    cout << "_______________________________________________________________________" <<endl;

	displayTreeGraphically(OST);
	
    return 0;
    }
