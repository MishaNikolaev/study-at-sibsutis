 #include <stdio.h>
#include <time.h>
#include <stdlib.h>

#define n 10
int m = 0;
int c = 0;

int MyArray[n];
void FillRand(){
for (int i=0;i<n;i++){
MyArray[i] = (rand()% 15 + 1);
}

}

void PrintMas(){
for (int i=0;i<n;i++){
printf(" %d",MyArray[i]);
}
printf("\n");
}

int CheckSum(){
int sum = 0;
for (int i=0;i<n;i++){
sum+=MyArray[i];
}
printf("\n%d",sum);
return sum;
}

void FillInc(){
for (int i=0;i<n;i++){
MyArray[i]=i;
}
}

void FillDec(){
for (int i=0;i<n;i++){
MyArray[i]=n-i;
}
}

int RunNumber(){

int series = 1;
for (int i=0;i<n-1;i++){
if (MyArray[i]>MyArray[i+1]){
series+=1;
}
}
return series;
}

void SelectSort(){
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

void FixSelectSort(){
	for(int i=0; i < n - 1; i++){
		int count = i;
		for(int j = count + 1; j < n; j++){
			c++;
			if (MyArray[j]<MyArray[count]){
				count=j;
			}
		}
		if (i!=count){
		m+=3;
		int temp = MyArray[count];
		MyArray[count]=MyArray[i];
		MyArray[i]=temp;
	}
}
}

void Reset(){
	m=0;
	c=0;
}


int main(){
srand(time(NULL));
FillRand();
printf("Unsorted array:");
PrintMas();
printf("Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("------------------------------------");
printf("\nSorted array:");
SelectSort();
PrintMas();
printf("Fact M: %d\n", m);
printf("Fact C: %d\n", c);
Reset();
printf("Series sorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\n------------------------------------");
printf("\nDec array");
FillDec();
printf("\nUnsorted array:");
PrintMas();
printf("Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("\nSorted array:");
SelectSort();
PrintMas();
printf("Fact M: %d\n", m);
printf("Fact C: %d\n", c);
Reset();
printf("Series sorted dec Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\n------------------------------------");
printf("\nInc array");
FillInc();
printf("\nUnsorted array:");
PrintMas();
printf("Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("\nSorted array:");
SelectSort();
PrintMas();
printf("Fact M: %d\n", m);
printf("Fact C: %d\n", c);
Reset();
printf("Series sorted inc Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\n------------------------------------");

printf("\nFIX_SORT");
FillRand();
printf("\nFIX_SORT Unsorted array:");
PrintMas();
printf("FIX_SORT Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("------------------------------------");
printf("\nSorted array:");
FixSelectSort();
PrintMas();
printf("FIX_SORT Fact M: %d\n", m);
printf("FIX_SORT Fact C: %d\n", c);
Reset();
printf("FIX_SORT Series sorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\n------------------------------------");
printf("\n FIX_SORT Dec array");
FillDec();
printf("\n FIX_SORT Unsorted array:");
PrintMas();
printf(" FIX_SORT Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("\n FIX_SORT Sorted array:");
FixSelectSort();
PrintMas();
printf("FIX_SORT Fact M: %d\n", m);
printf("FIX_SORT Fact C: %d\n", c);
Reset();
printf("FIX_SORT Series sorted dec Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\n------------------------------------");
printf("\n FIX_SORT Inc array");
FillInc();
printf("\n FIX_SORT Unsorted array:");
PrintMas();
printf(" FIX_SORT Series Unsorted Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();
printf("\nTheory M: %d\n", 3*(n-1));
printf("Theory C: %d\n", (n*n-n)/2);
printf("\nSorted array:");
FixSelectSort();
PrintMas();
printf(" FIX_SORT Fact M: %d\n", m);
printf(" FIX_SORT Fact C: %d\n", c);
Reset();
printf(" FIX_SORT Series sorted inc Array:");
printf(" %d",RunNumber());
printf("\nSumma:");
CheckSum();


return 0;
}
