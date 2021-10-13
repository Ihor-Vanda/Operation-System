#include <stdio.h>
#include <time.h>
#include <stdlib.h>
#include <math.h>

typedef struct Point {
	int x;
	int y;
	int z;
	int weight;
} Point;

Point* creatRandomPoint();
Point* fillPoint(int x, int y, int z, int weight);
int findMinWeightPoint();
void printPoins();
void deletePointNearbyIndex(int index);
int distance(Point *a, Point *b);

Point **array = NULL;
int SIZE = 10;

int main () {
	srand(time(NULL));
	int i;
	array = (Point**) malloc (SIZE * sizeof(Point));
	
	for (i = 0; i < SIZE; i++) {
		array[i] = creatRandomPoint();
	}
	
	while (SIZE > 1) {
		printPoins();
		deletePointNearbyIndex(findMinWeightPoint());
	}	
	
	printPoins();
	
	return 0;
}

Point* creatRandomPoint() {
	Point* poin = (Point*) malloc (sizeof(Point));
	poin->x = rand()%200-100;
	poin->y = rand()%200-100;
	poin->z = rand()%200-100;
	poin->weight = rand()%100;
	
	return poin;
}

Point* fillPoint(int x, int y, int z, int weight) {
	Point* poin = (Point*) malloc (sizeof(Point));
	poin->x = x;
	poin->y = y;
	poin->z = z;
	poin->weight = weight;
	
	return poin;
}

int findMinWeightPoint() {
	int index = 0, i;
	double temp = array[0]->weight;
	
	for (i = 1; i < SIZE; i++) {
		if (array[i]->weight < temp) {
			temp = array[i]->weight;
			index = i;
		}
	}
	
	return index;
}

void printPoins() {
	int i;
	printf("\n");
	for (i = 0; i < SIZE; i++) {
		printf("\n%d.\tx: %d\ty: %d\tz: %d\tweight: %d", i+1, array[i]->x, array[i]->y, array[i]->z, array[i]->weight);
	}
	printf("\n");
}

void deletePointNearbyIndex(int index) {
	Point *temp = array[index];
	int i, mark = 0, tmp;
	int res = distance(temp, array[0]);

	
	for (i = 1; i < SIZE; i++) {
		tmp = distance(temp, array[i]);
		if (tmp <= res && i != index) {
			res = tmp; 
			mark = i;
		}
	}

	array[mark]->weight += temp->weight;
	
	for (i = index; i < SIZE - 1; i++) {
		array[i] = array[i + 1];
	}
	
	SIZE--;
	array = (Point**) realloc (array,SIZE * sizeof(Point));
}

int distance(Point *a, Point *b) {
	return sqrt(pow(a->x - b->x, 2) + pow(a->y - b->y, 2) + pow(a->z - b->z, 2));
}

