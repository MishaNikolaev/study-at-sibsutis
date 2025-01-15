#include <iostream>
#include <ctime>
#include <algorithm>

using namespace std;

struct vertex {
    int data;
    vertex* L = nullptr;
    vertex* R = nullptr;
};

const int MAX_RAND = 10;

vertex* init() {
    vertex* p = new vertex;
    p->data = rand() % MAX_RAND;
    return p;
}

void printTree(vertex *p) {
    cout << endl;
    cout << "                  ___                  " << endl;
    cout << "                 |";
    cout << p->data;
    cout << "|                  " << endl;
    cout << "                  ___                  " << endl;
    cout << "                 /                       " << endl;
    cout << "               ___                   " << endl;
    cout << "              |";
    cout << (p->L)->data;
    cout << "|" << endl;
    cout << "            /       \\                " << endl;
    cout << "          ___       ---       " << endl;
    cout << "         |";
    cout << ((p->L)->L)->data;
    cout << "|";
    cout << "      |";
    cout << ((p->L)->R)->data;
    cout << "|";
    cout << endl;
    cout << "        /     \\" << endl;
    cout << "    ___       ---       " << endl;
    cout << "   |";
    cout << (((p->L)->L)->L)->data;
    cout << "|";
    cout << "      |";
    cout << (((p->L)->L)->R)->data;
    cout << "|";
}

void createTree(vertex*& p) {
    p = init();

    p->L=init();
    (p->L)->R=init();
    (p->L)->L=init();
    ((p->L)->L)->L=init();
    ((p->L)->L)->R=init();

    printTree(p);
}

void obhodTree_TopBottom(vertex* p) {
    if (p != nullptr) {
        cout << p->data << "; ";
        obhodTree_TopBottom(p->L);
        obhodTree_TopBottom(p->R);
    }
}

void obhodTree_LeftToRight(vertex* p) {
    if (p != nullptr) {
        obhodTree_LeftToRight(p->L);
        cout << p->data << "; ";
        obhodTree_LeftToRight(p->R);
    }
}

void obhodTree_BottomToTop(vertex* p) {
    if (p != nullptr) {
        obhodTree_BottomToTop(p->L);
        obhodTree_BottomToTop(p->R);
        cout << p->data << "; ";
    }
}

int sizeTree(vertex* p) {
    if (p == nullptr)
        return 0;
    return 1 + sizeTree(p->L) + sizeTree(p->R);
}

int checkSumTree(vertex* p) {
    if (p == nullptr)
        return 0;
    return p->data + checkSumTree(p->L) + checkSumTree(p->R);
}

int summaLenghtofPaths(vertex* p, int depth) {
    if (p == nullptr)
        return 0;
    return depth + summaLenghtofPaths(p->L, depth + 1) + summaLenghtofPaths(p->R, depth + 1);
}

int heightTree(vertex* p) {
    if (p == nullptr)
        return 0;
    return 1 + max(heightTree(p->L), heightTree(p->R));
}

float averageHeightTree(vertex* p) {
    int size = sizeTree(p);
    if (size) {
        return float(summaLenghtofPaths(p, 1)) / size;
    } else {
        return 0;
    }
}

int main() {
    srand(time(NULL));
    vertex *root = nullptr;

    createTree(root);

    cout << endl << "Obhod top to bottom: ";
    obhodTree_TopBottom(root);
    cout << endl << "Obhod left to right: ";
    obhodTree_LeftToRight(root);
    cout << endl << "Obhod bottom to top: ";
    obhodTree_BottomToTop(root);

    cout << endl << "_____________________";
    cout << endl << "Size of tree: ";
    cout << sizeTree(root);
    cout << endl << "Height tree: ";
    cout << heightTree(root);
    cout << endl << "Summa lenght routes tree: ";
    cout << summaLenghtofPaths(root, 1);
    cout << endl << "Average height tree: ";
    cout << averageHeightTree(root);
    cout << endl << "Control sum tree: ";
    cout << checkSumTree(root);

    return 0;
}