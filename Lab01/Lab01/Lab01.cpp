#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>

using namespace std;

int n1 = 1000;
int m1 = 500;
int n2 = 500;
int m2 = 1200;

//Матрица результата n1 x m2
static int **result;

void randomiseMatrix(int **matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = rand() % 11;
		}
	}
}

//Производит умножение матрицы размером n1 x m1
//на матрицу размером n2 x m2
int** matrixMulti(int **matrix1, int n1, int m1, int **matrix2, int n2, int m2) {
	//Умножение по формуле
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			for (int k = 0; k < m1; k++) {
				result[i][j] += (matrix1[i][k] * matrix2[k][j]);
			}
		}
	}
	return result;
}

int main(int argc, char** argv)
{
	srand(time(NULL));

	//Матрица n1 x m1
	int **matrix1;
	//Матрица n2 x m2
	int **matrix2;

	matrix1 = (int**)malloc(sizeof(int*)*n1);
	for (int i = 0; i < n1; i++) {
		matrix1[i] = (int*)malloc(sizeof(int)*m1);
	}
	matrix2 = (int**)malloc(sizeof(int*)*n2);
	for (int i = 0; i < n2; i++) {
		matrix2[i] = (int*)malloc(sizeof(int)*m2);
	}

	//Генерируем случайные матрицы для умножения
	randomiseMatrix(matrix1, n1, m1);
	randomiseMatrix(matrix2, n2, m2);

	//Выделяем память под результат умножения
	result = (int**)malloc(sizeof(int*)*n1);
	for (int i = 0; i < n1; i++) {
		result[i] = (int*)malloc(sizeof(int)*m2);
	}

	//Обнуляем матрицу результатов
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			result[i][j] = 0;
		}
	}

	//Специальный тип данных из библиотеки time.h
	clock_t currentTime;
	//Берем текущее системное время
	currentTime = clock();

	matrixMulti(matrix1, n1, m1, matrix2, n2, m2);

	//Берем разницу
	currentTime = clock() - currentTime;

	cout << currentTime << " ms";

	/*int t = 0;
	while (t < 100) {
		cout << rand() % 11 << endl;
		t++;
	}*/
	
    return 0;
}