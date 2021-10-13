#include <stdio.h>
#include <stdio_ext.h>
#include <stdlib.h>

typedef struct Node {
	int value;
	struct Node *next;
	struct Node *prev;
} node;

typedef struct LinkedList {
	int size;
	node *head;
	node *tail;
}List;

int size ();
int enterNum();
void printMenu();
void printError();
List* createList();
void deleteList(List *list);
void add(int value);
node* get(int index);
void insert(int value, int index);
void removeNode(int index);
void print();
void set(int index, int value);

List *list = NULL;

int main() {
	int choice;
	int num, index;
	node *temp = NULL;
	while (1) {
		printMenu();
		choice = enterNum();
		switch (choice) {
			case 1:
				printf("\n Введите значение:");
				num = enterNum();
				add(num);
			break;
			case 2:
				printf("\n Введите значение:");
				num = enterNum();
				printf("\n Введите индекс:");
				index = enterNum();
				insert(num, index);
			break;
			case 3:
				printf("\n Количество элеметов в списке: %d", size());
			break;
			case 4:
				printf("\n Введите индекс:");
				index = enterNum();
				removeNode(index);
			break;
			case 5:
				printf("\n Введите значение:");
				num = enterNum();
				printf("\n Введите индекс:");
				index = enterNum();
				set(index, num);
			break;
			case 6:
				printf("\n Введите индекс:");
				index = enterNum();
				temp = get(index);
				if (!temp) {
					printError();
				} else {
					printf("\n Занчение элемента: %d", temp->value);
				}
			break;
			case 7:
				print();
			break;
			case 0:
				deleteList(list);
			return 0;
			default: printError();
		}
	}
	return 0;
}

int size () {
	if (!list) {
		return 0;
	}
	return list->size;
}

int enterNum() {
	int res, num;

	do {
		res = scanf("%d", &num);
		__fpurge(stdin);

		if (res != 1) printf("\n Некоректный ввод!\n->");
	} while (res != 1);
	
	return num;
}

void printMenu() {
	printf("\n 1 - Добавить в конец \n 2 - Вставить элемент\n 3 - Размер списка\n 4 - Удалить элемент\n 5 - Заменить элемент\n 6 - Получить элемент\n 7 - Распечатать список\n 0 - Выход\n->");
}

void printError() {
	printf("\n Что-то полшо не так :/");
}

List* createList() {
	List *temp = (List*) malloc (sizeof(List));
	temp->head = NULL;
	temp->tail = NULL;
	temp->size = 0;
	
	return temp;
}

void deleteList(List *list) {
	if (!list) return;

	node *temp = list->head;
	node *next = NULL;
	while (temp) {
		next = temp->next;
		free(temp);
		temp = next;
	}
	free(list);
	list = NULL;
}

void add(int value) {
	if(!list) {
		list = createList();
	}
	node *temp = (node*) malloc (sizeof(node));
	
	if (!temp) exit(-1);
	
	temp->next = NULL;
	temp->value = value;
	temp->prev = list->tail;
	
	if (list->tail) {
		list->tail->next = temp;
	}
	
	list->tail = temp;
	
	if (!list->head) {
		list->head = temp;
	}
	list->size++;
}

node* get(int index) {
	node *temp = list->head;
	int i = 0;
	
	if(!list || index > list->size || !list || index < 0) {
		printError();
		return NULL;
	}
	
	while(temp && i < index) {
		temp = temp->next;
		i++;
	}
	return temp;
}

void insert(int value, int index) {
	node *temp = NULL;
	node *ins = NULL;
	
	if (!list) {
		list = createList();
	}
	
	if(!index > list->size || index < 0) {
		printError();
		return;
	}
	
	temp = get(index);
	if (!temp) {
		printError();
		return;
	}
	
	ins = (node*) malloc (sizeof(node));
	ins->value = value;
	ins->prev = temp->prev;
	ins->next = temp;
	
	if (temp->next) {
		temp->prev->next = ins;
	}
	
	temp->prev = ins;
	
	if (!temp->prev) {
		list->head = temp;
	}
	
	if (!temp->next) {
		list->tail = temp;
	}
	
	list->size++;
}

void removeNode(int index) {
	node *temp = NULL;
	node *element = NULL;
	
	if (!list || index < 0 || index > list->size) {
		printError();
		return;
	}
	
	element = get(index);
	
	if (!element) {
		printError();
		return;
	}
	
	if (element->prev) {
		element->prev->next = element->next;
	}
	
	if (element->next) {
		element->next->prev = element->prev;
	}
	
	if (!element->prev) {
		list->head = element->next;
	}
	
	if(!element->next) {
		list->tail = element->prev;
	}
	
	free(element);
	
	list->size--;
}

void print() {
	node *temp = NULL;
	if (!list) {
		printError();
		return;
	}
	temp = list->head;
	while(temp) {
		printf(" %d", temp->value);
		temp = temp->next;
	}
}

void set(int index, int value) {
	node *temp = NULL;
	if (!list || index < 0 || index > list->size) {
		printError();
		return;
	}
	
	temp = get(index);
	
	if (!temp) {
		printError();
		return;
	}
	
	temp->value = value;
}