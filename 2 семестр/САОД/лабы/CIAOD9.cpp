#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int n = 10;

const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;

const int sumBTH100 = 3 * log2(n100_theory+1) + 2;
const int sumBTH200 = 3 * log2(n200_theory+1) + 2;
const int sumBTH300 = 3 * log2(n300_theory+1) + 2;
const int sumBTH400 = 3 * log2(n400_theory+1) + 2;
const int sumBTH500 = 3 * log2(n500_theory+1) + 2;

const int sumTH100 = 2741;
const int sumTH200 = 6084;
const int sumTH300 = 9653;
const int sumTH400 = 13370;
const int sumTH500 = 17196;

int *arr = NULL;
int *MyArray = NULL;
int Rand_MassivBuild[5],Inc_MassivBuild[5], Dec_MassivBuild[5];
int Rand_Massiv[5], IncreaseMassiv[5], DecreaseMassiv[5];

int m = 0;
int c = 0;

void FillRand() {
    for (int i = 0; i < n; i++) {
        MyArray[i] = (rand() % 100 + 1);
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

void Reset() {
    m = 0;
    c = 0;
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

void HeapSort()
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
void znGet() {
    for (int i = 0; i < 5; i++) {
        n = 100 * (i + 1);
        MyArray = (int *) realloc(arr, sizeof(int) * n);
        Reset();
        FillRand();
        HeapSort();
        Rand_Massiv[i] = m + c;
        Reset();
        FillDec();
        HeapSort();
        DecreaseMassiv[i] = m + c;
        Reset();
        FillInc();
        HeapSort();
        IncreaseMassiv[i] = m + c;
        Reset();
    }
}

void znGetBuild() {
    for (int i = 0; i < 5; i++) {
        n = 100 * (i + 1);
        MyArray = (int *) realloc(arr, sizeof(int) * n);
        Reset();
        FillRand();
        BuildSort(0, n-1);
        Rand_MassivBuild[i] = m + c;
        Reset();
        FillDec();
        BuildSort(0,n-1);
        Dec_MassivBuild[i] = m + c;
        Reset();
        FillInc();
        BuildSort(0,n-1);
        Inc_MassivBuild[i] = m + c;
        Reset();
    }
}

int main() {
    int m_t = (n*log2(n)+6.5*n-4);
    int c_t = (2*n*log2(n)+n+2);
    srand(time(NULL));
    int time;
    MyArray = (int *) malloc(sizeof(int) * n);

    printf("\nFor random unsorted array");
    FillRand();
    PrintMas();
    printf("\nTheory M: %d\n", m_t);
    printf("\nTheory C: %d\n", c_t);
    printf("\nSeries random Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor random sorted array");
    HeapSort();
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries random sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    printf("\n--------------------------------------------------------------------------------------------------------------------");

    znGet();
    znGetBuild();

    printf("\n");
    printf("Table of complexity building of pyramid\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    |   M + C teor (BuildSort) |  M + C fact (BuildSort)      \n");
    printf("     |   	                |  Dec   Rand   Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d|           %d             | %-5d  %-5d   %-5d\n", n100_theory, sumBTH100,
           Dec_MassivBuild[0], Rand_MassivBuild[0], Inc_MassivBuild[0]);
    printf("%-5d|           %d             | %-5d  %-5d   %-5d\n", n200_theory, sumBTH200,
           Dec_MassivBuild[1], Rand_MassivBuild[1], Inc_MassivBuild[1]);
    printf("%-5d|           %d             | %-5d  %-5d   %-5d\n", n300_theory, sumBTH300,
           Dec_MassivBuild[2], Rand_MassivBuild[2], Inc_MassivBuild[2]);
    printf("%-5d|           %d             | %-5d  %-5d   %-5d\n", n400_theory, sumBTH400,
           Dec_MassivBuild[3], Rand_MassivBuild[3], Inc_MassivBuild[3]);
    printf("%-5d|           %d             | %-5d  %-5d   %-5d\n", n500_theory, sumBTH500,
           Dec_MassivBuild[4], Rand_MassivBuild[4], Inc_MassivBuild[4]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\n");

    printf("\n");
    printf("Table of complexity of HeapSort\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    |   M + C teor (HeapSort)  |  M + C fact (HeapSort)      \n");
    printf("     |   	                |  Dec   Rand   Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d|           %d           | %-5d  %-5d   %-5d\n", n100_theory, sumTH100,
           DecreaseMassiv[0], Rand_Massiv[0], IncreaseMassiv[0]);
    printf("%-5d|           %d           | %-5d  %-5d   %-5d\n", n200_theory, sumTH200,
           DecreaseMassiv[1], Rand_Massiv[1], IncreaseMassiv[1]);
    printf("%-5d|           %d           | %-5d  %-5d   %-5d\n", n300_theory, sumTH300,
           DecreaseMassiv[2], Rand_Massiv[2], IncreaseMassiv[2]);
    printf("%-5d|           %d          | %-5d  %-5d   %-5d\n", n400_theory, sumTH400,
           DecreaseMassiv[3], Rand_Massiv[3], IncreaseMassiv[3]);
    printf("%-5d|           %d          | %-5d  %-5d   %-5d\n", n500_theory, sumTH500,
           DecreaseMassiv[4], Rand_Massiv[4], IncreaseMassiv[4]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\n");

    free(MyArray);
    return 0;
}
