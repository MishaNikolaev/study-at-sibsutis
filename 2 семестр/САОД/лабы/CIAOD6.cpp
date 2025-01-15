#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
int Inc_MassivSearch[10], Inc2_MassivSearch[10], IncAll1_MassivSearch[10],IncAll2_MassivSearch[10] ;
int n = 100;
int *MyArray = NULL;
int *arr = NULL;
int m = 0, c = 0;
int c_theory1, c_theory2;
const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;
const int n600_theory = 600;
const int n700_theory = 700;
const int n800_theory = 800;
const int n900_theory = 900;
const int n1000_theory = 10000;

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

int BSearch1(int MyArray[], int n, int key) {
    int L = 0;
    int R = n - 1;
    c = 0;

    while (L <= R) {
        int m = (L + R) / 2;
        c+=2;
        if (MyArray[m] == key)
            return m;
        else if (MyArray[m] < key) {
            L = m + 1;}
        else {
            R = m - 1;}
    }

    return -1;
}
int BSearchAll1(int MyArray[], int n, int key) {
    int L = 0;
    int R = n - 1;
    int found = -1;
    c = 0;

    while (L <= R) {
        int m = (L + R) / 2;
        c++;
        if (MyArray[m] == key) {
            found = m;
            int left = m - 1;
            while(left >= L && MyArray[left] == key) {
                found = left;
                left--;
                c++;
            }
            int right = m + 1;
            while(right <= R && MyArray[right] == key) {
                found = right;
                right++;
                c++;
            }
            break;
        } else if (MyArray[m] < key) {
            c++;
            L = m + 1;}
        else {c++;
            R = m - 1;}
    }

    return found;
}

int BSearch2(int MyArray[], int n, int key) {
    int L = 0;
    int R = n - 1;
    int m;
    c = 0;

    while (L < R) {
        m = L + (R - L) / 2;
        c++;
        if (MyArray[m] < key)
            L = m + 1;
        else {
            R = m;}
    }
    c++;
    if (MyArray[L] == key)
        return L;

    return -1;
}

int BSearchAll2(int MyArray[], int n, int key) {
    int L = 0;
    int R = n;
    int found = -1;

    while (L < R) {
        int m = (L + R) / 2;
        c++;
        if (MyArray[m] < key) {
            L = m + 1;
        } else {
            R = m;
        }
    }

    if (L < n && MyArray[L] == key) {
        found = L;
        int i = 1;
        while ((L + i) < n && MyArray[L + i] == key) {
            i++;
            c++;
        }
    }
    c++;
    return found;
}


void ReallocTableBSearch1() {
    int key;
    scanf("%d",&key);
    for(int i = 0; i < 10;i++) {
        n = 100 * (i + 1);
        MyArray=(int*)realloc(arr,sizeof(int)*n);
        Reset();
        FillInc();
        BSearch1(MyArray, n, key);
        Inc_MassivSearch[i] = c;
        Reset();
    }
}
void ReallocTableBSearch2(){
    int key;
    scanf("%d",&key);
    for(int i = 0; i < 10;i++) {
        n = 100 * (i + 1);
        MyArray=(int*)realloc(arr,sizeof(int)*n);
        Reset();
        FillInc();
        BSearch2(MyArray, n, key);
        Inc2_MassivSearch[i] = c;
        Reset();
    }
}

void ReallocTableBSearch1All() {

    int key;
    scanf("%d",&key);
    for(int i = 0; i < 10;i++) {
        n = 100 * (i + 1);
        MyArray=(int*)realloc(arr,sizeof(int)*n);
        Reset();
        FillInc();
        BSearchAll1(MyArray, n, key);
        IncAll1_MassivSearch[i] = c;
        Reset();
    }
}

void ReallocTableBSearch2All() {
    int key;
    scanf("%d",&key);
    for(int i = 0; i < 10;i++) {
        n = 100 * (i + 1);
        MyArray=(int*)realloc(arr,sizeof(int)*n);
        Reset();
        FillInc();
        BSearchAll2(MyArray, n, key);
        IncAll2_MassivSearch[i] = c;
        Reset();
    }
}

int main() {
    MyArray = (int *) malloc(sizeof(int) * n);
    if (MyArray == NULL) {
        perror("Malloc failed");
        return EXIT_FAILURE;
    }
    printf("BSearch #1");
    int key;
    c_theory1 = 2 * (log2(n));
    c_theory2 = log2(n);

    printf("\nFor random sorted array\n");
    FillRand();
    SelectSort();
    Reset();
    PrintMas();

    int firstElement = 12;
    int lastElement = MyArray[n - 1];
    int NetElement = 1000;


    int resultFirstEl = BSearch1(MyArray, n, firstElement);
    if (resultFirstEl != -1) {
        printf("First element %d is found %d on position\n", firstElement, resultFirstEl);
    } else {
        printf("First element %d not found\n", firstElement);
    }

    int resultLastEl = BSearch1(MyArray, n, lastElement);
    if (resultLastEl != -1) {
        printf("Last element %d is found %d on position\n", lastElement, resultLastEl);
    } else {
        printf("Last element %d not found\n", lastElement);
    }
    int resultNoEl = BSearch1(MyArray, n, NetElement);
    if (resultNoEl != -1) {
        printf("Not in array element %d is found %d on position\n", NetElement, resultNoEl);
    } else {
        printf("Not in array element %d not found\n", NetElement);
    }
    printf("\nTheory C: %d\n", c_theory1);
    Reset();
    BSearch1(MyArray,n,MyArray[0]);
    printf("Fact C for first element: %d\n", c);
    Reset();
    BSearch1(MyArray,n,MyArray[n-1]);
    printf("Fact C for last element: %d\n", c);
    Reset();
    BSearch1(MyArray,n,n+1);
    printf("Fact C for missing element: %d\n", c);
    printf("\n------------------------------------\n");


    printf("BSearch #2");

    printf("\nFor random sorted array\n");
    SelectSort();
    Reset();
    PrintMas();
    /*printf("Input element for search: ");
    scanf("%d", &key);
    int result2 = BSearch2(MyArray, n, key);
    if (result != -1) {
        printf("Element %d is found %d on position\n", key, result2);
    } else {
        printf("Element %d not found\n", key);
    }*/

    int resultFirstEl2 = BSearch2(MyArray, n, firstElement);
    if (resultFirstEl2 != -1) {
        printf("First element %d is found %d on position\n", firstElement, resultFirstEl2);
    } else {
        printf("First element %d not found\n", firstElement);
    }

    int resultLastEl2 = BSearch2(MyArray, n, lastElement);
    if (resultLastEl != -1) {
        printf("Last element %d is found %d on position\n", lastElement, resultLastEl2);
    } else {
        printf("Last element %d not found\n", lastElement);
    }
    int resultNoEl2 = BSearch2(MyArray, n, NetElement);
    if (resultNoEl2 != -1) {
        printf("Not in array element %d is found %d on position\n", NetElement, resultNoEl2);
    } else {
        printf("Not in array element %d not found\n", NetElement);
    }

    printf("\nTheory C: %d\n", c_theory2);
    Reset();
    BSearch2(MyArray,n,MyArray[0]);
    printf("Fact C for first element: %d\n", c);
    Reset();
    BSearch2(MyArray,n,MyArray[n-1]);
    printf("Fact C for last element: %d\n", c);
    Reset();
    BSearch2(MyArray,n,n+1);
    printf("Fact C for missing element: %d\n", c);
    printf("\n------------------------------------\n");

    ReallocTableBSearch1();
    ReallocTableBSearch2();
    ReallocTableBSearch1All();
    ReallocTableBSearch2All();
    printf("\n-------------------------------------------------------------------------------");
    printf("\nTRYDOEMKOCTb");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n|         N           |     C(f) BSearch1        |        C(f) BSearch2       |");
    printf("\n|---------------------|--------------------------|----------------------------|");
    printf("\n|         %d         |           %d              |            %d               |",n100_theory, Inc_MassivSearch[0],Inc2_MassivSearch[0]);
    printf("\n|         %d         |           %d              |            %d               |",n200_theory, Inc_MassivSearch[1],Inc2_MassivSearch[1]);
    printf("\n|         %d         |           %d              |            %d               |",n300_theory, Inc_MassivSearch[2],Inc2_MassivSearch[2]);
    printf("\n|         %d         |           %d              |            %d               |",n400_theory, Inc_MassivSearch[3],Inc2_MassivSearch[3]);
    printf("\n|         %d         |           %d              |            %d               |",n500_theory, Inc_MassivSearch[4],Inc2_MassivSearch[4]);
    printf("\n|         %d         |           %d              |            %d              |",n600_theory,Inc_MassivSearch[5],Inc2_MassivSearch[5]);
    printf("\n|         %d         |           %d              |            %d              |",n700_theory,Inc_MassivSearch[6],Inc2_MassivSearch[6]);
    printf("\n|         %d         |           %d              |            %d              |",n800_theory,Inc_MassivSearch[7],Inc2_MassivSearch[7]);
    printf("\n|         %d         |           %d              |            %d              |",n900_theory,Inc_MassivSearch[8],Inc2_MassivSearch[8]);
    printf("\n|         %d        |           %d              |            %d              |",n1000_theory,Inc_MassivSearch[9],Inc2_MassivSearch[9]);
    printf("\n-------------------------------------------------------------------------------");


    printf("\n-------------------------------------------------------------------------------");
    printf("\nTRYDOEMKOCTb BCEX ELEMENTOB");
    printf("\n-------------------------------------------------------------------------------");
    printf("\n|         N           |  C(f) BSearch1All        |     C(f) BSearch2All       |");
    printf("\n|---------------------|--------------------------|----------------------------|");
    printf("\n|         %d         |           %d              |            %d               |",n100_theory, IncAll1_MassivSearch[0],IncAll2_MassivSearch[0]);
    printf("\n|         %d         |           %d              |            %d               |",n200_theory, IncAll1_MassivSearch[1],IncAll2_MassivSearch[1]);
    printf("\n|         %d         |           %d              |            %d               |",n300_theory, IncAll1_MassivSearch[2],IncAll2_MassivSearch[2]);
    printf("\n|         %d         |           %d              |            %d               |",n400_theory, IncAll1_MassivSearch[3],IncAll2_MassivSearch[3]);
    printf("\n|         %d         |           %d              |            %d               |",n500_theory, IncAll1_MassivSearch[4],IncAll2_MassivSearch[4]);
    printf("\n|         %d         |           %d              |            %d               |",n600_theory,IncAll1_MassivSearch[5],IncAll2_MassivSearch[5]);
    printf("\n|         %d         |           %d              |            %d               |",n700_theory,IncAll1_MassivSearch[6],IncAll2_MassivSearch[6]);
    printf("\n|         %d         |           %d              |            %d               |",n800_theory,IncAll1_MassivSearch[7],IncAll2_MassivSearch[7]);
    printf("\n|         %d         |           %d              |            %d               |",n900_theory,IncAll1_MassivSearch[8],IncAll2_MassivSearch[8]);
    printf("\n|         %d        |           %d              |            %d               |",n1000_theory,IncAll1_MassivSearch[9],IncAll2_MassivSearch[9]);
    printf("\n-------------------------------------------------------------------------------");

    free(MyArray);
    return 0;
}