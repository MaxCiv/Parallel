#include <stdio.h>
#include <tchar.h>
#include <iostream>
#include <ctime>
#include <process.h>
#include <thread>

using namespace std;

int n1 = 1000;
int m1 = 500;
int n2 = 500;
int m2 = 700;

//������� n1 x m1
int **matrix1;
//������� n2 x m2
int **matrix2;
//������� ���������� n1 x m2
int **result;

int counter = 0;
const int threads = 2;

typedef struct
{
	int from;
	int to;
} Params;

Params params[threads];

void matrixMultiThread(void *param) {
	Params *ptr = (Params*)param;
	//��������� �� ������� � ������ from �� ������ to
	for (int i = ptr->from; i < ptr->to; i++) {
		for (int j = 0; j < m2; j++) {
			for (int k = 0; k < m1; k++) {
				result[i][j] += (matrix1[i][k] * matrix2[k][j]);
			}
		}
	}
}

void randomiseMatrix(int **matrix, int n, int m) {
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < m; j++) {
			matrix[i][j] = rand() % 11;
		}
	}
	counter++;
}

int main(int argc, char** argv)
{
	srand(time(NULL));
	
	//�������� ������ ��� ������
	matrix1 = (int**)malloc(sizeof(int*)*n1);
	for (int i = 0; i < n1; i++) {
		matrix1[i] = (int*)malloc(sizeof(int)*m1);
	}
	matrix2 = (int**)malloc(sizeof(int*)*n2);
	for (int i = 0; i < n2; i++) {
		matrix2[i] = (int*)malloc(sizeof(int)*m2);
	}

	//���������� ��������� ������� ��� ���������
	randomiseMatrix(matrix1, n1, m1);
	randomiseMatrix(matrix2, n2, m2);

	//�������� ������ ��� ������� �����������
	int **result = (int**)malloc(sizeof(int*)*n1);;
	for (int i = 0; i < n1; i++) {
		result[i] = (int*)malloc(sizeof(int)*m2);
	}

	//�������� ������� �����������
	for (int i = 0; i < n1; i++) {
		for (int j = 0; j < m2; j++) {
			result[i][j] = 0;
		}
	}

	//��������� ��������� ��� ������� �������
	int from = 0, to;
	int q = m1 / threads,
		r = m1 % threads;

	for (int i = 0; i < threads; i++) {
		params[i].from = from;
		to = from + q + (i < r ? 1 : 0);
		params[i].to = to;
		from = to;
	}

	//����������� ��� ������ �� ���������� time.h
	clock_t currentTime;
	//����� ������� ��������� �����
	currentTime = clock();


	for (int i = 0; i < threads; i++) {
		_beginthread(matrixMultiThread, 0, (void*)&params[i]);
	}


	while (counter != threads);

	//����� �������
	currentTime = clock() - currentTime;
	cout << currentTime << " ms";
	return 0;
}