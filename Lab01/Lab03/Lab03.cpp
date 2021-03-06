#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <fstream>

#include <omp.h>

using namespace std;

const int threads = 8;

void randomiseMatrix(int **matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = rand() % 11;
		}
	}
}

int main(int argc, char** argv) {
	srand(time(NULL));
	int n1 = 1000;
	int m1 = 500;
	int n2 = 500;
	int m2 = 1200;

	//Матрица n1 x m1
	int **matrix1;
	//Матрица n2 x m2
	int **matrix2;

	//Выделяем память для матриц
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

	//Выделяем память для матрицы результатов
	int **result = (int**)malloc(sizeof(int*)*n1);;
	for (int i = 0; i < n1; i++) {
		result[i] = (int*)malloc(sizeof(int)*m2);
	}

	//Обнуляем матрицу результатов
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			result[i][j] = 0;
		}
	}

	//Запрещаем библиотеке openmp менять число потоков во время исполнения
	omp_set_dynamic(0);

	//Устанавливаем число потоков
	omp_set_num_threads(threads);


	//Специальный тип данных из библиотеки time.h
	clock_t currentTime;
	//Берем текущее системное время
	currentTime = clock();

	int i, j, k;
#pragma omp parallel for shared(matrix1, matrix2, result) private(i, j, k)
	for (i = 0; i < n1; i++) {
		for (j = 0; j < m2; j++) {
			for (k = 0; k < m1; k++) {
				result[i][j] += (matrix1[i][k] * matrix2[k][j]);
			}
		}
	}

	//Берем разницу
	currentTime = clock() - currentTime;
	cout << currentTime << " ms";

	//Cоздаём объект класса ofstream для записи и связываем его с файлом OpenMP.txt
	ofstream fout("OpenMP_8.txt", ios_base::app);
	fout << currentTime << endl;
	fout.close();

	return 0;
}