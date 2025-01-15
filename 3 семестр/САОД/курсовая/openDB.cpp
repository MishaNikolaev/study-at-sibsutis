#include <conio.h>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <fstream>
//#include <string>
#include <unordered_map>
#include <algorithm>

const char *base = "C://Users//HUAWEI//Downloads//testBase4.dat";

typedef struct record {
    char name[32];
    char address[18];
    short int house_number;
    short int kvartira_number;
    char date[10];
} record;

struct queEl {
    record* data;
    queEl* next=NULL;
    int wes;
};
struct que {
    queEl* head=NULL;
    queEl* tail=NULL;
};
struct vertex {
    record *data;
    vertex *L=nullptr;
    vertex *R=nullptr;
    vertex *center=NULL;
    int wes;
};

using namespace std;
int countRecords;
record *pData = NULL;
record **indexData = NULL;
const int PAGE_SIZE = 20;
void printElement(const record *p, int index) {
    printf("%6d ", index + 1);
    printf("%32.32s ", p->name);
    printf("St. ");
    printf("%18.18s ", p->address);
    printf("dom.");
    printf("%02d ", p->house_number);
    printf("kv.");
    printf("%03d ", p->kvartira_number);
    printf("%10.10s ", p->date);
    printf("\n");
}
int readData() {
    FILE *f;
    int count;

    f = fopen(base, "rb");
    if (f == NULL) {
        printf("\nError: file base4.dat not found.");
        printf("\nPlease check the file location.\n");
        exit(1);
    }

    fseek(f, 0, SEEK_END);
    count = ftell(f) / sizeof(record);

    if (count != 0) {
        fseek(f, 0, SEEK_SET);
        pData = (record *)malloc(sizeof(record) * count);
        fread(pData, sizeof(record), count, f);
    }

    fclose(f);

    return count;
}

queEl* initQueEl(record* data) {
    queEl* newQueEl=new queEl;
    newQueEl->data=data;
    return newQueEl;
}
que* initQue() {
    que* newQue=new que;
    newQue->tail=(queEl*)&(newQue->head);
    return newQue;
}
void addToQue(que* curQue,queEl* rec) {
    curQue->tail->next=rec;
    curQue->tail=rec;
}
int searchCompare(record* rec,char* key) {
    return strncmp(rec->name,key,3);
}

int compareRecords(const record* record1, const record* record2) {
    int cmp = strcmp(record1->name, record2->name);
    if (cmp != 0) {
        return cmp;
    }

    cmp = strcmp(record1->address, record2->address);
    return cmp;
}

void QuickSortV2(record* MyArray[], int L, int R)
{
    while (L < R)
    {
        int i = L, j = R;
        record x = *indexData[L];
        while (i < j)
        {
            while (compareRecords(indexData[i], &x) < 0) {
                i++;
            }
            while (compareRecords(indexData[j], &x) > 0) {
                j--;
            }
            if (i <= j)
            {
                record* temp = indexData[i];
                indexData[i] =indexData[j];
                indexData[j] = temp;
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
}
int compareWes(int wes1,int wes2) {
    return wes1>wes2;
}
void QuickSortV2Ubiv(queEl** MyArray, int L, int R)
{
    while (L < R)
    {
        int i = L, j = R;
        int x = MyArray[L]->wes;
        while (i < j)
        {

            while (compareWes(MyArray[i]->wes, x)) {
                i++;
            }
            while (compareWes(x, MyArray[j]->wes) ) {
                j--;
            }
            if (i <= j)
            {
                queEl* temp = MyArray[i];
                MyArray[i] =MyArray[j];
                MyArray[j] = temp;

                i++;
                j--;
            }
        }
        if ((j - L) < (R - i))
        {
            QuickSortV2Ubiv(MyArray, L, j);
            L = i;
        }
        else
        {
            QuickSortV2Ubiv(MyArray, i, R);
            R = j;
        }
    }
}
que* binSearch(record* indexData[],int size,char* key) {
    int L=0,R=size-1,m;
    while(L<R) {
        m=(L+R)/2;
        if (searchCompare(indexData[m],key)<0) {
            L=m+1;
        }
        else {
            R=m;
        }
    }
    que* newQue=initQue();
    newQue->head=initQueEl(indexData[R]);
    newQue->tail=newQue->head;
    R++;
    while(R<size && searchCompare(indexData[R],key)==0) {
        addToQue(newQue,initQueEl(indexData[R]));
        R++;
    }
    return newQue;
}
int searchInTree(vertex*& p,char* r) {
    return strncmp(p->data->date,r,8);
}
void addRST_R(vertex *&p,queEl* data,int& kolv)
{
    if (!p)
    {
        p = new vertex;
        p->data=data->data;
        p->wes=data->wes;
        kolv++;
    }
    else if ((searchInTree(p,data->data->date)) > 0)
    {
        addRST_R(p->L, data,kolv);
    }
    else if (searchInTree(p,data->data->date) < 0)
    {
        addRST_R(p->R, data,kolv);
    }
    else {
        addRST_R(p->center,data,kolv);
    }
}
void printTreeElement(vertex *p, int& index) {
    vertex* cursor=p;
    while(cursor){
        index++;
        printElement(cursor->data,index);
        cursor=cursor->center;
    }
}
void printTree(vertex* root,int &index) {
    if(!root)
        return;
    printTree(root->L,index);
    printTreeElement(root,index);
    printTree(root->R,index);
}
vertex* A1(record *V[],int size)
{
    queEl** arr=new queEl*[size];
    for(int i=0;i<size;i++) {
        arr[i]=initQueEl(V[i]);
        arr[i]->wes=rand()%100;
    }
    QuickSortV2Ubiv(arr,0,size-1);
    vertex* root=nullptr;
    int size1=0;
    for(int i=0;i<size;i++){
        addRST_R(root,arr[i],size1);
    }
    int index=-1;
    printTree(root,index);
    cout<<"size of array: "<<size<<endl<<"size of tree: "<<size1<<endl;
    return root;
}
void search_in_tree(vertex *root, char* key, int &i)
{
    if (root)
    {
        if (searchInTree(root,key)<0)
        {
            search_in_tree(root->R, key, i);
        }
        else if (searchInTree(root,key)>0)
        {
            search_in_tree(root->L, key, i);
        }
        else if (searchInTree(root,key) == 0)
        {
            printTreeElement(root, i);
            return;
        }
    }
}


void Print_tree(vertex *p, int &i)
{
    if (p)
    {
        Print_tree(p->L, i);
        printTreeElement(p, i);
        Print_tree(p->R, i);
        i++;
    }
}

void printAll() {
    for (int i = 0; i < countRecords; i++) {
        printElement(indexData[i], i);
    }
}


void printPage(int start) {
    int end = start + PAGE_SIZE;
    if (end > countRecords) end = countRecords;

    for (int i = start; i < end; i++) {
        printElement(indexData[i], i);
    }
}

void printQue(que* queToPrint) {
    queEl* cursor=queToPrint->head;
    int ind=0;
    while(cursor) {
        printElement(cursor->data,ind);
        ind++;
        cursor=cursor->next;
    }
}

void printDBPageByPage() {
    int totalPages = 200;
    int currentPage = 0;

    bool exitToMenu = false;

    while (!exitToMenu) {
        int start = currentPage * PAGE_SIZE;
        int end = start + PAGE_SIZE - 1;
        if (end >= countRecords) end = countRecords - 1;

        printPage(start);
        printf("\n"
               "1 - Next page\n"
               "2 - Choose the page\n"
               "3 - Previous page\n"
               "4 - Sorting by FIO and name street\n"
               "5 - Searching by FIO\n");
        printf("0 - Exit to main menu\n");

        int choice;
        scanf("%d", &choice);

        if (choice == 0) {
            exitToMenu = true;
        } else if (choice == 1 && currentPage < totalPages - 1) {
            currentPage++;
        } else if (choice == 2) {
            int page;
            printf("Choose the page (1 - %d): ", totalPages);
            scanf("%d", &page);
            if (page < 1 || page > totalPages) {
                printf("Failed choice of the page.\n");
            }
            currentPage = page - 1;
        } else if (choice == 3 && currentPage > 0) {
            currentPage--;
        } else if (choice == 4) {
            QuickSortV2(indexData, start, end);
        } else if (choice == 5) {
            printf("Input key to search by FIO:\n");
            char *key = new char[4];
            scanf("%s", key);
            que* findQue = binSearch(indexData, countRecords, key);
            printQue(findQue);
            delete[] key;
        } else {
            continue;
        }
    }
}

void displayAll() {
    printAll();
    while (1) {
        printf("\n1 - Sort by FIO and street\n0 - Exit\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 0) return;
        if (choice == 1) {
            QuickSortV2(indexData, 0, countRecords - 1);
            printAll();
            break;
        } else {
            continue;
        }
    }
    while (1) {
        printf("\n1 - Search by three symbols of surname\n0 - Exit\n");
        int choice;
        scanf("%d", &choice);
        if (choice == 0) return;
        else if(choice == 1){
            printf("Input key to search:\n");
            char *key=new char[5];
            scanf("%s",key);
            que* findQue=binSearch(indexData,countRecords,key);
            printQue(findQue);
            break;
        }
        else{
            continue;
        }
    }
}
vertex* root=NULL;
void mainMenu(int mode) {
    if (mode == 1) {
        displayAll();
    } else if (mode == 2) {
        printDBPageByPage();
    }
    else if(mode==3) {
        root=A1(indexData,countRecords);
    }
    else if(mode==4) {
        if(!root) {
            cout<<"no tree"<<endl;
            return;
        }
        char* key=new char[5];
        cout<<endl<<"input key: ";
        scanf("%s",key);
        int index=0;
        search_in_tree(root,key,index);
    }
}

int menu() {
    int in;

    printf("\n");
    printf("1 - Display all records.\n");
    printf("2 - Display records page by page (20 records per page).\n");
    printf("3 - Create tree\n");
    printf("4 - Search in tree\n");
    printf("0 - Exit.\n");
    scanf("%d", &in);
    printf("\n");

    return in;
}
void createIndexMass(int size) {
    indexData=new record*[size];
    for(int i=0;i<size;i++) {
        indexData[i]=&(pData[i]);
    }
}
int main() {
    countRecords = readData();
    createIndexMass(countRecords);
    while (1) {
        int mode=menu();
        switch (mode) {
            case 0:
                printf("Program exit.\n");
                exit(0);
                break;
            default:
                mainMenu(mode);
                break;
        }
    }
}