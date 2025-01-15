#include <iostream>
#include <ctime>
#include <math.h>
#include <ctime>

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

void Merge(Stack **a, int q, Stack **b, int r, Queue *c, int &C, int &M)
{
    while (q != 0 && r != 0)
    {
        C++;
        if ((*a)->data <= (*b)->data)
        {
            M+=2;
            c->tail->next = *a;
            c->tail = *a;
            *a = (*a)->next;
            q--;
        }
        else
        {
            M+=2;
            c->tail->next = *b;
            c->tail = *b;
            *b = (*b)->next;
            r--;
        }
    }
    while (q > 0)
    {
        M+=2;
        c->tail->next = *a;
        c->tail = *a;
        *a = (*a)->next;
        q--;
    }
    while (r > 0)
    {
        M+=2;
        c->tail->next = *b;
        c->tail = *b;
        *b = (*b)->next;
        r--;
    }
}
int Split(Stack *S, Stack **a, Stack **b, int &M)
{
    Stack *k, *p;
    *a = S;
    *b = S->next;
    int n = 1;
    k = *a;
    p = *b;
    while (p != NULL)
    {
        n++;
        k->next = p->next;
        k = p;
        p = p->next;
    }
    M += n;
    return n;
}

void MergeSort(Stack *(&S), Stack *(&tail), int &C, int &M)
{
    C = M = 0;
    Stack *a;
    Stack *b;
    int n = Split(S, &a, &b, M);
    int p = 1;
    int q, r;
    Queue c[2];
    while (p < n)
    {
        c[0].tail = (Stack *)&(c[0].head);
        c[1].tail = (Stack *)&(c[1].head);

        int i = 0;
        int m = n;
        while (m > 0)
        {
            if (m >= p)
                q = p;
            else
                q = m;

            m = m - q;

            if (m >= p)
                r = p;
            else
                r = m;

            m = m - r;
            Merge(&a, q, &b, r, &c[i], C, M);
            i = 1 - i;
        }
        a = c[0].head;
        b = c[1].head;
        p = 2 * p;
    }
    c[0].tail->next = nullptr;
    S = c[0].head;
    tail = c[0].tail;
}

void QueueFillInc(int n, Stack *(&head), Stack *(&tail))
{
    int i = 1;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = i;
    i++;
    do
    {
        p = new Stack;
        p->data = i;
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}

void QueueFillDec(int n, Stack *(&head), Stack *(&tail))
{
    int i = n;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = i;
    i--;
    do
    {
        p = new Stack;
        p->data = i;
        tail->next = p;
        tail = p;
        i--;

    } while (i > 0);
    tail->next = 0;
}
void CheckKolvo(Stack* head)
{
    Stack *p;
    p = head;
    int i = 0;
    while(p != nullptr)
    {
        p = p->next;
        i++;
    }
    cout << "Count elements - " << i << endl;
}
void QueueFillRand(int n, Stack *(&head), Stack *(&tail))
{
    srand(time(NULL));
    int i = 1;
    Stack *p;
    head = tail = new Stack;
    head->next = tail->next = 0;
    tail->data = rand() % (n);
    i++;
    do
    {
        p = new Stack;
        p->data = rand() % (n);
        tail->next = p;
        tail = p;
        i++;

    } while (i <= n);
    tail->next = 0;
}
void CheckSum(Stack* head){
    Stack *p;
    int chksum = 0;
    p = head;
    while (p != nullptr)
    {
        chksum += p->data;
        p = p->next;
    }
    cout << "Check Sum Spis: " << chksum << endl;
}

void RunNumber(Stack* head){
    Stack *p;
    Stack *p2;
    p = head;
    p2 = p->next;
    int count = 1;
    while (p2 != nullptr)
    {
        if (p->data > p2->data) count++;
        p = p->next;
        p2 = p2->next;
    }
    cout << "Run Number Spis: " << count << endl;
}

void PrintList(Stack *head, Stack *tail = NULL) {
    Stack *p;
    int q = 0;

    for (p = head; p; p = p->next) {
        cout << p->data << " ";
        q++;
    }
    if (tail != NULL) {
        cout << endl;
    }
    cout << endl;
    cout << endl;
}

void AddSomeList(Stack* &a, int q, Stack* &b, int r, Stack* &c)
{
    tail = nullptr;
    Stack *p = new Stack;

    tail = p;

    while(q != 0 && r != 0)
    {
        if (a->data <= b->data)
        {
            tail->next = a;
            a = a->next;
            q--;
        } else {
            tail->next = b;
            b = b->next;
            r--;
        }
        tail = tail->next;
    }
    while(q > 0)
    {
        tail ->next = a;
        a = a->next;
        q--;
        tail = tail->next;
    }
    while(r > 0)
    {
        tail->next = b;
        b = b->next;
        r--;
        tail = tail->next;
    }
    c = p->next;

    delete p;


}

void Reset(){
    M = 0;
    C = 0;
}

float timer(void (*Sort) (Stack *head, int n),Stack *head ,int n)
{
    clock_t start = clock();
    Sort(head,n);
    clock_t end = clock();
    return (float)(end - start) / CLOCKS_PER_SEC;

}

int main() {
    double n;
    Stack *head = NULL, *tail = NULL;
    Stack *a, *b;
    cout << "\n#2-3 SPLIT ELEMENTS and MERGE SERIES\n";
    QueueFillInc(8, head, tail);
    cout << "Initial list: ";
    PrintList(head);
    CheckKolvo(head);
    Split(head, &a, &b, M);
    cout << "\nFirst part after split: ";
    PrintList(a);
    CheckKolvo(head);
    RunNumber(a);
    CheckSum(a);
    cout << "\nSecond part after split: ";
    PrintList(b);
    CheckKolvo(head);
    RunNumber(b);
    CheckSum(b);
    cout << "\n";
    Stack *tmp;
    AddSomeList(a, 4, b, 4, tmp);
    PrintList(tmp);
    RunNumber(tmp);

    cout << "\n#4 MERGE SORT\n";
    Stack *sortMethod;
    cout << "Initial list: ";
    QueueFillRand(128, sortMethod, tail);
    n = 128;
    PrintList(sortMethod);
    MergeSort(sortMethod, tail, C, M);
    cout << "Sorted list: ";
    PrintList(sortMethod);
    cout << "Theory M: " << n * log2(n) << endl;
    cout << "Theory C: " << n * log2(n) << endl;

    cout << " " << endl;

    cout << "Fact M: " << M << endl;
    cout << "Fact C: " << C << endl;

    cout << "\n#5 MERGE SORT TABLE\n";

    QueueFillDec(100, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T100 = M + C;
    Reset();
    QueueFillRand(100, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T100_Rand = M + C;
    Reset();
    QueueFillInc(100, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T100_Inc = M + C;
    Reset();

    QueueFillDec(200, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T200 = M + C;
    Reset();
    QueueFillRand(200, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T200_Rand = M + C;
    Reset();
    QueueFillInc(200, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T200_Inc = M + C;
    Reset();

    QueueFillDec(300, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T300 = M + C;
    Reset();
    QueueFillRand(300, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T300_Rand = M + C;
    Reset();
    QueueFillInc(300, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T300_Inc = M + C;
    Reset();

    QueueFillDec(400, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T400 = M + C;
    Reset();
    QueueFillRand(400, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T400_Rand = M + C;
    Reset();
    QueueFillInc(400, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T400_Inc = M + C;
    Reset();

    QueueFillDec(500, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T500 = M + C;
    Reset();
    QueueFillRand(500, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T500_Rand = M + C;
    Reset();
    QueueFillInc(500, sortMethod, tail);
    MergeSort(sortMethod, tail, C, M);
    int T500_Inc = M + C;
    Reset();

    int theory100 = 100 * log2(100) + 100 * log2(100);
    int theory200 = 200 * log2(200) + 200 * log2(200);
    int theory300 = 300 * log2(300) + 300 * log2(300);
    int theory400 = 400 * log2(400) + 400 * log2(400);
    int theory500 = 500 * log2(500) + 500 * log2(500);

    printf("-----------------------------------------------------------------------------------------\n");
    printf("N    | M + C       	|  M(f) + C(f)     \n");
    printf("     | theory  	        |  Dec   Rand   Inc \n");
    printf("-----------------------------------------------------------------------------------------\n");
    printf("%-5d| %-5d	        | %-5d  %-5d   %-5d\n", n100_theory, theory100,
           T100, T100_Rand, T100_Inc);
    printf("%-5d| %-5d	        | %-5d  %-5d   %-5d\n", n200_theory, theory200,
           T200, T200_Rand, T200_Inc);
    printf("%-5d| %-5d	        | %-5d  %-5d   %-5d\n", n300_theory, theory300,
           T300, T300_Rand, T300_Inc);
    printf("%-5d| %-5d	        | %-5d  %-5d   %-5d\n", n400_theory, theory400,
           T400, T400_Rand, T400_Inc);
    printf("%-5d| %-5d	        | %-5d  %-5d   %-5d\n", n500_theory, theory500,
           T500, T500_Rand, T500_Inc);
    printf("-----------------------------------------------------------------------------------------\n");


    //printf("\nTime of working MergeSort n=%d:  %.6f  cek.", n, timer(MergeSort(sortMethod, tail, C, M)));
    return 0;
}