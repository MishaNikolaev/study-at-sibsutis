#include <iostream>
#include <ctime>
#include <cstdlib>

using namespace std;

const int n = 10;

struct Stack {
    int data;
    Stack* next;
} *p, *head = nullptr;

struct Que {
    int data;
    Que* next;
} *qhead = nullptr, *qtail = nullptr, *q;

void push(int data) {
    p = new Stack;
    p->data = data;
    p->next = head;
    head = p;
}

void enqueue(int data) {
    q = new Que;
    q->data = data;
    q->next = nullptr;
    qtail->next = q;
    qtail = q;
}

void FillIncStack(int n) {
    for (int i = n - 1; i >= 0; i--) {
        push(i);
    }
}

void FillIncQueue(int n) {
    q = new Que;
    q -> data = 0;
    q -> next = nullptr;
    qtail = qhead = q;
    for (int i = 1; i < n; i++) {
        enqueue(i);
    }
}

void FillDecStack(int n) {
    for (int i = 0; i < n; i++) {
        push(i);
    }
}

void FillIncStackTask(int n) {
    for (int i = n - 1; i >= 1; i--) {
        push(i);
    }
}

void FillDecQueue(int n) {
    q = new Que;
    q -> data = n - 1;
    q -> next = nullptr;
    qtail = qhead = q;
    for (int i = n - 2; i >= 0; i--) {
        enqueue(i);
    }
}

void FillIncQueueInitialization(int n) { //////
  qtail = (Que*)&head;
    for (int i = 1; i < n; i++) {
        enqueue(i);
    }
}

void FillRandStack(int n) {
    srand(time(NULL));
    for (int i = 0; i < n; i++) {
        push(rand() % n);
    }
}

void FillRandQueue(int n) {
    srand(time(NULL));
    q = new Que;
    q -> data = rand()%n;
    q -> next = nullptr;
    qtail = qhead = q;
    for (int i = 1; i < n; i++) {
        enqueue(rand() % n);
    }
}

void PrintStack() {
    if (head == nullptr) {
        cout << "Stack is empty";
        return;
    }
    p = head;
    while (p != nullptr) {
        cout << p->data << " ";
        p = p->next;
    }
    cout << endl;
}

void PrintQueue() {
    if (qhead == nullptr || qtail == nullptr) {
        cout << "Queue is empty" << endl;
        return;
    }
    Que* temp = qhead;
    while (temp != nullptr) {
        cout << temp->data << " ";
        temp = temp->next;
    }
    cout << endl;
}

int CheckSumList(Stack* listHead) {
    int checksum = 0;
    Stack* pList = listHead;

    while (pList != nullptr) {
        checksum += pList->data;
        pList = pList->next;
    }
    return checksum;
}

int RunNumber(Stack* listHead) {
    int series = 0;
    Stack* pList = listHead;

    while (pList != nullptr) {
        Stack* next = pList->next;
        while (next != nullptr && next->data >= pList->data) {
            pList = next;
            next = next->next;
        }
        series++;

        pList = next;
    }

    return series;
}

void Reset() {
    p = head;
    while (p != nullptr) {
        p->data = 0;
        p = p->next;
    }
    head = nullptr;
}

void ResetQueue() {
    Que* temp = qhead;
    while (temp != nullptr) {
        temp->data = 0;
        temp = temp->next;
    }
    qhead = qtail = nullptr;
}

void DeleteAllElemenets() {
    while(head) {
        Stack *temp = head;
        head = head->next;
        free(temp);
    }

}

void PrintListForward(Stack* p) {
    if (p == nullptr) {
        return;
    }

    cout << p->data << " ";
    PrintListForward(p->next);
}

void PrintListBackward(Stack* p) {
    if (p == nullptr) {
        return;
    }

    PrintListBackward(p->next);
    cout << p->data << " ";
}
int main() {

    cout << "#1 STACK\n";
    cout << "\nFilling stack with decreasing numbers\n";
    FillDecStack(n);
    PrintStack();
    Reset();

    cout << "\nFilling stack with increasing numbers\n";
    FillIncStack(n);
    PrintStack();
    Reset();

    cout << "\nFilling stack with random numbers\n";
    FillRandStack(n);
    PrintStack();
    Reset();

    cout << "\n#2 QUEUE\n";

    cout << "Filling queue with increasing numbers" << endl;
    FillIncQueue(n);
    PrintQueue();
    ResetQueue();

    cout << "\nFilling queue with decreasing numbers" << endl;
    FillDecQueue(n);
    PrintQueue();
    ResetQueue();

    cout << "\nFilling queue with random numbers" << endl;
    FillRandQueue(n);
    PrintQueue();
    ResetQueue();

    cout << "\n#3 LIST\n";
    FillRandStack(n);
    PrintStack();
    printf("Series: %d\n",RunNumber(head));
    printf("Summ: %d\n",CheckSumList(head));
    Reset();


    cout << "\n#4 DELETE ALL LIST ELEMENTS\n";
    FillRandStack(n);
    PrintStack();
    DeleteAllElemenets();
    PrintStack();
    cout << "\n#5 RECURSIVE FUNCTION INC/DEC\n";
    cout << "\nPrinting list elements in forward order:\n";
    FillRandStack(n);
    PrintListForward(head);

    cout << "\nPrinting list elements in reverse order:\n";
    PrintListBackward(head);

    Reset();

    cout << "\n#6 SWAP ELEMENTS 4 and 6\n";
    FillIncStackTask(10);
    PrintStack();

    Stack *p3=head->next->next,
    *p4=p3->next,
    *p5=p4->next,
    *p6=p5->next,
    *p7=p6->next;
    p3->next=p6;
    p5->next=p4;
    p6->next=p4->next;
    p4->next=p7;
    PrintStack();

    cout << "\n#7 INITIALIZATION QUEUE\n";
    qtail = (Que*)&qhead;
    FillIncQueueInitialization(10);
    PrintQueue();

    return 0;
}