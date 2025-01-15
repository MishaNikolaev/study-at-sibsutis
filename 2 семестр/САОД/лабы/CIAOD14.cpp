#include <stdio.h>
#include <stdlib.h>
#include <ctime>
#include <math.h>
#include <iostream>

using namespace std;

int SizeHashTable = 19;
const int countNums = 40;
int collisions = 0;

struct list {
    list *next;
    int data;
};

struct hash_table {
    hash_table *next;
    long hash;
    list *data;
};

long hash_func(int *num) {
    int hash;
    hash = *num % SizeHashTable;
    return hash;
}

void printList(hash_table *head) {
    hash_table *p = head;
    while (p != nullptr) {
        cout << p->hash << " ";
        list *temp = p->data;
        while (temp != nullptr) {
            cout << " -> " << temp->data;
            temp = temp->next;
        }
        p = p->next;
        cout << "\t" << endl;
    }
    cout << endl;
}

void addToTheTable(hash_table *head, int *elem, int &collisions) {
    int hash = hash_func(elem);
    hash_table *find = head;
    while (find != nullptr) {
        if (find->hash == hash) {
            break;
        }
        find = find->next;
    }
    list *p = find->data;
    if (p == nullptr) {
        p = new list;
        p->data = *elem;
        p->next = nullptr;
        find->data = p;
    } else {
        if(*elem==p->data) {
            return;
        }
        while (p->next != nullptr) {
            p = p->next;
            if(*elem==p->data) {
                return;
            }
        }
        list *newNode = new list;
        newNode->data = *elem;
        newNode->next = nullptr;
        p->next = newNode;
        collisions++;
    }
    return;
}

int HashSearch(hash_table *head, int *elem) {
    int x = hash_func(elem);
    int index;
    hash_table *find = head;

    while (find != nullptr) {
        index = 1;
        if (find->hash == x) {
            list *p = find->data;
            while (p != nullptr) {
                if (p->data == *elem) {
                    cout << "Element " << *elem << " is found " << "on position " << index;
                    return 1;
                }
                index++;
                p = p->next;
            }
        }
        find = find->next;
    }
    cout << "Element " << *elem << " isn`t found";
    return 0;
}

bool isSimple(int numb) {
    for(int i=2;i<numb;i++) {
        if(numb%i==0) {
            return false;
        }
    }
    return true;
}

int getHashTableSize(int n) {
    int hash_table_size=n/(2*log2(n));
    while(!isSimple(hash_table_size)) {
        hash_table_size++;
    }
    return hash_table_size;
}

int main() {
    srand(time(nullptr));

    int num;
    hash_table *head = nullptr;

    hash_table *p, *temp;
    temp = (hash_table *) (&head);

    for (int i = 0; i < SizeHashTable; i++) {
        p = new hash_table;
        temp->next = p;
        temp = p;
        p->hash = i;
        p->data = nullptr;
        p->next = nullptr;
    }

    cout<<getHashTableSize(87)<<endl;

    for (int i = 0; i < countNums; i++) {
        num = rand() % 1000;
        int hash = hash_func(&num);
        cout << num << ": hash-adres-> " << hash << endl;
        addToTheTable(head, &num, collisions);
    }
    cout << "Hash table:" << endl;
    printList(head);
    cout << "Count of collisions: " << collisions << "\n" << endl;

    cout << "Input element for search: ";
    cin >> num;
    HashSearch(head, &num);

    cout << "\n#3 TABLE COLLISION" << endl;
    int countNumsTable = 87;
    int sizes[] = {11, 19, 31, 41, 53, 61, 71, 83, 97, 101};
    int collisionCounts[10];

    for (int i = 0; i < 10; ++i) {
        SizeHashTable = sizes[i];
        collisions = 0;
        hash_table *head = nullptr;

        hash_table *p, *temp;
        temp = (hash_table*)(&head);

        for (int j = 0; j < sizes[i]; j++) {
            p = new hash_table;
            temp->next = p;
            temp = p;
            p->hash = j;
            p->data = nullptr;
            p->next = nullptr;
        }

        for (int k = 0; k < countNumsTable; k++) {
            num = rand() % 1000;
            addToTheTable(head, &num, collisions);
        }

        collisionCounts[i] = collisions;
    }

    printf("---------------------------------------------------------------------|\n");
    printf("|Size hash table  |    Count initial symbols   | Count of collisions   |\n");
    printf("|-----------------|----------------------------|-----------------------|\n");
    for (int i = 0; i < 10; ++i) {
        printf("|     %d          |            %d              |           %d          |\n", sizes[i], countNumsTable, collisionCounts[i]);
    }
    printf("--------------------------------------------------------------------\n");

    return 0;
}
