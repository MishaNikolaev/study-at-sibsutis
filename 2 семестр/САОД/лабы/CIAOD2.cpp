 #include <stdio.h>
#include <stdlib.h>
#include <time.h>

#define n 80
const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;

const int sumTHDEC100 = 3*((n100_theory*n100_theory-n100_theory)/2) + (n100_theory * n100_theory - n100_theory) / 2;
const int sumTHDEC200 = 3*((n200_theory*n200_theory-n200_theory)/2) + (n200_theory * n200_theory - n200_theory) / 2;
const int sumTHDEC300 = 3*((n300_theory*n300_theory-n300_theory)/2) + (n300_theory * n300_theory - n300_theory) / 2;
const int sumTHDEC400 = 3*((n400_theory*n400_theory-n400_theory)/2) + (n400_theory * n400_theory - n400_theory) / 2;
const int sumTHDEC500 = 3*((n500_theory*n500_theory-n500_theory)/2) + (n500_theory * n500_theory - n500_theory) / 2;

const int sumTHRAND100 = 3*((n100_theory*n100_theory-n100_theory)/4) + (n100_theory * n100_theory - n100_theory) / 2;
const int sumTHRAND200 = 3*((n200_theory*n200_theory-n200_theory)/4) + (n200_theory * n200_theory - n200_theory) / 2;
const int sumTHRAND300 = 3*((n300_theory*n300_theory-n300_theory)/4) + (n300_theory * n300_theory - n300_theory) / 2;
const int sumTHRAND400 = 3*((n400_theory*n400_theory-n400_theory)/4) + (n400_theory * n400_theory - n400_theory) / 2;
const int sumTHRAND500 = 3*((n500_theory*n500_theory-n500_theory)/4) + (n500_theory * n500_theory - n500_theory) / 2;

const int sumTHINC100 = (n100_theory * n100_theory - n100_theory) / 2;
const int sumTHINC200 = (n200_theory * n200_theory - n200_theory) / 2;
const int sumTHINC300 = (n300_theory * n300_theory - n300_theory) / 2;
const int sumTHINC400 = (n400_theory * n400_theory - n400_theory) / 2;
const int sumTHINC500 = (n500_theory * n500_theory - n500_theory) / 2;

int MyArray[n];

int m = 0;
int c = 0;
void PrintTheoryDEC(){
	printf("\nTheory M: %d\n", 3*((n100_theory*n100_theory-n100_theory)/2));
  printf("\nTheory C: %d\n", (n100_theory * n100_theory - n100_theory) / 2);
}
void PrintTheoryRAND(){
	printf("\nTheory M: %d\n", 3*((n100_theory*n100_theory-n100_theory)/4));
  printf("\nTheory C: %d\n", (n100_theory * n100_theory - n100_theory) / 2);
}

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
  //printf("\n%d", sum);
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

int main() {
  srand(time(NULL));
  int time;
  
  printf("For inc unsorted array");
  FillInc();
  PrintMas();
  printf("\nTheory M: 0\n");
  printf("\nTheory C: %d\n", (n * n - n) / 2);
  printf("\nSeries Inc Unsorted Array: %d", RunNumber());
  printf("\nSumma: %d", CheckSum());
  printf("\n------------------------------------");

  
  
  printf("\nFor inc sorted array");
  bubbleSort();
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
  bubbleSort();
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
  bubbleSort();
  PrintMas();
  printf("\nFact M: %d \n", m);
  printf("Fact C: %d\n", c);
  printf("\nSeries random sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  
  printf("\n");
  printf("\nTABLE TRUDOEMKOSTI:");
  printf("\n");
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  printf("\nN 		|		M + C teor.				|	M + C fact.");
  printf("\n 		|		Dec	Rand	Inc			|	Dec	Rand	Inc");
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  printf("\n%d 		|		%d	%d	%d			|	19800	12507	4950", n100_theory,sumTHDEC100,sumTHRAND100,sumTHINC100);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	79600	47770	19900",n200_theory,sumTHDEC200,sumTHRAND200,sumTHINC200);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	179400	108021	44850",n300_theory,sumTHDEC300,sumTHRAND300,sumTHINC300);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	319200	192615	79800",n400_theory,sumTHDEC400,sumTHRAND400,sumTHINC400);
  printf("\n		|							|");
  printf("\n%d 		|		%d	%d	%d			|	499000	299128	124750",n500_theory,sumTHDEC500,sumTHRAND500,sumTHINC500);
  printf("\n--------------------------------------------------------------------------------------------------------------------");
  
	return 0;
}

