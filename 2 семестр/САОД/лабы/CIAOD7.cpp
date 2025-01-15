#include <stdio.h>
#include <string.h>

struct abonent {
  char name[50];
  char surname[50];
  char phone[15];
  int age;
};
int c=0;
int less(struct abonent X, struct abonent Y, int key, int direction) {
  switch (key) {
    case 1:
      if (direction == 1)
        if (strcmp(X.name, Y.name) < 0) {
          return 1;
        } else {
          return 0;
        }
      else if (strcmp(X.name, Y.name) > 0) {
        return 1;
      } else {
        return 0;
      }
      break;
    case 2:
      if (direction == 1)
        if (strcmp(X.phone, Y.phone) < 0) {
          return 1;
        } else {
          return 0;
        }
      else if (strcmp(X.phone, Y.phone) > 0) {
        return 1;
      } else {
        return 0;
      }
      break;
    case 3:
      if (direction == 1)
        if (X.age > Y.age) {
          return 1;
        } else {
          return 0;
        }
      else if (X.age < Y.age) {
        return 1;
      } else {
        return 0;
      }
      break;
    default:
      return -1;
  }
}

void SelectSort(struct abonent MyArray[], int n, int key, int direction) {
  for (int i = 0; i < n - 1; i++) {
    int count = i;
    for (int j = count + 1; j < n; j++) {
      if (less(MyArray[j], MyArray[count], key, direction)) {
        count = j;
      }
    }
    if (i != count) {
      struct abonent temp = MyArray[count];
      MyArray[count] = MyArray[i];
      MyArray[i] = temp;
    }
  }
}

int main() {
  struct abonent phoneBook[5] = {{"Ivan", "Ivanov", "11111", 21},
                                 {"Misha", "Nikolaev", "33333", 21},
                                 {"Gleb", "Merlinskiy", "22222", 32},
                                 {"Dima", "Kumov", "44444", 63},
                                 {"Andrey", "Ivanov", "55555", 76}};

  int n = 5;

  printf("Original spravochnik:\n");
  for (int i = 0; i < n; i++) {
    printf("%s %s, %s, %d years\n", phoneBook[i].name, phoneBook[i].surname, phoneBook[i].phone,
           phoneBook[i].age);
  }

  printf("\n");
  SelectSort(phoneBook, n, 3, 1);
  for (int i = 0; i < n; i++) {
    printf("%s %s, %s, %d years\n", phoneBook[i].name, phoneBook[i].surname, phoneBook[i].phone,
           phoneBook[i].age);
  }
  return 0;
}
