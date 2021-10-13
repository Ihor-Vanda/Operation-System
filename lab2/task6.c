#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <malloc.h>
#include <locale.h>
#include <limits.h>

int **CreateMatrix(int n,int m);
int printMatrix(int n, int m, int **arr);
int **MatrixSum(int **arrA, int **arrB, int nA, int mA, int nB, int mB);
int **MatrixDifference(int **arrA, int **arrB, int nA, int mA, int nB, int mB);
int **MatrixMultiplication(int **arrA, int nA, int mA);
int **TwoMatrixMultiplication(int **arrA, int **arrB, int nA, int mA, int nB, int mB);
int **ResizeMatrix(int **arrA, int nA, int mA, int n, int m);
int saveMatrix(int** A,char* fileName, int rows, int cols);
int** loadMatrix(char* fileName);
void printMenu();
int inputNum(int min, int max);

int main() {
    srand(time(0));
    int nA,mA,nB,mB;
    int **arrA = NULL, **arrB = NULL, **arrC = NULL;
    int ch, chos, temp, i, j;
	
    while (1){
        printMenu();
        scanf("%d", &ch);
		
        switch (ch) {
            case 0:
               return 0;
            case 1:
                printf("\n Матрица А. Столбцы: ");
                nA = inputNum(1, INT_MAX);
				
                printf("\n Матрица А. Колонки: ");
                mA = inputNum(1, INT_MAX);
	
                arrA = CreateMatrix(nA,mA);
				
                printf("\n Матрица В. Столбцы: ");
                nB = inputNum(1, INT_MAX);
				
                printf("\n Матрица В. Колонки: ");
                mB = inputNum(1, INT_MAX);
				
                arrB = CreateMatrix(nB,mB);
                break;
            case 2:
                if (arrA) { 
                    free(arrA);
                    arrA = NULL;
                }
                if (arrB) {
                    free(arrB);
                    arrB = NULL;
                }
            break;
            case 3:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                chos = inputNum(1,2);
				
                printf("\n Введите значение: ");
                temp = inputNum(INT_MIN, INT_MAX);
				
                printf("\n Столбцы: ");
                i = inputNum(1, INT_MAX);
				
                printf("\n Колонки: ");
                j = inputNum(1, INT_MAX);
				
                if(chos == 1 && arrA) {
                    arrA[i][j] = temp;
                } else if (chos == 2 && arrB) {
                    arrB[i][j] = temp;
                }
            break;
            case 4:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                chos = inputNum(1,2);
                
                printf("\n Столбцы: ");
                i = inputNum(1, INT_MAX);
                
                printf("\n Колонки: ");
                j = inputNum(1, INT_MAX);
				
                if(chos == 1 && arrA) {
                    printf("\n%d\n",arrA[i][j]);
                } else if (chos == 2 && arrB) {
                    printf("\n%d\n",arrB[i][j]);
                }
            break;
            case 5:
                printf("\n Выберете матрицу. 1 - A, 2 - B.->");
                chos = inputNum(1,2);
				
                if(chos == 1 && arrA) {
                    printMatrix(nA,nB,arrA);
                } else if (chos == 2 && arrB) {
                    printMatrix(mA,mB,arrB);
                }
            break;
            case 6:
                printf("\n 1 - Сумма\n 2 - Разность\n 3 - Умножить на число\n 4 - Умножить матрицы\n->");
                chos = inputNum(1,4);

                if (arrA && arrB) {
                    if(chos == 1) {
                        arrC = MatrixSum(arrA,arrB,nA,mA,nB,mB);
                    } else if(chos == 2) {
                        arrC = MatrixDifference(arrA,arrB,nA,mA,nB,mB);
                    } else if(chos == 3) {
                        arrA = MatrixMultiplication(arrA,nA,mA);
                    } else if (chos == 4) {
                        arrC = TwoMatrixMultiplication(arrA,arrB,nA,mA,nB,mB);
                    }
                }   
            break;
            case 7:
                printf("\n Столбцы: ");
                i = inputNum(1, INT_MAX);
                
                printf("\n Колонки: ");
                j = inputNum(1, INT_MAX);
				
                if (arrA) {
                    arrA = ResizeMatrix(arrA,nA,mA,i,j);
                    nA = i;
                    mA = j;
                }
            break;
            case 8:
                if (arrA) saveMatrix(arrA,"test.txt", nA, mA);
            break;
            case 9:
                arrA = loadMatrix("test.txt");
            break;
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
	printf("\n 1 - Создать матрицу\n 2 - Удалить матрицу\n 3 - Изменить значение элемента\n"
               " 4 - Получить значение элемента\n 5 - Распечатать матрицу\n"
               " 6 - Операции с матрицами\n 7 - Изменить размер\n 8 - Сохранить\n"
               " 9 - Загрузить\n 0 - Выход\n->");
}

int **ResizeMatrix(int **arrA, int nA, int mA, int n, int m) {
	int i, j;
    int **arrC = CreateMatrix(n,m);
	
    for (i = 0; i < n; i++) {
        for (j = 0; j < m; j++) {
            arrC[i][j] = arrA[i][j];
        }
    }
    return arrC;
}


int saveMatrix(int** A,char* fileName, int rows, int cols) {
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

int** loadMatrix(char* fileName) {
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

    int** A = CreateMatrix(row, col);

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

int **TwoMatrixMultiplication(int **arrA, int **arrB, int nA, int mA, int nB, int mB) {
	int i, j, k;
	
    if (mA == nB) {
        int **arrC = CreateMatrix(nA, mB);
        for (i = 0; i < nA; i++) {
            for (j = 0; j < mB; j++) {
                arrC[i][j] = 0;
                for (k = 0; k < mA; k++) {
                    arrC[i][j] += arrA[i][k] + arrB[k][j];
                }
            }
        }
		
        printMatrix(nA, mB, arrC);
        return arrC;
    } else{
        printf("\n Некорректные размеры матриц");
        return NULL;
    }
}


int **MatrixMultiplication(int **arrA, int nA, int mA) {
    int **arrC = CreateMatrix(nA,mA);
    int num, i, j;
	
    printf("\n Введите число: ");
    scanf("%d", &num);
	
    for (i = 0; i < nA; ++i) {
        for (j = 0; j < mA; ++j) {
            arrC[i][j] = num * arrA[i][j];
        }
    }
    printMatrix(nA,mA,arrC);
    return arrC;
}

int **MatrixSum(int **arrA, int **arrB, int nA, int mA, int nB, int mB) {
	int i, j;
    int **arrC = CreateMatrix(nA,mA);
    if (nA == nB && mA == mB){
        for(i =0; i < nA; i++){
            for (j = 0; j < mA; j++) {
                arrC[i][j] = arrA[i][j] + arrB[i][j];
            }
        }
        printMatrix(nA,mA,arrC);
        return arrC;
    } else{
         printf("\n Некорректные размеры матриц");
        return NULL;
    }
}

int **MatrixDifference(int **arrA, int **arrB, int nA, int mA, int nB, int mB){
    int **arrC = CreateMatrix(nA,mA);
	int i, j;
	
    if (nA == nB && mA == mB) {
		
        for(i =0; i < nA; i++){
            for (j = 0; j < mA; j++) {
                arrC[i][j] = arrA[i][j] - arrB[i][j];
            }
        }
        printMatrix(nA,mA,arrC);
        return arrC;
    } else{
        printf("\n Некорректные размеры матриц");
        return NULL;
    }
}


int **CreateMatrix(int n, int m) {
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
