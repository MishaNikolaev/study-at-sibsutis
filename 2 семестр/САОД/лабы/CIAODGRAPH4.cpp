#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>
#include <ctime>
#include <math.h>

using namespace std;
int n100_theory = 100;
int n200_theory = 200;
int n300_theory = 300;
int n400_theory = 400;
int n500_theory = 500;
int M = 0, C = 0, M32 = 0;
float n_in_cell=100,zn_in_cell=1;
struct tLE32
{
    tLE32 *next;
    union {
        int data;
        unsigned char Digit[sizeof(data)];
    };
};
struct Queue32
{
    tLE32 *head;
    tLE32 *tail;
};
struct Stack {
  Stack *next;
  int data;
} * tail;

struct Queue {
  Stack *head;
  Stack *tail;
};

void initGraph() {
  int gd = DETECT, gm;
  initwindow(1920, 1080, "Window");
  setbkcolor(WHITE);
  cleardevice();
}

int MyArray[3000];
int currentSort = 1;
int m = 0;
int c = 0;

void FillRand(int n) {
  for (int i = 0; i < n; i++) {
    MyArray[i] = (rand() % 15 + 1);
  }
}

void PrintMas(int n) {
  for (int i = 0; i < n; i++) {
    printf(" %d", MyArray[i]);
  }
  printf("\n");
}

int CheckSum(int n) {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += MyArray[i];
  }
  return sum;
}

void FillInc(int n) {
  for (int i = 0; i < n; i++) {
    MyArray[i] = i + 1;
  }
}

void FillDec(int n) {
  for (int i = 0; i < n; i++) {
    MyArray[i] = n - i;
  }
}
void QueueFillInc(int n, Stack *(&head), Stack *(&tail))
{
    int i = 1;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = i;
    i++;
    do
    {
        p = new Stack;
        p->data = i;
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void QueueFillDec(int n, Stack *(&head), Stack *(&tail))
{
    int i = n;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = i;
    i--;
    do
    {
        p = new Stack;
        p->data = i;
        tail->next = p;
        tail = p;
        i--;

    } while (i > 0);
    tail->next = 0;
}

void QueueFillRand(int n, Stack *(&head), Stack *(&tail))
{
    srand(time(NULL));
    int i = 1;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = rand() % (20);
    i++;
    do
    {
        p = new Stack;
        p->data = rand() % (20);
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void Merge(Stack **a, int q, Stack **b, int r, Queue *c, int &C, int &M)
{
    while (q != 0 && r != 0)
    {
        C++;
        if ((*a)->data <= (*b)->data)
        {
            M++;
            c->tail->next = *a;
            c->tail = *a;
            *a = (*a)->next;
            q--;
        }
        else
        {
            M++;
            c->tail->next = *b;
            c->tail = *b;
            *b = (*b)->next;
            r--;
        }
    }
    while (q > 0)
    {
        M++;
        c->tail->next = *a;
        c->tail = *a;
        *a = (*a)->next;
        q--;
    }
    while (r > 0)
    {
        M++;
        c->tail->next = *b;
        c->tail = *b;
        *b = (*b)->next;
        r--;
    }
}
int Split(Stack *S, Stack **a, Stack **b, int &M)
{
    Stack *k, *p;
    *a = S;
    *b = S->next;
    int n = 1;
    k = *a;
    p = *b;
    while (p != NULL)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    M += n;
    return n;
}
void MergeSort(Stack *(&S), Stack *(&tail), int &C, int &M)
{
    C = M = 0;
    Stack *a;
    Stack *b;
    int n = Split(S, &a, &b, M);
    int p = 1;
    int q, r;
    Queue c[2];
    while (p < n)
    {
        c[0].tail = (Stack *)&(c[0].head);
        c[1].tail = (Stack *)&(c[1].head);

        int i = 0;
        int m = n;
        while (m > 0)
        {
            if (m >= p)
                q = p;
            else
                q = m;

            m = m - q;

            if (m >= p)
                r = p;
            else
                r = m;

            m = m - r;
            Merge(&a, q, &b, r, &c[i], C, M);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = NULL;
    S = c[0].head;
    tail = c[0].tail;
}

void DigitalSort(tLE32 *(&S), tLE32 *(&tail), int &M, int dec = 0) {
    int KDI[4] = {3, 2, 1, 0};
    int L = 4;
    tLE32 *temp;
    Queue32 q[256];
    tLE32 *p;
    unsigned char d;
    int k;

    for (int j = L - 1; j >= 0; j--) {
        for (int i = 0; i <= 255; i++) {
            q[i].tail = (tLE32 *)&(q[i].head);
        }
        p = S;
        k = KDI[j];
        while (p != NULL) {
            M32++;
            d = p->Digit[k];
            q[d].tail->next = p;
            q[d].tail = p;
            p = p->next;
        }
        temp = p = (tLE32 *)&S;
        int i = 0;
        int sign = 1;
        if (dec == 1) {
            i = 255;
            sign = -1;
        }

        while ((i > -1) && (i < 256)) {
            if (q[i].tail != (tLE32 *)&(q[i].head)) {
                M32++;
                p->next = q[i].head;
                p = q[i].tail;
            }
            i += sign;
        }

        p->next = NULL;
        S = temp->next;
    }
    return;
}
void QueueFillIncDG(int n, tLE32 *(&head), tLE32 *(&tail))
{
    int i = 1;
    tLE32 *p;
    head = tail = new tLE32;
    head->next = tail->next = 0;
    tail->data = i;
    i++;
    do
    {
        p = new tLE32;
        p->data = i;
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void QueueFillDecDG(int n, tLE32 *(&head), tLE32 *(&tail))
{
    int i = n;
    tLE32 *p;
    head = tail = new tLE32;
    head->next = tail->next = 0;
    tail->data = i;
    i--;
    do
    {
        p = new tLE32;
        p->data = i;
        tail->next = p;
        tail = p;
        i--;

    } while (i > 0);
    tail->next = 0;
}

void QueueFillRandDG(int n, tLE32 *(&head), tLE32 *(&tail))
{
    srand(time(NULL));
    int i = 1;
    tLE32 *p;
    head = tail = new tLE32;
    head->next = tail->next = 0;
    tail->data = rand() % (10000);
    i++;
    do
    {
        p = new tLE32;
        p->data = rand() % (10000);
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void PrintListDG(tLE32 *head, tLE32 *tail = NULL) {
    tLE32 *p;
    int q = 0;

    for (p = head; p; p = p->next) {
        cout << p->data << " ";
        q++;
    }
    if (tail != NULL) {
        cout << endl;
    }
}

void Reset() {
  m = 0;
  c = 0;
}

void BuildSort(int L, int R) {
  int x = MyArray[L];
  int i = L;
  while (true) {
    int j = 2 * i;
    if (j >= R) break;
    c++;
    if ((j < R) && (MyArray[j + 1] >= MyArray[j])) j = j + 1;
    c++;
    if (x >= MyArray[j]) break;
    m++;
    MyArray[i] = MyArray[j];
    i = j;
  }
  m += 2;
  MyArray[i] = x;
}

void HeapSort(int n) {
  int L, R = n - 1;
  L = (n / 2);
  while (L >= 0) {
    BuildSort(L, R);
    L--;
  }
  R = n - 1;
  while (R > 0) {
    int temp = MyArray[0];
    MyArray[0] = MyArray[R];
    MyArray[R] = temp;
    m += 3;
    R--;
    BuildSort(0, R);
  }
}

void QuickSort(int R, int L = 0) {
  int x = MyArray[L];
  int i = L;
  int j = R;
  while (i <= j) {
    while (MyArray[i] < x) {
      i++;
      c++;
    }
    while (MyArray[j] > x) {
      j--;
      c++;
    }
    if (i <= j) {
      int temp = MyArray[i];
      MyArray[i] = MyArray[j];
      MyArray[j] = temp;
      m += 3;
      i++;
      j--;
    }
    c++;
  }
  if (L < j) {
    QuickSort(j, L);
    c++;
  }
  if (i < R) {
    QuickSort(R, i);
    c++;
  }
}

void HeapSortDEC() {
  int startX = 50;
  int startY = 648;

  int steps = 200;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillDec(n);
    HeapSort(n);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(GREEN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}
void HeapSortRAND() {
  int startX = 50;
  int startY = 648;

  int steps = 200;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillRand(n);
    HeapSort(n);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(GREEN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void HeapSortINC() {
  int startX = 50;
  int startY = 648;

  int steps = 200;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillInc(n);
    HeapSort(n);
    data[i][0] = n * 50.0/100.0;
    data[i][1] = (m + c)*50.0/50000.0;
    Reset();
  }

  setcolor(GREEN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void QuickSortINC() {
  int startX = 50;
  int startY = 648;

  int steps = 300;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillInc(n);
    QuickSort(n - 1);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    //printf("%f %f\n",data[i][0],data[i][1]);
    printf("%f\n",n);
    //data[i][0]=n*2.5;
    //data[i][1]=(m+c)/100.0;
    Reset();
  }

  setcolor(LIGHTMAGENTA);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void QuickSortDEC() {
  int startX = 50;
  int startY = 648;

  int steps = 200;
  int maxN = 210;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillDec(n);
    QuickSort(n - 1);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(LIGHTMAGENTA);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void QuickSortRAND() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];

  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    FillRand(n);
    QuickSort(n - 1);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(LIGHTMAGENTA);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}
void MergeSortRAND() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  Stack *head,*tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    QueueFillRand(n,head,tail);
    MergeSort(head,tail,c,m);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(LIGHTRED);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void MergeSortINC() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  Stack *head,*tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    QueueFillInc(n,head,tail);
    MergeSort(head,tail,c,m);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(LIGHTRED);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}
void ResetList(){
    M = 0;
    C = 0;
    //M32=0;
}

void MergeSortDEC() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  Stack *head,*tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    QueueFillDec(n,head,tail);
    MergeSort(head,tail,c,m);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (m + c)*50.0/zn_in_cell/1000.0;
    Reset();
  }

  setcolor(LIGHTRED);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}
void DigitalSortINC() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  tLE32 *S = new tLE32;
  tLE32 *head, *tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    QueueFillIncDG(n,head,tail);
    DigitalSort(S, tail, M, 0);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (M32 + c)*50.0/zn_in_cell/1000.0;
    ResetList();
  }

  setcolor(LIGHTCYAN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void DigitalSortDEC() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  tLE32 *S = new tLE32;
  tLE32 *head, *tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;

    QueueFillDecDG(n,head,tail);
    DigitalSort(S, tail, M, 0);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (M32 + c)*50.0/zn_in_cell/1000.0;
    ResetList();
  }

  setcolor(LIGHTCYAN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}

void DigitalSortRAND() {
  int startX = 50;
  int startY = 648;

  int steps = 250;
  int maxN = 2100;
  float stepX = maxN / (float)steps;
  int scaleY = 10;

  float data[steps][2];
  tLE32 *S = new tLE32;
  tLE32 *head, *tail;
  for (int i = 0; i <= steps; i++) {
    float n = (i / (float)steps) * maxN;
	std::cout<<"1";
    QueueFillRandDG(n,head,tail);
    std::cout<<"2";
    DigitalSort(S, tail, M, 0);
    data[i][0] = n * 50.0/n_in_cell;
    data[i][1] = (M32 + c)*50.0/zn_in_cell/1000.0;
    ResetList();
  }

  setcolor(LIGHTCYAN);
  for (int i = 0; i < steps; ++i) {
    line(startX + data[i][0], startY - data[i][1], startX + data[i + 1][0],
         startY - data[i + 1][1]);
  }
}
void drawGrid(int width, int height) {
  setbkcolor(WHITE);

  setcolor(LIGHTGRAY);
  int cellWidth = 50;
  int cellHeight = 50;
  int twoThirdsWidth = (width * 2) / 3;
  int startYAxis = cellWidth;
  for (int x = 0; x < twoThirdsWidth; x += cellWidth) {
    for (int y = 0; y < height; y += cellHeight) {
      rectangle(x, y, x + cellWidth, y + cellHeight);
    }
  }

  setcolor(BLACK);
  int xAxisPosition = height - cellHeight;
  line(0, xAxisPosition, width, xAxisPosition);
  line(startYAxis, 0, startYAxis, height);

  char text[20];
  for (int x = cellWidth, value = 0; x < twoThirdsWidth;
       x += cellWidth, value += n_in_cell) {
    line(x, xAxisPosition - 4, x, xAxisPosition + 4);
    sprintf(text, "%d", value);
    outtextxy(x - 10, xAxisPosition + 10, text);
  }

  int valueY = 0;
  for (int y = (height / cellHeight - 1) * cellHeight; y >= 0;
       y -= cellHeight, valueY += zn_in_cell) {
    line(startYAxis - 4, y, startYAxis + 4, y);
    if (valueY == 80) {
      strcpy(text, "M(f)+C(f)");
      outtextxy(startYAxis - (strlen(text) * 8 + 20), y + 10, text);
    } else {
      sprintf(text, "%dk", valueY);
      outtextxy(startYAxis - (strlen(text) * 8 + 20), y, text);
    }
  }
}

void Inc() {
setcolor(DARKGRAY);
outtextxy(900, 730, (char*)"[I] Inc");
switch (currentSort) {
case 6: HeapSortINC(); break;
case 7: QuickSortINC(); break;
case 8: MergeSortINC(); break;
case 9: DigitalSortINC(); break;
}
}


void Rand() {
setcolor(DARKGRAY);
outtextxy(900, 760, (char*)"[R] Rand");
switch (currentSort) {
case 6: HeapSortRAND(); break;
case 7: QuickSortRAND(); break;
case 8: MergeSortRAND(); break;
case 9: DigitalSortRAND(); break;
}
}

void Dec() {
setcolor(DARKGRAY);
outtextxy(900, 790, (char*)"[D] Dec");
switch (currentSort) {
case 6: HeapSortDEC(); break;
case 7: QuickSortDEC(); break;
case 8: MergeSortDEC(); break;
case 9: DigitalSortDEC(); break;
}
}

void drawTexts() {
    setcolor(LIGHTGRAY);
    outtextxy(900, 730, (char*)"[I] Inc");
    outtextxy(900, 760, (char*)"[R] Rand");
    outtextxy(900, 790, (char*)"[D] Dec");

    setcolor(DARKGRAY);
    if (currentSort == 6) setcolor(GREEN);
    outtextxy(240, 730, (char*)"[6] HeapSort");

    setcolor(DARKGRAY);
    if (currentSort == 7) setcolor(LIGHTMAGENTA);
    outtextxy(240, 760, (char*)"[7] QuickSort");
    
    setcolor(DARKGRAY);
    if (currentSort == 8) setcolor(LIGHTRED);
    outtextxy(240, 790, (char*)"[8] MergeSort");
    
    setcolor(DARKGRAY);
    if (currentSort == 9) setcolor(LIGHTCYAN);
    outtextxy(400, 730, (char*)"[9] DigitalSort");
    
}

int main() {
initGraph();
drawGrid(1920, 700);
drawTexts();

bool running = true;
while (running) {
int key = getch();
drawGrid(1920, 700);
drawTexts();

switch (key) {
case 'i':
case 'I':
Inc();
break;
case 'd':
case 'D':
Dec();
break;
case 'r':
case 'R':
Rand();
break;

case '6': currentSort = 6; break;
case '7': currentSort = 7; break;
case '8': currentSort = 8; break;
case '9': currentSort = 9; break;

case 'C':
case 'c':
cleardevice();
drawGrid(1920,700);
drawTexts(); 
break;
case 27: 
running = false;
break;
}
}

closegraph();
return 0;
}

