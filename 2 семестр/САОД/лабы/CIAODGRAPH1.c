#include <graphics.h>
#include <conio.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
int func(int x) {
	return x+1;
}
int n = 100;
const int n100 = 100;
const int n200 = 200;
const int n300 = 300;
const int n400 = 400;
const int n500 = 500;

int* arr = NULL;
int* MyArray=NULL;
void bubleSortNew(int);
int Rand_MassivBubble[5],IncreaseMassivBubble[5],DecreaseMassivBubble[5];
int Rand_MassivShaker[5],IncreaseMassivShaker[5],DecreaseMassivShaker[5];

int m = 0;
int c = 0;


void FillRand() {
  for (int i = 0; i < n; i++) {
    MyArray[i] = (rand() % 15 + 1);
  }
}

void PrintMas() {
  for (int i = 0; i < n; i++) {
    printf(" %d", MyArray[i]);
  }
  printf("\n");
}

int CheckSum() {
  int sum = 0;
  for (int i = 0; i < n; i++) {
    sum += MyArray[i];
  }
  return sum;
}

void FillInc() {
  for (int i = 0; i < n; i++) {
    MyArray[i] = i;
  }
}

void FillDec() {
  for (int i = 0; i < n; i++) {
    MyArray[i] = n - i;
  }
}

int RunNumber() {
  int series = 1;
  for (int i = 0; i < n - 1; i++) {
    if (MyArray[i] > MyArray[i + 1]) {
      series += 1;
    }
  }
  return series;
}

void Reset(){
	m=0;
	c=0;
}
void bubbleSort() {
  int temp;
  for (int i = 0; i < n - 1; i++) {
    for (int j = 0; j < n - i - 1; j++) {
      c++;
      if (MyArray[j] > MyArray[j + 1]) {
        temp = MyArray[j];
        MyArray[j] = MyArray[j + 1];
        MyArray[j + 1] = temp;
        m+=3;
      }
    }
  }
}

void ShakerSort() {
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
void znGet() {
for(int i = 0; i < 5;i++) {
n = 100 * (i + 1);
MyArray=realloc(arr,sizeof(int)*n);
Reset();
FillRand();
bubbleSort();
Rand_MassivBubble[i] = m+c;
Reset();
FillDec();
bubbleSort();
DecreaseMassivBubble[i] = m+c;
Reset();
FillInc();
bubbleSort();
IncreaseMassivBubble[i] = m+c;
Reset();

Reset();
FillRand();
ShakerSort();
Rand_MassivShaker[i] = m+c;
Reset();
FillDec();
ShakerSort();
DecreaseMassivShaker[i] = m+c;
Reset();
FillInc();
ShakerSort();
IncreaseMassivShaker[i] = m+c;
Reset();
}
}
void drawGrid(int width, int height) {
    setbkcolor(WHITE);
    cleardevice();

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
    //int xAxisPosition = (height / 2) + (height / 4) - ((height / 2 + height / 4) % cellHeight);
    int xAxisPosition = height-cellHeight;//(height / 2) + (height / 4) - ((height / 2 + height / 4) % cellHeight);
    line(0, xAxisPosition, width, xAxisPosition);
    line(startYAxis, 0, startYAxis, height);
	
    char text[20]; 
    for (int x = cellWidth, value = 0; x < twoThirdsWidth; x += cellWidth, value += 20) {
        line(x, xAxisPosition - 4, x, xAxisPosition + 4);
        sprintf(text, "%d", value);
        outtextxy(x - 10, xAxisPosition + 10, text);
    }

    
    int valueY = 0; 
    int uf=height/cellHeight-1;
    printf("%d",uf);
    for (int y = (height/cellHeight-1)*cellHeight; y >= 0; y -= cellHeight, valueY += 5) {
        line(startYAxis - 4, y, startYAxis + 4, y);
        if (valueY == 80) { 
            strcpy(text, "M(f)+C(f)");
            outtextxy(startYAxis - (strlen(text) * 8 + 20), y + 10, text);
        } else {
            sprintf(text, "%dk", valueY);
            outtextxy(startYAxis - (strlen(text) * 8 + 20), y , text); 
        }
    }
    znGet();
    for (int i=1;i<4;i++) {
    	line(i*cellWidth,height-RandMassiveShaker[i]*cellHeight,(i+1)*cellWidth,height-RandMassiveShaker[i]*cellHeight);
	}
    
}

int main() {
    int gd = DETECT, gm;
    initwindow(1920, 700, "Grid with Y-axis Labels");
    drawGrid(1920, 700);

    getch();
    closegraph();
    return 0;
}
