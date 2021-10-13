#include <stdio.h>
#include <stdlib.h>

int add (int element);
int insert (int index, int value);
int removeElement (int index);
int getSize ();
int get (int index);
int set (int index, int value);
void addMemoryInArray();
void removeMemoryInArray();
void printError();
void printMenu();
int inputNum(int min, int max);
void printMessage();
void printArray();


int* array = NULL;
int size = 0;

int main () {
  int choice, num, index;
  while (1) {
    printMenu();
    choice = inputNum(0, 7);
    
    switch(choice) {
      case 1:
        printf("\n Введите значение\n->");
        scanf("%d", &num);
        if (add(num)) printMessage();
      break;
      case 2:
        printf("\n Введите индекс элемента\n->");
        index = inputNum(0, size);
        
        printf("\n Введите значение\n->");
        scanf("%d", &num);
        
        if (insert(index, num)) printMessage();
      break;
      case 3:
        printf("\n Введите индекс элемента\n->");
        index = inputNum(0, size - 1);
        if (removeElement(index)) printMessage();
      break;
      case 4:
        printf("\n Размер массива: %d", getSize());
      break;
      case 5:
        printf("\n Введите индекс элемента\n->");
        index = inputNum(0, size - 1);
        
        printf("\n Введите новое значение\n->");
        scanf("%d", &num);
        
        if (set(index, num)) printMessage();
      break;
      case 6:
        printf("\n Введите индекс элемента\n->");
        index = inputNum(0, size - 1);
        printf("\n Значения элемента: %d", get(index));
      break;
      case 7:
        printArray();
      break;
      case 0:
      return 0;
      default: printError();
    }
  }
  return 0;
}

int add (int element) {
  addMemoryInArray();
  if (array) {
    array[size - 1] = element;
    return 1;
  } else
    printError();
  return 0;
}

int insert (int index, int value) {
  int i;

    if(index >= 0 && index <= size) {
    addMemoryInArray();
        for (i = size - 1; i > index; i--) {
      array[i] = array[i - 1];
    }
    array[index] = value;
    return 1;
    } else
        printError();
  return 0;
}

int removeElement (int index) {
  int i;
  if(!array) return 0;

  if (index >= 0 && index < size) {
    for (i = index; i < size - 1; i++) {
      array[i] = array[i + 1];
    }
    removeMemoryInArray();
    return 1;
  } else
    printError();
  return 0;
}

int getSize () { return size; }

int get (int index) {
  if(!array) return 0;

  if (index >= 0 && index < size)
    return array[index];
  else printError();
  return 0;
}

int set (int index, int value) {
  if(!array) return 0;

  if (index >= 0 && index < size) {
    array[index] = value;
    return 1;
  } else printError();
  return 0;
}

void addMemoryInArray() {
  array = (int*) realloc(array, (size + 1) * sizeof(int));
  size++;
}

void removeMemoryInArray() {
  array = (int*) realloc(array, (size - 1) * sizeof(int));
  size--;
}

void printError() {
  printf("\n Что-то пошло не так! :/");
}

void printMessage() {
  printf("\n Операция выполнена успешно!");
}

void printMenu() {
  printf("\n\n 1 - Добавить в конец массива\n 2 - Добавить в определенную позицию\n 3 - Удалить по индексу\n 4 - Размер массива\n 5 - Изменить элемент\n 6 - Получить элемент массива\n 7 - Распечатать\n 0 - Выход\n->");
}

int inputNum(int min, int max) {
  int temp, res;
  
  if (min > max) max = min;

  do {
    res = scanf("%d", &temp);
    fflush(stdin);

    if (res != 1 || temp < min || temp > max) printf("\n Некорректный ввод!\n->");  
  } while (res != 1 || temp < min || temp > max);
  return temp;
}

void printArray() {
  int i;
  if (array) {
    printf("\n");
    for (i = 0; i < size; i++) {
      printf(" %d", array[i]);
    }
  } else
    printError();
}

