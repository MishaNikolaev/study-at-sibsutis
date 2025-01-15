#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int Depth_max = 0;
int Depth = 0;
int n = 100;

int randTH = n*log2(n);
const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;

int *arr = NULL;
int *MyArray = NULL;
int Rand_Massiv[5], IncreaseMassiv[5], DecreaseMassiv[5];
int m = 0;
int c = 0;

void FillRand() {
    for (int i = 0; i < n; i++) {
        MyArray[i] = (rand() % 100 + 1);
    }
}
void FillRandParam(int MyArray[], int n) {
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

void FillIncParam(int MyArray[], int n) {
    for (int i = 0; i < n; i++) {
        MyArray[i] = i;
    }
}

void FillDec() {
    for (int i = 0; i < n; i++) {
        MyArray[i] = n - i;
    }
}

void FillDecParam(int MyArray[], int n) {
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
    Depth_max = 0;
}
void QuickSort(int MyArray[], int L, int R)
{
    Depth ++;
    if (Depth > Depth_max)
    {
        Depth_max = Depth;
    }
    int x = MyArray[L];
    int i = L, j = R;
    while (i < j)
    {
        while (MyArray[i] < x)
        {
            c++;
            i++;
        }
        while (MyArray[j] > x)
        {
            c++;
            j--;
        }
        if (i <= j)
        {
            c++;
            m += 3;
            int temp = MyArray[i];
            MyArray[i] = MyArray[j];
            MyArray[j] = temp;
            i++;
            j--;
        }
    }
    if (L < j)
    {
        c++;
        QuickSort(MyArray, L, j);
    }
    if (i < R)
    {
        c++;
        QuickSort(MyArray, i, R);
    }
    Depth --;
}
void QuickSortV2(int MyArray[], int L, int R)
{
    Depth ++;
    if (Depth > Depth_max)
    {
        Depth_max = Depth;
    }
    while (L < R)
    {
        //int x = MyArray[(L+R)/2];
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
    Depth --;
}

void znGet() {
    for (int i = 0; i < 5; i++) {
        n = 100 * (i + 1);
        MyArray = (int *) realloc(arr, sizeof(int) * n);
        Reset();
        FillRand();
        QuickSort(MyArray,0,n-1);
        Rand_Massiv[i] = m + c;
        Reset();
        FillDec();
        QuickSort(MyArray,0,n-1);
        DecreaseMassiv[i] = m + c;
        Reset();
        FillInc();
        QuickSort(MyArray,0,n-1);
        IncreaseMassiv[i] = m + c;
        Reset();
    }
}
void QuickSortTable()
{
    int MyArray[500];
    int QuickDec1, QuickDec2, QuickDec3, QuickDec4, QuickDec5;
    int QuickInc1, QuickInc2, QuickInc3, QuickInc4, QuickInc5;
    int QuickRand1, QuickRand2, QuickRand3, QuickRand4, QuickRand5;

    int Quick2Dec1, Quick2Dec2, Quick2Dec3, Quick2Dec4, Quick2Dec5;
    int Quick2Inc1, Quick2Inc2, Quick2Inc3, Quick2Inc4, Quick2Inc5;
    int Quick2Rand1, Quick2Rand2, Quick2Rand3, Quick2Rand4, Quick2Rand5;

    Reset(); FillDecParam(MyArray, 100); QuickSort(MyArray, 0, 100 - 1); QuickDec1 = Depth_max;
    Reset(); FillDecParam(MyArray, 200); QuickSort(MyArray, 0, 200 - 1); QuickDec2 = Depth_max;
    Reset(); FillDecParam(MyArray, 300); QuickSort(MyArray, 0, 300 - 1); QuickDec3 = Depth_max;
    Reset(); FillDecParam(MyArray, 400); QuickSort(MyArray, 0, 400 - 1); QuickDec4 = Depth_max;
    Reset(); FillDecParam(MyArray, 500); QuickSort(MyArray, 0, 500 - 1); QuickDec5 = Depth_max;

    Reset(); FillIncParam(MyArray, 100); QuickSort(MyArray, 0, 100 - 1); QuickInc1 = Depth_max;
    Reset(); FillIncParam(MyArray, 200); QuickSort(MyArray, 0, 200 - 1); QuickInc2 = Depth_max;
    Reset(); FillIncParam(MyArray, 300); QuickSort(MyArray, 0, 300 - 1); QuickInc3 = Depth_max;
    Reset(); FillIncParam(MyArray, 400); QuickSort(MyArray, 0, 400 - 1); QuickInc4 = Depth_max;
    Reset(); FillIncParam(MyArray, 500); QuickSort(MyArray, 0, 500 - 1); QuickInc5 = Depth_max;

    Reset(); FillRandParam(MyArray, 100); QuickSort(MyArray, 0, 100  -1); QuickRand1 = Depth_max;
    Reset(); FillRandParam(MyArray, 200); QuickSort(MyArray, 0, 200 - 1); QuickRand2 = Depth_max;
    Reset(); FillRandParam(MyArray, 300); QuickSort(MyArray, 0, 300 - 1); QuickRand3 = Depth_max;
    Reset(); FillRandParam(MyArray, 400); QuickSort(MyArray, 0, 400 - 1); QuickRand4 = Depth_max;
    Reset(); FillRandParam(MyArray, 500); QuickSort(MyArray, 0, 500 - 1); QuickRand5 = Depth_max;

    Reset(); FillDecParam(MyArray, 100); QuickSortV2(MyArray, 0, 100 - 1); Quick2Dec1 = Depth_max;
    Reset(); FillDecParam(MyArray, 200); QuickSortV2(MyArray, 0, 200 - 1); Quick2Dec2 = Depth_max;
    Reset(); FillDecParam(MyArray, 300); QuickSortV2(MyArray, 0, 300 - 1); Quick2Dec3 = Depth_max;
    Reset(); FillDecParam(MyArray, 400); QuickSortV2(MyArray, 0, 400 - 1); Quick2Dec4 = Depth_max;
    Reset(); FillDecParam(MyArray, 500); QuickSortV2(MyArray, 0, 500 - 1); Quick2Dec5 = Depth_max;

    Reset(); FillIncParam(MyArray, 100); QuickSortV2(MyArray, 0, 100 - 1); Quick2Inc1 = Depth_max;
    Reset(); FillIncParam(MyArray, 200); QuickSortV2(MyArray, 0, 200 - 1); Quick2Inc2 = Depth_max;
    Reset(); FillIncParam(MyArray, 300); QuickSortV2(MyArray, 0, 300 - 1); Quick2Inc3 = Depth_max;
    Reset(); FillIncParam(MyArray, 400); QuickSortV2(MyArray, 0, 400 - 1); Quick2Inc4 = Depth_max;
    Reset(); FillIncParam(MyArray, 500); QuickSortV2(MyArray, 0, 500 - 1); Quick2Inc5 = Depth_max;

    Reset(); FillRandParam(MyArray, 100); QuickSortV2(MyArray, 0, 100 - 1); Quick2Rand1 = Depth_max;
    Reset(); FillRandParam(MyArray, 200); QuickSortV2(MyArray, 0, 200 - 1); Quick2Rand2 = Depth_max;
    Reset(); FillRandParam(MyArray, 300); QuickSortV2(MyArray, 0, 300 - 1); Quick2Rand3 = Depth_max;
    Reset(); FillRandParam(MyArray, 400); QuickSortV2(MyArray, 0, 400 - 1); Quick2Rand4 = Depth_max;
    Reset(); FillRandParam(MyArray, 500); QuickSortV2(MyArray, 0, 500 - 1); Quick2Rand5 = Depth_max;
    //
    printf("\n");
    printf("DEPTH OF RECURSION\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    | QuickSort V1       	|  QuickSort V2      \n");
    printf("     | Dec   Rand   Inc  	|  Dec   Rand   Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n100_theory, QuickDec1, QuickRand1, QuickInc1,
           Quick2Dec1, Quick2Rand1, Quick2Inc1);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n200_theory, QuickDec2, QuickRand2, QuickInc2,
           Quick2Dec2, Quick2Rand2, Quick2Inc2);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n300_theory, QuickDec3, QuickRand3, QuickInc3,
           Quick2Dec3, Quick2Rand3, Quick2Inc3);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n400_theory, QuickDec4, QuickRand4, QuickInc4,
           Quick2Dec4, Quick2Rand4, Quick2Inc4);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n500_theory, QuickDec5, QuickRand5, QuickInc5,
           Quick2Dec5, Quick2Rand5, Quick2Inc5);
    printf("-----------------------------------------------------------------------------------------\n");
}


int main() {

    srand(time(NULL));
    int time;
    MyArray = (int *) malloc(sizeof(int) * n);
    printf("For inc unsorted array");
    FillInc();
    PrintMas();
    printf("\nTheory M: %d\n", 3 * (n - 1));
    printf("\nTheory C: %d\n", ((n*n+5*n+4)/2));
    printf("\nSeries Inc Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor inc sorted array");
    QuickSort(MyArray,0,n-1);
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries Inc sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    printf("\n------------------------------------");
    QuickSort(MyArray,0,n-1);
    Reset();

    printf("\nFor dec unsorted array");
    FillDec();
    PrintMas();
    printf("\nTheory M: %d\n", 3 * (n - 1));
    printf("\nTheory C: %d\n", ((n*n+5*n+4)/2));
    printf("\nSeries dec Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor dec sorted array");
    QuickSortV2(MyArray, 0, n-1);
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries dec sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    printf("\n------------------------------------");
    Reset();

    printf("\nFor random unsorted array");
    FillRand();
    PrintMas();
    printf("\nTheory M: %d\n", randTH);
    printf("\nTheory C: %d\n", randTH);
    printf("\nSeries random Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");

    printf("\nFor random sorted array");
    QuickSort(MyArray,0,n-1);
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries random sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    znGet();
    printf("\n--------------------------------------------------------------------------------------------------------------------");
	 printf("\nTABLE TRUDOEMKOSTI:\n");
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    | 				QuickSort (M(f)+C(f))      \n");
    printf("     |  	Dec   		Rand   		Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d|  	%d  		%d   		%d\n", n100_theory,
           DecreaseMassiv[0], Rand_Massiv[0], IncreaseMassiv[0]);
    printf("%-5d|  	%d  		%d   		%d\n", n200_theory,
           DecreaseMassiv[1], Rand_Massiv[1], IncreaseMassiv[1]);
    printf("%-5d|  	%d  		%d   		%d\n", n300_theory,
           DecreaseMassiv[2], Rand_Massiv[2], IncreaseMassiv[2]);
    printf("%-5d|  	%d  		%d   		%d\n", n400_theory,
           DecreaseMassiv[3], Rand_Massiv[3], IncreaseMassiv[3]);
    printf("%d  | 	        %d  	       %d            %d\n", n500_theory,
           DecreaseMassiv[4], Rand_Massiv[4], IncreaseMassiv[4]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\n");
    QuickSortTable();
    return 0;
}
