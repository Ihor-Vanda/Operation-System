#include <stdio.h>
#include <time.h>
#include <math.h>
#include <stdlib.h>

int* fillArray(int *array, int size);
int findMean(int *array, int size);
int sumAbs(int *array, int size);
void print(int *array, int size);

int main() {
	srand(time(NULL));
	int size = 5, i, num;
	int *array = (int*) malloc (sizeof(int));

	array = fillArray(array, size);
	num = findMean(array, size);
	
	print(array, size);

	printf("\n Mean = %d\n Number > mean \n", num);
	
	for (i = 0; i < size; i++) {
		if (array[i] > num) {
			printf(" %d", array[i]);
		}
	}

	printf("\n Sum abs after first minus num: %d\n", sumAbs(array, size));

	return 0;
}

int* fillArray(int *array, int size) {
	int i;
	
	for (i = 0; i < size; i++) {
		array[i] = rand()%20-10;
	}
	
	return array;
}

int findMean(int *array, int size) {
	int sum = 0, i;
	
	for (i = 0; i < size; i++) {
		sum += array[i];
	}
	
	return sum/size;
}

void print(int *array, int size) {
	int i;
	
	printf("\n");
	for (i = 0; i < size; i++) {
		printf(" %d", array[i]);
	}
}

int sumAbs(int *array, int size) {
	int sum = 0, i;
	int flag = 0;
	
	for (i = 0; i < size; i++) {
		if (flag == 1) {
			sum += abs(array[i]);		
		}
		if (array[i] < 0) flag = 1;
	}
	return sum;
}


