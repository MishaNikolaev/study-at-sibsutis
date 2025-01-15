#include <stdio.h>
#include <string.h>

struct abonent {
    char name[50];
    char surname[50];
    char phone[15];
    int age;
};

int LessIncreaseByName(struct abonent x, struct abonent y) {
    if (strcmp(x.name, y.name) < 0)
        return 1;
    else if (strcmp(x.name, y.name) > 0)
        return 0;
    else if (strcmp(x.surname, y.surname) < 0)
        return 1;
    else
        return 0;
}
int LessDecByName(struct abonent x, struct abonent y) {
    if (strcmp(x.name, y.name) > 0)
        return 1;
    else if (strcmp(x.name, y.name) < 0)
        return 0;
    else if (strcmp(x.surname, y.surname) > 0)
        return 1;
    else
        return 0;
}

int LessIncreaseByPhone(struct abonent x, struct abonent y) {
    if (strcmp(x.phone, y.phone) < 0)
        return 1;
    else
        return 0;
}

int LessDecByPhone(struct abonent x, struct abonent y) {
    if (strcmp(x.phone, y.phone) > 0)
        return 1;
    else
        return 0;
}

void SelectSort(struct abonent a[], int n, int b[], int (*cmp)(struct abonent, struct abonent)) {
    for (int i = 0; i < n - 1; i++) {
        int k = i;
        for (int j = i + 1; j < n; j++) {
            if (cmp(a[b[j]], a[b[k]]))
                k = j;
        }
        if (i != k) {
            int temp = b[i];
            b[i] = b[k];
            b[k] = temp;
        }
    }
}

int main() {
    struct abonent abonents[5] = {
            {"Kirill", "Dimitrov", "33333", 21},
            {"Dmitry", "Chanov", "11111", 21},
            {"Bogdan", "Kumov", "55555", 32},
            {"Charles", "Aricson", "44444", 63},
            {"Andrey", "Borisov", "22222", 76}
    };

    int n = sizeof(abonents) / sizeof(abonents[0]);
    int i, a[n], c[n];

    for (i = 0; i < n; i++) {
        a[i] = i;
    }

    for (i = 0; i < n; i++) {
        c[i] = i;
    }

    printf("Original struct:\n");
    for (i = 0; i < n; i++) {
        printf("%s %s, %s, %d\n", abonents[i].name, abonents[i].surname, abonents[i].phone, abonents[i].age);
    }

    printf("\nStruct, sorted by name in increasing order:\n");
    SelectSort(abonents, n, a, LessIncreaseByName);
    for (i = 0; i < n; i++) {
        printf("%s %s, %s, %d\n", abonents[a[i]].name, abonents[a[i]].surname, abonents[a[i]].phone, abonents[a[i]].age);
    }

    printf("\nStruct, sorted by name in dec order:\n");
    SelectSort(abonents, n, c, LessDecByName);
    for (i = 0; i < n; i++) {
        printf("%s %s, %s, %d\n", abonents[c[i]].name, abonents[c[i]].surname, abonents[c[i]].phone, abonents[c[i]].age);
    }

    printf("\nStruct, sorted by phone number in increasing order:\n");
    SelectSort(abonents, n, a, LessIncreaseByPhone);
    for (i = 0; i < n; i++) {
        printf("%s %s, %s, %d\n", abonents[a[i]].name, abonents[a[i]].surname, abonents[a[i]].phone, abonents[a[i]].age);
    }

    printf("\nStruct, sorted by phone number in dec order:\n");
    SelectSort(abonents, n, c, LessDecByPhone);
    for (i = 0; i < n; i++) {
        printf("%s %s, %s, %d\n", abonents[c[i]].name, abonents[c[i]].surname, abonents[c[i]].phone, abonents[c[i]].age);
    }

    return 0;
}
