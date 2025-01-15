#include <stdio.h>
#include <stdlib.h>
#include <time.h>

int n = 400;

const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;

const int sumTHDEC100 = ((n100_theory * n100_theory - n100_theory)) / 2 + 2 * n100_theory - 2 +
                        (n100_theory * n100_theory - n100_theory) / 2;
const int sumTHDEC200 = ((n200_theory * n200_theory - n200_theory)) / 2 + 2 * n200_theory - 2 +
                        (n200_theory * n200_theory - n200_theory) / 2;
const int sumTHDEC300 = ((n300_theory * n300_theory - n300_theory)) / 2 + 2 * n300_theory - 2 +
                        (n300_theory * n300_theory - n300_theory) / 2;
const int sumTHDEC400 = ((n400_theory * n400_theory - n400_theory)) / 2 + 2 * n400_theory - 2 +
                        (n400_theory * n400_theory - n400_theory) / 2;
const int sumTHDEC500 = ((n500_theory * n500_theory - n500_theory)) / 2 + 2 * n500_theory - 2 +
                        (n500_theory * n500_theory - n500_theory) / 2;

const int sumTHRAND100 =
        ((n100_theory * n100_theory - n100_theory) / 4 + n - 1) + (n100_theory * n100_theory - n100_theory) / 4;
const int sumTHRAND200 =
        ((n200_theory * n200_theory - n200_theory) / 4 + n - 1) + (n200_theory * n200_theory - n200_theory) / 4;
const int sumTHRAND300 =
        ((n300_theory * n300_theory - n300_theory) / 4 + n - 1) + (n300_theory * n300_theory - n300_theory) / 4;
const int sumTHRAND400 =
        ((n400_theory * n400_theory - n400_theory) / 4 + n - 1) + (n400_theory * n400_theory - n400_theory) / 4;
const int sumTHRAND500 =
        ((n500_theory * n500_theory - n500_theory) / 4 + n - 1) + (n500_theory * n500_theory - n500_theory) / 4;

const int sumTHINC100 = (2 * (n100_theory - 1) + n100_theory - 1);
const int sumTHINC200 = (2 * (n200_theory - 1) + n200_theory - 1);
const int sumTHINC300 = (2 * (n300_theory - 1) + n300_theory - 1);
const int sumTHINC400 = (2 * (n400_theory - 1) + n400_theory - 1);
const int sumTHINC500 = (2 * (n500_theory - 1) + n500_theory - 1);

int *arr = NULL;
int *MyArray = NULL;
int Rand_Massiv[5], IncreaseMassiv[5], DecreaseMassiv[5];
int Rand_MassivFourSelect[5], Rand_MassivFourBubble[5], Rand_MassivFourShaker[5], Rand_MassivFourInsert[5];
int m = 0;
int c = 0;

void FillRand() {
    for (int i = 0; i < n; i++) {
        MyArray[i] = (rand() % 1000 + 1);
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

/*��� 4 ������� (��������� ����������� ��������� ������)*/

void SelectSort() {
    for (int i = 0; i < n - 1; i++) {
        int count = i;
        for (int j = count + 1; j < n; j++) {
            c++;
            if (MyArray[j] < MyArray[count]) {
                count = j;
            }
        }
        if (i != count) {
            m += 3;
            int temp = MyArray[count];
            MyArray[count] = MyArray[i];
            MyArray[i] = temp;
        }
    }
}

void BubbleSort() {
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

void ShakerSort() {
    int left = 0, right = n - 1, k = 0;
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
                m += 3;
                k = i;
            }
        }
        right = k;

        for (int i = right; i > left; i--) {
            c++;
            if (MyArray[i] < MyArray[i - 1]) {
                int tmp = MyArray[i];
                MyArray[i] = MyArray[i - 1];
                MyArray[i - 1] = tmp;
                flag = 1;
                m += 3;
                k = i;
            }
        }
        left = k;
    }
}


void insertSort() {
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
        m += 2;
        MyArray[j + 1] = flag;
    }
}

void znGet() {
    for (int i = 0; i < 5; i++) {
        n = 100 * (i + 1);
        MyArray = (int *) realloc(arr, sizeof(int) * n);
        Reset();
        FillRand();
        insertSort();
        Rand_Massiv[i] = m + c;
        Reset();
        FillDec();
        insertSort();
        DecreaseMassiv[i] = m + c;
        Reset();
        FillInc();
        insertSort();
        IncreaseMassiv[i] = m + c;
        Reset();
    }
}


void znGetFour() {
    for (int i = 0; i < 5; i++) {
        n = 100 * (i + 1);
        MyArray = (int *) realloc(arr, sizeof(int) * n);
        Reset();
        FillRand();
        SelectSort();
        Rand_MassivFourSelect[i] = m + c;
        Reset();

        FillRand();
        BubbleSort();
        Rand_MassivFourBubble[i] = m + c;
        Reset();

        Reset();
        FillRand();
        ShakerSort();
        Rand_MassivFourShaker[i] = m + c;
        Reset();

        FillRand();
        insertSort();
        Rand_MassivFourInsert[i] = m + c;
        Reset();
    }
}

int main() {
    srand(time(NULL));
    int time;
    MyArray = (int *) malloc(sizeof(int) * n);

    printf("For inc unsorted array");
    FillInc();
    PrintMas();
    printf("\nTheory M: %d\n", 2 * (n - 1));
    printf("\nTheory C: %d\n", (n - 1));
    printf("\nSeries Inc Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor inc sorted array");
    insertSort();
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries Inc sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    printf("\n------------------------------------");
    insertSort();
    Reset();

    printf("\nFor dec unsorted array");
    FillDec();
    PrintMas();
    printf("\nTheory M: %d\n", ((n * n - n)) / 2 + 2 * n - 2);
    printf("\nTheory C: %d\n", (n * n - n) / 2);
    printf("\nSeries dec Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor dec sorted array");
    insertSort();
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
    printf("\nTheory M: %d\n", ((n * n - n) / 4) + n - 1);
    printf("\nTheory C: %d\n", (n * n - n) / 2);
    printf("\nSeries random Unsorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    printf("\n------------------------------------");


    printf("\nFor random sorted array");
    insertSort();
    PrintMas();
    printf("\nFact M: %d \n", m);
    printf("Fact C: %d\n", c);
    printf("\nSeries random sorted Array: %d", RunNumber());
    printf("\nSumma: %d", CheckSum());
    time = m + c;
    printf("\nTime:%d", time);
    printf("\n--------------------------------------------------------------------------------------------------------------------");
    znGet();
    printf("\n");
    printf("TABLE TRUDOEMKOSTI:\n");
    printf("\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    | M + C teor.       	|  M + C fact.      \n");
    printf("     | Dec   Rand   Inc  	|  Dec   Rand   Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n100_theory, sumTHDEC100, sumTHRAND100, sumTHINC100,
           DecreaseMassiv[0], Rand_Massiv[0], IncreaseMassiv[0]);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n200_theory, sumTHDEC200, sumTHRAND200, sumTHINC200,
           DecreaseMassiv[1], Rand_Massiv[1], IncreaseMassiv[1]);
    printf("%-5d| %-5d  %-5d  %-5d 	| %-5d  %-5d   %-5d\n", n300_theory, sumTHDEC300, sumTHRAND300, sumTHINC300,
           DecreaseMassiv[2], Rand_Massiv[2], IncreaseMassiv[2]);
    printf("%-5d| %-5d %-5d  %-5d 	| %-5d %-5d   %-5d\n", n400_theory, sumTHDEC400, sumTHRAND400, sumTHINC400,
           DecreaseMassiv[3], Rand_Massiv[3], IncreaseMassiv[3]);
    printf("%-5d| %-5d %-5d %-5d 	| %-5d %-5d  %-5d\n", n500_theory, sumTHDEC500, sumTHRAND500, sumTHINC500,
           DecreaseMassiv[4], Rand_Massiv[4], IncreaseMassiv[4]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("\n");
    znGetFour();
    printf("TABLE TRUDOEMKOSTI SORT METHODS:\n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4s | %-8s | %-7s | %-7s | %-7s |\n", "N", "Select", "Bubble", "Shaker", "Insert");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-8d | %-7d | %-7d | %-7d |\n", n100_theory, Rand_MassivFourSelect[0], Rand_MassivFourBubble[0],
           Rand_MassivFourShaker[0], Rand_MassivFourInsert[0]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-8d | %-7d | %-7d | %-7d |\n", n200_theory, Rand_MassivFourSelect[1], Rand_MassivFourBubble[1],
           Rand_MassivFourShaker[1], Rand_MassivFourInsert[1]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-8d | %-7d | %-7d | %-7d |\n", n300_theory, Rand_MassivFourSelect[2], Rand_MassivFourBubble[2],
           Rand_MassivFourShaker[2], Rand_MassivFourInsert[2]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-8d | %-7d | %-7d | %-7d |\n", n400_theory, Rand_MassivFourSelect[3], Rand_MassivFourBubble[3],
           Rand_MassivFourShaker[3], Rand_MassivFourInsert[3]);
    printf("-----------------------------------------------------------------------------------------\n");
    printf("| %-4d | %-8d | %-7d | %-7d | %-7d |\n", n500_theory, Rand_MassivFourSelect[4], Rand_MassivFourBubble[4],
           Rand_MassivFourShaker[4], Rand_MassivFourInsert[4]);
    printf("-----------------------------------------------------------------------------------------\n");

    return 0;
}
