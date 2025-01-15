#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>

int n=500;
const int n100_theory = 100;
const int n200_theory = 200;
const int n300_theory = 300;
const int n400_theory = 400;
const int n500_theory = 500;

const int sumTHDEC100 = 0;
const int sumTHDEC200 = 0;
const int sumTHDEC300 = 0;
const int sumTHDEC400 = 0;
const int sumTHDEC500 = 0;

const int sumTHRAND100 = 0;
const int sumTHRAND200 = 0;
const int sumTHRAND300 = 0;
const int sumTHRAND400 = 0;
const int sumTHRAND500 = 0;

const int sumTHINC100 = 0;
const int sumTHINC200 = 0;
const int sumTHINC300 = 0;
const int sumTHINC400 = 0;
const int sumTHINC500 = 0;


int* arr = NULL;
int* MyArray=NULL;
int Rand_Massiv[5],IncreaseMassiv[5],DecreaseMassiv[5];
int Rand_MassivFourSelect[5], Rand_MassivFourBubble[5], Rand_MassivFourShaker[5], Rand_MassivInsert[5], Rand_MassivShell[5];
int Rand_MassivKnut[5], Rand_MassivKhibard[5];
int** Shag1=NULL,Shag2=NULL;
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

void Reset(){
m=0;
c=0;
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
        m+=2;
        MyArray[j + 1] = flag;
    }
}
void ShellSort() {
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

void Knut()
{
    int step = 1;
    while (step < log2(n)-1)
    {
        step = step * 2 + 1;
    }

    while (step > 0)
    {
        for (int i = step; i < n; i += 1)
        {
            int temp = MyArray[i];
            int j;
            for (j = i; j >= step; j -= step)
            {
                c++;
                if (MyArray[j - step] > temp)
                {
                    MyArray[j] = MyArray[j - step];
                    m++;
                }
                else
                {
                    break;
                }
            }
            MyArray[j] = temp;
            m += 2;
        }
        step = (step - 1) / 2;
    }
}
/*
void ShellSortKhibard() {
    int h = 1;
    int temp, i, j, k;
    while (h < n) {
        h = 2 * h + 1;
    }
    h = (h - 1) / 2;
    while (h > 0) {
        for (i = h; i < n; i++) {
            temp = MyArray[i];
            for (j = i; j >= h && MyArray[j - h] > temp; j -= h) {
                MyArray[j] = MyArray[j - h];
            }
            MyArray[j] = temp;
        }
        h = (h - 1) / 2;
    }
}
*/

void ShellSortKhibard()
{
    int steps[] = {1, 4, 10, 23, 57, 132, 301, 701, 1750};
	
    for(int gapId = sizeof(steps)/sizeof(steps[0]) - 1; gapId >= 0; gapId--)
    {
        int step = steps[gapId];
        for(int i = step; i < n; i += 1)
        {
            int temp = MyArray[i];
            int j;
            for(j = i; j >= step; j -= step)
            {
                c++;
                if(MyArray[j - step] > temp)
                {
                    MyArray[j] = MyArray[j - step];
                    m++;
                }
                else
                {
                    break;
                }
            }
            MyArray[j] = temp;
            m += 2;
        }
    }
}

void znGetShell() {
for(int i = 0; i < 5;i++) {
n = 100 * (i + 1);
MyArray=(int*)realloc(arr,sizeof(int)*n);
Reset();
FillRand();
ShellSort();
Rand_MassivShell[i] = m+c;
Reset();
}
}

void znGetInsert() {
for(int i = 0; i < 5;i++) {
n = 100 * (i + 1);
MyArray=(int*)realloc(arr,sizeof(int)*n);
Reset();
FillRand();
insertSort();
Rand_MassivInsert[i] = m+c;
Reset();
}
}
void ZnGetKnut(){
	Shag1=(int**)malloc(sizeof(int*)*5);
	for(int i = 0; i<5; i++){
		n = 100 * (i+1);
		int* uf;
		uf=(int*)malloc((log2(n)-1)*sizeof(int));
		uf[0]=1;
		for(int j=0;j<log2(n)-1;j++) {
			uf[j]=uf[j-1]*2+1;
		}
		Shag1[i]=uf;
		MyArray = (int*)realloc(arr,sizeof(int)*n);
		Reset();
		FillRand();
		Knut();
		Rand_MassivKnut[i] = m+c;
		Reset();
	}
}

void ZnGetKhibard(){
	//Shag2=(int**)malloc(sizeof(int*)*5);
	for(int i = 0; i<5; i++){
		n = 100 * (i+1);
		int shags[]={1, 4, 10, 23, 57, 132, 301, 701, 1750};
		free(MyArray);
		MyArray = (int*)malloc(sizeof(int)*n);
		int* uf=(int*)malloc(sizeof(shags)/sizeof(shags[0])*sizeof(int));
		uf[0]=1;
		for(int j=0;j<sizeof(shags)/sizeof(shags[0]);j++) {
			uf[j]=shags[j];
		}
		Shag1[i]=uf;
		Reset();
		FillRand();
		ShellSortKhibard();
		Rand_MassivKhibard[i] = m+c;
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
printf("\nTheory M: %d\n", 2*(n-1));
printf("\nTheory C: %d\n", (n-1));
printf("\nSeries Inc Unsorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
printf("\n------------------------------------");



printf("\nFor inc sorted array");
ShellSort();
PrintMas();
printf("\nFact M: %d \n", m);
printf("Fact C: %d\n", c);
printf("\nSeries Inc sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
printf("\n------------------------------------");
ShellSort();
Reset();

printf("\nFor dec unsorted array");
FillDec();
PrintMas();
printf("\nTheory M: %d\n", ((n*n-n))/2 +2*n-2);
printf("\nTheory C: %d\n", (n * n - n) / 2);
printf("\nSeries dec Unsorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
printf("\n------------------------------------");



printf("\nFor dec sorted array");
ShellSort();
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
printf("\nTheory M: %d\n", ((n*n-n)/4) +n -1);
printf("\nTheory C: %d\n", (n * n - n) / 2);
printf("\nSeries random Unsorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
printf("\n------------------------------------");


printf("\nFor random sorted array");
ZnGetKnut();
znGetInsert();
znGetShell();
ZnGetKhibard();
PrintMas();
printf("\nFact M: %d \n", m);
printf("Fact C: %d\n", c);
printf("\nSeries random sorted Array: %d", RunNumber());
printf("\nSumma: %d", CheckSum());
time = m + c;
printf("\nTime:%d",time);
printf("\n-----------------------------------------------------------------------------------------------------");
printf("\n");
printf("TABLE TRUDOEMKOSTI SHELLA	:\n");
printf("\n");
printf("-----------------------------------------------------------------------------------------\n");
printf("n    | h1 ... hm po formule     |  Insert M(f)+C(f)	|   Shell M(f)+C(f)    | \n");
printf("     | D.Knuta  				|		    		|                      |\n");
printf("-----------------------------------------------------------------------------------------\n");
printf("%-5d|",n100_theory);
for(int i=0;i<log2(100)-1;i++) {
	printf("%d,",Shag1[0][i]);
}
printf("| %-5d 		|		  %-5d|\n", Rand_MassivInsert[0], Rand_MassivShell[0]);
printf("\n%-5d|",n200_theory);
for(int i=0;i<log2(200)-1;i++) {
	printf("%d,",Shag1[1][i]);
}
printf("| %-5d 		|		  %-5d|\n", Rand_MassivInsert[1], Rand_MassivShell[1]);
printf("\n%-5d|",n300_theory);
for(int i=0;i<log2(300)-1;i++) {
	printf("%d,",Shag1[2][i]);
}
printf("| %-5d 		|		  %-5d|\n", Rand_MassivInsert[2], Rand_MassivShell[2]);
printf("\n%-5d|",n400_theory);
for(int i=0;i<log2(400)-1;i++) {
	printf("%d,",Shag1[3][i]);
}
printf("| %-5d 		|		  %-5d|\n", Rand_MassivInsert[3], Rand_MassivShell[3]);
printf("\n%-5d|",n500_theory);
for(int i=0;i<log2(500)-1;i++) {
	printf("%d,",Shag1[4][i]);
}
printf("| %-5d 		|		  %-5d|\n", Rand_MassivInsert[4], Rand_MassivShell[4]);
//printf("%-5d| %-5d  			| %-5d  		| 		  %-5d|		      \n", n200_theory, Rand_MassivKnut[1], Rand_MassivInsert[1], Rand_MassivShell[1]);
//printf("%-5d| %-5d 			| %-5d 		|		  %-5d|\n", n300_theory, Rand_MassivKnut[2], Rand_MassivInsert[2], Rand_MassivShell[2]);
//printf("%-5d| %-5d 			| %-5d 		|		  %-5d|\n", n400_theory, Rand_MassivKnut[3], Rand_MassivInsert[3], Rand_MassivShell[3]);
//printf("%-5d| %-5d 			| %-5d 		|		  %-5d|\n", n500_theory, Rand_MassivKnut[4], Rand_MassivInsert[4], Rand_MassivShell[4]);
printf("-----------------------------------------------------------------------------------------\n");
printf("\n");


printf("DISCOVERING TRUDOEMKOSTI SHELL METHOD	:\n");
printf("\n");
printf("-----------------------------------------------------------------------------------------------------------------------------\n");
printf("n    | h1 ... hm po formule     |  Shell M(f)+C(f)      |   Khibard M(f)+C(f)  | Shell M(f)+C(f)	 |\n");
printf("     | D.Knuta  		|		    	|                      |			 |				    |\n");
printf("------------------------------------------------------------------------------------------------------------------------\n");
printf("%-5d| %-5d 			| %-5d 		|		  %-5d|			%-5d|\n", n100_theory, Rand_MassivKnut[0], Rand_MassivShell[0],Rand_MassivKhibard[0],Rand_MassivShell[0]);
printf("%-5d| %-5d  			| %-5d  		| 		  %-5d|		     	%-5d|\n", n200_theory, Rand_MassivKnut[1], Rand_MassivShell[1],Rand_MassivKhibard[1], Rand_MassivShell[1]);
printf("%-5d| %-5d 			| %-5d 		|		  %-5d|			%-5d|\n", n300_theory, Rand_MassivKnut[2], Rand_MassivShell[2],Rand_MassivKhibard[2],Rand_MassivShell[2]);
printf("%-5d| %-5d 			| %-5d 		|		  %-5d|			%-5d|\n", n400_theory, Rand_MassivKnut[3], Rand_MassivShell[3],Rand_MassivKhibard[3],Rand_MassivShell[3]);
printf("%-5d| %-5d 			| %-5d 		|		  %-5d|			%-5d|\n", n500_theory, Rand_MassivKnut[4], Rand_MassivShell[4],Rand_MassivKhibard[4],Rand_MassivShell[4]);
printf("-------------------------------------------------------------------------------------------------------------------------\n");
printf("\n");
return 0;
}
