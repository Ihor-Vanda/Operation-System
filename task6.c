#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>
#include <limits.h>

int **createMatrix(int n,int m);
int printMatrix(int n, int m, int **arr);
int **sumMatrix(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM);
int **differenceMatrix(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM);
int **multiplicationWithNum(int **firstMatrix, int rowFirsM, int colFirsM);
int **matrixMultiplication(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM);
int **resize(int **firstMatrix, int rowFirsM, int colFirsM, int n, int m);
int save(int** A,char* fileName, int rows, int cols);
int** load(char* fileName, int numberM);
void printMenu();
int inputNum(int min, int max);

int rowFirsM, colFirsM, rowSecondM, colSecondM;
int **firstMatrix = NULL, **secondMatrix = NULL;

int main() {
    srand(time(0));
    int choise, row, col, value;
	int **resultMatrix = NULL;
	
    while (1){
        printMenu();
        scanf("%d", &choise);
		
        switch (choise) {
            case 1:
                printf("\n Матрица А. Столбцы: ");
                rowFirsM = inputNum(1, INT_MAX);
				
                printf("\n Матрица А. Колонки: ");
                colFirsM = inputNum(1, INT_MAX);
	
                firstMatrix = createMatrix(rowFirsM,colFirsM);
				
                printf("\n Матрица В. Столбцы: ");
                rowSecondM = inputNum(1, INT_MAX);
				
                printf("\n Матрица В. Колонки: ");
                colSecondM = inputNum(1, INT_MAX);
				
                secondMatrix = createMatrix(rowSecondM,colSecondM);
                break;
            case 2:
                if (firstMatrix) { 
                    free(firstMatrix);
                    firstMatrix = NULL;
                }
                if (secondMatrix) {
                    free(secondMatrix);
                    secondMatrix = NULL;
                }
            break;
            case 3:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
				
                printf("\n Введите значение: ");
                value = inputNum(INT_MIN, INT_MAX);
				
                printf("\n Столбцы: ");
                row = inputNum(1, INT_MAX);
				
                printf("\n Колонки: ");
                col = inputNum(1, INT_MAX);
				
                if(choise == 1 && firstMatrix) {
                    firstMatrix[row][col] = value;
                } else if (choise == 2 && secondMatrix) {
                    secondMatrix[row][col] = value;
                }
            break;
            case 4:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
                
                printf("\n Столбцы: ");
                row = inputNum(1, INT_MAX);
                
                printf("\n Колонки: ");
                col = inputNum(1, INT_MAX);
				
                if(choise == 1 && firstMatrix) {
                    printf("\n%d\n",firstMatrix[row][col]);
                } else if (choise == 2 && secondMatrix) {
                    printf("\n%d\n",secondMatrix[row][col]);
                }
            break;
            case 5:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
				
                if(choise == 1 && firstMatrix) {
                    printMatrix(rowFirsM,colFirsM,firstMatrix);
                } else if (choise == 2 && secondMatrix) {
                    printMatrix(rowSecondM,colSecondM,secondMatrix);
                }
            break;
            case 6:
                printf("\n 1 - Сумма\n 2 - Разность\n 3 - Умножить на число\n 4 - Умножить матрицы\n->");
                choise = inputNum(1,4);

                if (firstMatrix && secondMatrix) {
                    if(choise == 1) {
                        resultMatrix = sumMatrix(firstMatrix,secondMatrix,rowFirsM,colFirsM,rowSecondM,colSecondM);
                    } else if(choise == 2) {
                        resultMatrix = differenceMatrix(firstMatrix,secondMatrix,rowFirsM,colFirsM,rowSecondM,colSecondM);
                    } else if(choise == 3) {
                        firstMatrix = multiplicationWithNum(firstMatrix,rowFirsM,colFirsM);
                    } else if (choise == 4) {
                        resultMatrix = matrixMultiplication(firstMatrix,secondMatrix,rowFirsM,colFirsM,rowSecondM,colSecondM);
                    }
                }   
            break;
            case 7:
				printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
			
                printf("\n Столбцы: ");
                row = inputNum(1, INT_MAX);
                
                printf("\n Колонки: ");
                col = inputNum(1, INT_MAX);
				
                if (firstMatrix && choise == 1) {
                    firstMatrix = resize(firstMatrix, rowFirsM, colFirsM, row, col);
                    rowFirsM = row;
                    colFirsM = col;
                } else if (secondMatrix && choise == 2) {
					secondMatrix = resize(secondMatrix, rowSecondM, colSecondM, row, col);
                    rowSecondM = row;
                    colSecondM = col;
				}
            break;
            case 8:
				printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
				
                if(choise == 1 && firstMatrix) {
                    save(firstMatrix,"test.txt", rowFirsM, colFirsM);
                } else if (choise == 2 && secondMatrix) {
                    save(firstMatrix,"test1.txt", rowSecondM, colSecondM);
                }
            break;
            case 9:
				printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                choise = inputNum(1,2);
				
                if(choise == 1) {
                    firstMatrix = load("test.txt", 1);
                } else if (choise == 2) {
                    secondMatrix = load("test1.txt", 2);
                } 
            break;
			case 0:
               return 0;
        }
    }
    return 0;
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

void printMenu() {
	printf("\n 1 - Создать матрицы\n 2 - Удалить матрицы\n 3 - Изменить значение элемента\n"
               " 4 - Получить значение элемента\n 5 - Распечатать матрицу\n"
               " 6 - Операции с матрицами\n 7 - Изменить размер\n 8 - Сохранить\n"
               " 9 - Загрузить\n 0 - Выход\n->");
}

int **resize(int **firstMatrix, int rowFirsM, int colFirsM, int n, int m) {
	int i, j, k, l;
    int **resultMatrix = createMatrix(n, m);
	
	if (n > rowFirsM) k = rowFirsM;
	else k = n;
	
	if (m > colFirsM) l = colFirsM;
	else l = m;
	
    for (i = 0; i < k; i++) {
        for (j = 0; j < l; j++) {
            resultMatrix[i][j] = firstMatrix[i][j];
        }
    }
    return resultMatrix;
}


int save(int** A,char* fileName, int rows, int cols) {
    int i, j;
    FILE* fp = NULL;
    if (A == NULL) {
        return 0;
    }
    if (!(fp = fopen(fileName, "w"))) {
        printf("\n Ошибка!");
        getchar();
        return 0;
    }
    fprintf(fp, "%d %d\n", rows, cols);
    for (i = 0; i < rows; i++) {
        for (j = 0; j < cols; j++) {
            fprintf(fp, "%d ", A[i][j]);
        }
        fprintf(fp, "\n");
    }
    fclose(fp);
    return 1;
}

int** load(char* fileName, int numberM) {
    FILE* fp = NULL;
    char arr[8];
    int t = 0, i = 0, j = 0;

    if (!(fp = fopen(fileName, "r"))) {
        printf("\n Ошибка!");
        getchar();
        return 0;
    }

    int row = 0, col = 0;
    fscanf(fp, "%d %d\n", &row, &col);
	
	if (numberM == 1) {
		rowFirsM = row;
		colFirsM = col;
	} else if (numberM == 2) {
		rowSecondM = row;
		colSecondM = col;
	}

    int** A = createMatrix(row, col);

    while (!feof(fp)) {
        fscanf(fp, "%c", &arr[t]);
        t++;
        if (arr[t - 1] == (' ')) {
            A[i][j] = atoi(arr);
            t = 0;
            j++;
        }
        if (arr[t - 1] == ('\n')) {
            i++;
            t = 0;
            j = 0;
        }
    }

    fclose(fp);

    return A;
}

int **matrixMultiplication(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM) {
	int i, j, k;
	
    if (colFirsM == rowSecondM) {
        int **resultMatrix = createMatrix(rowFirsM, colSecondM);
        for (i = 0; i < rowFirsM; i++) {
            for (j = 0; j < colSecondM; j++) {
                resultMatrix[i][j] = 0;
                for (k = 0; k < colFirsM; k++) {
                    resultMatrix[i][j] += firstMatrix[i][k] + secondMatrix[k][j];
                }
            }
        }
		
        printMatrix(rowFirsM, colSecondM, resultMatrix);
        return resultMatrix;
    } else{
        printf("\n Некорректные размеры матриц");
        return NULL;
    }
}


int **multiplicationWithNum(int **firstMatrix, int rowFirsM, int colFirsM) {
    int **resultMatrix = createMatrix(rowFirsM,colFirsM);
    int num, i, j;
	
    printf("\n Введите число: ");
    scanf("%d", &num);
	
    for (i = 0; i < rowFirsM; ++i) {
        for (j = 0; j < colFirsM; ++j) {
            resultMatrix[i][j] = num * firstMatrix[i][j];
        }
    }
    printMatrix(rowFirsM,colFirsM,resultMatrix);
    return resultMatrix;
}

int **sumMatrix(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM) {
	int i, j;
    int **resultMatrix = createMatrix(rowFirsM,colFirsM);
    if (rowFirsM == rowSecondM && colFirsM == colSecondM){
        for(i =0; i < rowFirsM; i++){
            for (j = 0; j < colFirsM; j++) {
                resultMatrix[i][j] = firstMatrix[i][j] + secondMatrix[i][j];
            }
        }
        printMatrix(rowFirsM,colFirsM,resultMatrix);
        return resultMatrix;
    } else{
         printf("\n Некорректные размеры матриц");
        return NULL;
    }
}

int **differenceMatrix(int **firstMatrix, int **secondMatrix, int rowFirsM, int colFirsM, int rowSecondM, int colSecondM){
    int **resultMatrix = createMatrix(rowFirsM,colFirsM);
	int i, j;
	
    if (rowFirsM == rowSecondM && colFirsM == colSecondM) {
		
        for(i =0; i < rowFirsM; i++){
            for (j = 0; j < colFirsM; j++) {
                resultMatrix[i][j] = firstMatrix[i][j] - secondMatrix[i][j];
            }
        }
        printMatrix(rowFirsM,colFirsM,resultMatrix);
        return resultMatrix;
    } else{
        printf("\n Некорректные размеры матриц");
        return NULL;
    }
}


int **createMatrix(int n, int m) {
	int i, j;
    int **arr = (int **) malloc(n*sizeof (int *));
	
    for(i = 0; i < n; i++){
        arr[i] = (int*) malloc(m * sizeof (int));
    }
    for (i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            arr[i][j] = rand()%20;
        }
    }
    return arr;
}

int printMatrix(int n, int m, int **arr) {
	int i, j;
    printf("\n");
    for(int i = 0; i < n; i++){
        for(j = 0; j < m; j++){
            printf("%d ",arr[i][j]);
        }
        printf("\n");
    }
}
