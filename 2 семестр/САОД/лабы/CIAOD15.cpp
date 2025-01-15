#include <iostream>
#include <ctime>

using namespace std;

const int SIZE_OF_HASH_TABLE = 15;
const int NUM_OF_STRING = 13;

long hash_func(int num) {
    int hash = num % SIZE_OF_HASH_TABLE;
    return hash;
}

void printHashTable(int hash_table[]) {
    printf("\n");
    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++)
        printf("%-6d", i);

    printf("\n");
    for (int i = 0; i < SIZE_OF_HASH_TABLE; i++)
        printf("%-6d", hash_table[i]);
}

int QuadraticProb(int hash_table[], int num, int size_table, int search) {
    int hash = hash_func(num);
    int d = 1;
    int collisions = 0;
    while (true) {
        if (hash_table[hash] == num && search) {
            cout << "\nElement is found" << endl;
            cout << "Position: " << hash << endl;
            break;
        }
        if (hash_table[hash] == 0 && !search) {
            hash_table[hash] = num;
            break;
        } else if (!search) {
            collisions++;
        }
        if (d >= size_table && !search) {
            break;
        } else if (d >= size_table && search) {
            cout << "\nElement is not found" << endl;
            break;
        }
        hash = (hash + d * d) % size_table;
        d++;
    }

    return collisions;
}

int LinearProb(int hash_table[], int num, int size_table, int search) {
    int hash = hash_func(num);
    int d = 1;
    int collisions = 0;
    while (1) {
        if (hash_table[hash] == num && search) {
            cout << "\nElement is found" << endl;
            cout << "Position: " << hash << endl;
            break;
        }
        if (hash_table[hash] == 0 && !search) {
            hash_table[hash] = num;
            break;
        } else if (!search) {
            collisions++;
        }
        if (d >= size_table && !search) {
            break;
        } else if (d >= size_table && search) {
            cout << "\nElement is not found" << endl;
            break;
        }
        hash = (hash + 1) % size_table;
        d++;
    }

    return collisions;
}

int main() {
    int collisions = 0;
    srand(time(NULL));
    int hashTableLinear[SIZE_OF_HASH_TABLE] = {0};
    int hashTableQuadratic[SIZE_OF_HASH_TABLE] = {0};
    cout << "\n#2 HASHING TABLE LINEAR/QUADRATIC PROB" << endl;
    cout << "\n~~~~~~~~~~~~~~ Linear prob ~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < NUM_OF_STRING; i++)
        collisions+=LinearProb(hashTableLinear, rand() % 100 + 1, SIZE_OF_HASH_TABLE, 0);


    printHashTable(hashTableLinear);
    cout << "\nCount collisions: " << collisions << endl;

    cout << "\n\n~~~~~~~~~~~~~~ Quadratic prob ~~~~~~~~~~~~~~" << endl;

    for (int i = 0; i < NUM_OF_STRING; i++)
        collisions += QuadraticProb(hashTableQuadratic, rand() % 100 + 1, SIZE_OF_HASH_TABLE, 0);

    printHashTable(hashTableQuadratic);
    cout << "\nCount collisions: " << collisions << endl;


    cout << "\n\n#3 COLLISIONS";
    int simple_num[5] = {11, 23, 37, 47, 53};
    cout << "\n\n" << "Size table " << " Count symbols" << "\t" << "Linear" << "\t" << "    Quadratic" << endl;

    for (int i = 0; i < 5; i++) {
        int line_colis = 0;
        int quadr_colis = 0;
        for(int j=0;j<SIZE_OF_HASH_TABLE;j++) {
            hashTableLinear[j]=0;
            hashTableQuadratic[j]=0;
        }
        int count = NUM_OF_STRING;
        for (int j = 0; j < count; j++)
            line_colis += LinearProb(hashTableLinear, rand() % 100 + 1, simple_num[i], 0);

        for (int j = 0; j < count; j++)
            quadr_colis += QuadraticProb(hashTableQuadratic, rand() % 100 + 1, simple_num[i], 0);

        cout << endl;
        cout << simple_num[i] << "\t\t" << NUM_OF_STRING << "\t\t" << line_colis << "\t\t" << quadr_colis << "\t\t" << endl;
    }


    cout << "\n\n#4 SEARCHING HASH TABLE";
    int hashTableLinearHash[SIZE_OF_HASH_TABLE] = {0};
    int hashTableQuadraticHash[SIZE_OF_HASH_TABLE] = {0};
    cout << "\n~~~~~~~~~~~~~~ Linear prob ~~~~~~~~~~~~~~" << endl;
    for (int i = 0; i < NUM_OF_STRING; i++)
        LinearProb(hashTableLinearHash, rand() % 100 + 1, SIZE_OF_HASH_TABLE, 0);

    printHashTable(hashTableLinearHash);

    cout << "\n\n~~~~~~~~~~~~~~ Quadratic prob ~~~~~~~~~~~~~~" << endl;

    for (int i = 0; i < NUM_OF_STRING; i++)
        QuadraticProb(hashTableQuadraticHash, rand() % 100 + 1, SIZE_OF_HASH_TABLE, 0);

    printHashTable(hashTableQuadraticHash);

    int choose = 0;
    cout << "\n\nChoose method searching[ 0/1 ]: ";
    cin >> choose;
    cout << "Input number: ";

    while (true) {
        int num;
        cin >> num;
        if (num == 0) break;

        if (choose == 0)
            LinearProb(hashTableLinearHash, num, SIZE_OF_HASH_TABLE, 1);
        if (choose == 1)
            QuadraticProb(hashTableQuadraticHash, num, SIZE_OF_HASH_TABLE, 1);
        cout << "Input method searching [ 0/1 ]: ";
        cin >> choose;
        cout << "Input number: ";
    }

    return 0;
}