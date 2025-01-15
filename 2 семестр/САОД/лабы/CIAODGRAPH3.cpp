#include <conio.h>
#include <graphics.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

using namespace std;
int n100_theory = 100;
int n200_theory = 200;
int n300_theory = 300;
int n400_theory = 400;
int n500_theory = 500;
int M = 0, C = 0;

struct Stack{
    Stack *next;
    int data;
} *tail;

struct Queue
{
    Stack *head;
    Stack *tail;
};


void initGraph() {
int gd = DETECT, gm;
initwindow(1920, 1080, "Window");
setbkcolor(WHITE);
cleardevice();
}

int MyArray[480];
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

int RunNumber(int n) {
int series = 1;
for (int i = 0; i < n - 1; i++) {
if (MyArray[i] > MyArray[i + 1]) {
series += 1;
}
}
return series;
}

void Reset() {
m = 0;
c = 0;
}

void bubbleSort(int n) {
int temp;
for (int i = 0; i < n - 1; i++) {
for (int j = 0; j < n - i - 1; j++) {
c++;
if (MyArray[j] > MyArray[j + 1]) {
temp = MyArray[j];
MyArray[j] = MyArray[j + 1];
MyArray[j + 1] = temp;
m += 3;
}
}
}
}

void SelectSort(int n){
for(int i=0; i < n - 1; i++){
int count = i;
for(int j = count + 1; j < n; j++){
c++;
if (MyArray[j]<MyArray[count]){
count=j;
}
}
m+=3;
int temp = MyArray[count];
MyArray[count]=MyArray[i];
MyArray[i]=temp;
}
}

void ShakerSort(int n) {
int left = 0, right = n - 1;
int flag = 1;

while ((left < right) && flag > 0) {
flag = 0;
for (int i = left; i < right; i++) {
c++;
if (MyArray[i] > MyArray[i + 1]) {
int tmp = MyArray[i];
MyArray[i] = MyArray[i + 1];
MyArray[i + 1] = tmp;
flag = 1;
m+=3;
}
}
right--;

for (int i = right; i > left; i--) {
c++;
if (MyArray[i] < MyArray[i - 1]) {
int tmp = MyArray[i];
MyArray[i] = MyArray[i - 1];
MyArray[i - 1] = tmp;
flag = 1;
m+=3;
}
}
left++;
}
}
void BuildSort(int L, int R)
{
    int x = MyArray[L];
    int i = L;
    while (true) {
        int j = 2 * i;
        if (j >= R)
            break;
        c++;
        if ((j < R) && (MyArray[j + 1] >= MyArray[j]))
            j = j + 1;
        c++;
        if (x >= MyArray[j])
            break;
        m++;
        MyArray[i] = MyArray[j];
        i = j;
    }
    m+=2;
    MyArray[i] = x;
}

void HeapSort(int n)
{
    int L, R=n-1;
    L = (n  / 2);
    while (L >= 0) {
        BuildSort(L,R);
        L--;
    }
    R = n - 1;
    while (R > 0) {
        int temp = MyArray[0];
        MyArray[0] = MyArray[R];
        MyArray[R] = temp;
        m += 3;
        R--;
        BuildSort(0,R);
    }

}

void insertSort(int n) {
int i, j, flag;

for (i = 1; i < n; i++) {
flag = MyArray[i];
j = i - 1;

while (j >= 0) {
c++;
if (MyArray[j] > flag) {
MyArray[j + 1] = MyArray[j];
j = j - 1;
m++;
} else {
break;
}
}
m+=2;
MyArray[j + 1] = flag;
}
}
void ShellSort(int n) {
for (int h = n / 2; h > 0; h /= 2) {
for (int i = h; i < n; i += 1) {
int temp = MyArray[i];
int j;
for (j = i; j >= h; j -= h) {
c++;
if (MyArray[j - h] > temp) {
MyArray[j] = MyArray[j - h];
m++;
} else {
break;
}
}
MyArray[j] = temp;
m += 2;
}
}
}
void QuickSort(int R, int L = 0)
{
    int x = MyArray[L];
    int i = L;
    int j = R;
    while (i <= j) {
        while (MyArray[i] < x){
            i++;
            c++;
        }
        while (MyArray[j] > x){
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
    if (L < j){
        QuickSort(j, L);
        c++;
    }
    if (i < R){
        QuickSort(R, i);
        c++;
    }
}

void ShellSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
ShellSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}
setcolor(LIGHTBLUE);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void HeapSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
HeapSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}
setcolor(GREEN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void HeapSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
HeapSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(GREEN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void HeapSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
HeapSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(GREEN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void ShellSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
ShellSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(LIGHTBLUE);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void ShellSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
ShellSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(LIGHTBLUE);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void BubbleSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
bubbleSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(CYAN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void SelectSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
SelectSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(MAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void ShakerSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
ShakerSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(RED);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void SelectSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;
FillRand(n);
SelectSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(MAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void BubbleSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
bubbleSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(CYAN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void ShakerSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
ShakerSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(RED);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void SelectSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
SelectSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(MAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void ShakerSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;
FillDec(n);
ShakerSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(RED);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void QuickSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
QuickSort(n-1);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(LIGHTMAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void QuickSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
QuickSort(n-1);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(LIGHTMAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void QuickSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
QuickSort(n-1);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(LIGHTMAGENTA);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}





void BubbleSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
bubbleSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(CYAN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void InsertSortINC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillInc(n);
insertSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(BROWN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void InsertSortDEC() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillDec(n);
insertSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(BROWN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}

void InsertSortRAND() {
int startX = 50;
int startY = 648;

int steps = 100;
int maxN = 480;
float stepX = maxN/(float)steps;
int scaleY = 10;

float data[steps][2];

for (int i = 0; i <= steps; i++) {
float n = (i/(float)steps) * maxN;

FillRand(n);
insertSort(n);
data[i][0]=n*2.5;
data[i][1] =(m + c) / 100.0;
Reset();
}

setcolor(BROWN);
for (int i = 0; i < steps; ++i) {
line(startX + data[i][0], startY - data[i][1],
startX + data[i+1][0], startY - data[i + 1][1]);
}
}
void Inc() {
setcolor(DARKGRAY);
outtextxy(900, 730, "[I] Inc");
switch (currentSort) {
case 1: SelectSortINC(); break;
case 2: BubbleSortINC(); break;
case 3: ShakerSortINC(); break;
case 4: InsertSortINC(); break;
case 5: ShellSortINC(); break;
case 6: HeapSortINC(); break;
case 7: QuickSortINC(); break;
}
}


void Rand() {
setcolor(DARKGRAY);
outtextxy(900, 760, "[R] Rand");
switch (currentSort) {
case 1: SelectSortRAND(); break;
case 2: BubbleSortRAND(); break;
case 3: ShakerSortRAND(); break;
case 4: InsertSortRAND(); break;
case 5: ShellSortRAND(); break;
case 6: HeapSortRAND(); break;
case 7: QuickSortRAND(); break;
}
}

void Dec() {
setcolor(DARKGRAY);
outtextxy(900, 790, "[D] Dec");
switch (currentSort) {
case 1: SelectSortDEC(); break;
case 2: BubbleSortDEC(); break;
case 3: ShakerSortDEC(); break;
case 4: InsertSortDEC(); break;
case 5: ShellSortDEC(); break;
case 6: HeapSortDEC(); break;
case 7: QuickSortDEC(); break;
}
}
void drawTexts() {
setcolor(LIGHTGRAY);
outtextxy(900, 730, "[I] Inc");
outtextxy(900, 760, "[R] Rand");
outtextxy(900, 790, "[D] Dec");
setcolor(DARKGRAY);
if(currentSort == 1) setcolor(MAGENTA);
outtextxy(100, 730, "[1] SelectSort");
setcolor(DARKGRAY);
if (currentSort == 2) setcolor(CYAN);
outtextxy(100, 760, "[2] BubbleSort");
setcolor(DARKGRAY);
if (currentSort == 3) setcolor(RED);
outtextxy(100, 790, "[3] ShakerSort");
setcolor(DARKGRAY);
if (currentSort == 4) setcolor(BROWN);
outtextxy(240, 730, "[4] InsertSort");
setcolor(DARKGRAY);

if (currentSort == 5) setcolor(LIGHTBLUE);
outtextxy(240, 760, "[5] ShellSort");
setcolor(DARKGRAY);

if (currentSort == 6) setcolor(GREEN);
outtextxy(240, 790, "[6] HeapSort");
setcolor(DARKGRAY);

if (currentSort == 7) setcolor(LIGHTMAGENTA);
outtextxy(350, 730, "[7] QuickSort");
setcolor(DARKGRAY);

}

void drawGrid(int width, int height) {
setbkcolor(WHITE);
//cleardevice();

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
x += cellWidth, value += 20) {
line(x, xAxisPosition - 4, x, xAxisPosition + 4);
sprintf(text, "%d", value);
outtextxy(x - 10, xAxisPosition + 10, text);
}

int valueY = 0;
for (int y = (height / cellHeight - 1) * cellHeight; y >= 0;
y -= cellHeight, valueY += 5) {
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

int main() {
initGraph();
drawGrid(1920, 700);
drawTexts();

bool running = true;
while (running) {
int key = getch();
//cleardevice();
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

case '1': currentSort = 1; break;
case '2': currentSort = 2; break;
case '3': currentSort = 3; break;
case '4': currentSort = 4; break;
case '5': currentSort = 5; break;
case '6': currentSort = 6; break;
case '7': currentSort = 7; break;

case 'C':
case 'c':
cleardevice();drawGrid(1920,700);drawTexts(); break;
case 27: //ESC
running = false;
break;
}
}

closegraph();
return 0;
}
