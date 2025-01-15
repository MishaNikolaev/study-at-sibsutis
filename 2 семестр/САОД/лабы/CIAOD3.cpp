#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 100;
const int n100 = 100;
const int n200 = 200;
const int n300 = 300;
const int n400 = 400;
const int n500 = 500;

int* arr = NULL;
int* MyArray=NULL;
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
    int left = 0, right = n - 1,k=0;
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
                k=i;
            }
        }
        right=k;

        for (int i = right; i > left; i--) {
        	c++;
            if (MyArray[i] < MyArray[i - 1]) {
                int tmp = MyArray[i];
                MyArray[i] = MyArray[i - 1];
                MyArray[i - 1] = tmp;
                flag = 1;
                m+=3;
                k=i;
            }
        }
        left=k;
    }
}

void znGet() {
for(int i = 0; i < 5;i++) {
n = 100 * (i + 1);
MyArray=(int*)realloc(arr,sizeof(int)*n);
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

int main() {
srand(time(NULL));
  int time;
  MyArray = (int*)malloc(sizeof(int)*n);
  
  printf("For inc unsorted array");
  FillInc();
  PrintMas();
  printf("\nTheory M: 0\n");
  printf("\nTheory C: %d\n", (n -1));
  printf("\nSeries Inc Unsorted Array: %d", RunNumber());
  printf("\nSumma: %d", CheckSum());
  printf("\n------------------------------------");

  
  
  printf("\nFor inc sorted array");
  ShakerSort();
  PrintMas();
  printf("\nFact M: %d \n", m);
  printf("Fact C: %d\n", c);
  printf("\nSeries Inc sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
  printf("\n------------------------------------");
  Reset();
  
  printf("\nFor dec unsorted array");
  FillDec();
  PrintMas();
  printf("\nTheory M: %d\n", 3*((n*n-n)/2));
  printf("\nTheory C: %d\n", (n * n - n) / 2);
  printf("\nSeries dec Unsorted Array: %d", RunNumber());
  printf("\nSumma: %d", CheckSum());
  printf("\n------------------------------------");
  
  
  
  printf("\nFor dec sorted array");
  ShakerSort();
  PrintMas();
  printf("\nFact M: %d \n", m);
  printf("Fact C: %d\n", c);
  printf("\nSeries dec sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
  printf("\n------------------------------------");
  Reset();
  
  printf("\nFor random unsorted array");
  FillRand();
  PrintMas();
  printf("\nTheory M: %d\n", 3*((n*n-n)/4));
  printf("\nTheory C: %d\n", (n * n - n) / 2);
  printf("\nSeries random Unsorted Array: %d", RunNumber());
  printf("\nSumma: %d", CheckSum());
  printf("\n------------------------------------");
  
  
  printf("\nFor random sorted array");
  ShakerSort();
  PrintMas();
  printf("\nFact M: %d \n", m);
  printf("Fact C: %d\n", c);
  printf("\nSeries random sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
znGet();
  printf("\n--------------------------------------------------------------------------------------------------------------------");
   printf("\n");
  printf("\nTABLE TRUDOEMKOSTI:");
  printf("\n");
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  printf("\nN 		|		M(f) + C(f) bubble sort			|	M(f) + C(f) shaker sort");
  printf("\n 		|		Dec	Rand	Inc			|	Dec	Rand	Inc");
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  printf("\n%d 		|		%d	%d	%d			|	%d	%d	%d", n100, DecreaseMassivBubble[0],Rand_MassivBubble[0],IncreaseMassivBubble[0], DecreaseMassivShaker[0],Rand_MassivShaker[0],IncreaseMassivShaker[0]);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	%d	%d	%d", n200, DecreaseMassivBubble[1],Rand_MassivBubble[1],IncreaseMassivBubble[1], DecreaseMassivShaker[1],Rand_MassivShaker[1],IncreaseMassivShaker[1]);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	%d	%d	%d", n300, DecreaseMassivBubble[2],Rand_MassivBubble[2],IncreaseMassivBubble[2], DecreaseMassivShaker[2],Rand_MassivShaker[2],IncreaseMassivShaker[2]);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	%d	%d	%d", n400, DecreaseMassivBubble[3],Rand_MassivBubble[3],IncreaseMassivBubble[3], DecreaseMassivShaker[3],Rand_MassivShaker[3],IncreaseMassivShaker[3]);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	%d	%d	%d", n500, DecreaseMassivBubble[4],Rand_MassivBubble[4],IncreaseMassivBubble[4], DecreaseMassivShaker[4],Rand_MassivShaker[4],IncreaseMassivShaker[4]);
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  
    
    return 0;
}

