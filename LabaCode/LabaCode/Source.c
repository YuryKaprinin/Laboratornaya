#include "stdio.h"
#include "stdlib.h"
#include "time.h"
#include "windows.h"
#include "locale.h"

void randArray(int A[], int n)
{
	int i;
	srand(time);

	for (i = 0; i < n; i++)
	{
		A[i] = rand() % 10;
	}
}

void vvod(int A[], int n)
{
	int i;

	printf("Введите массив из 10 символов\n");

	for (int i = 0; i < n; ++i)
	{
		scanf_s("%d", &A[i]);
	}
}

void print(int a[], int n)
{
	int i;

	for (i = 0; i < n; i++)
	{
		printf("%d  ", a[i]);
	}
}

int Slianie(int* B, int mid, int l, int r, int* nc, int* nsw)
{
	int i = l;
	int j = mid + 1;
	int s = 0;
	int g = r - l + 1;
	int* k;
	k = (int*)malloc(sizeof(int) * g);
	while (i <= mid && j <= r)
	{
		if (B[i] < B[j])
		{
			k[s] = B[i];
			s++;
			i++;
			(*nsw)++;
		}
		else
		{
			k[s] = B[j];
			s++;
			j++;
			(*nsw)++;
		}
	}
	(*nc)++;
	while (i <= mid)
	{
		k[s] = B[i];
		s++;
		i++;
		(*nsw)++;
	}
	while (j <= r)
	{
		k[s] = B[j];
		s++;
		j++;
		(*nsw)++;
	}
	for (s = 0; s < g; s++)
	{
		B[l + s] = k[s];
	}
	free(k);
}
int Slianie1(int* B, int l, int r, int* nc, int* nsw)
{
	int mid;
	if (l < r)
	{
		mid = (l + r) / 2;
		Slianie1(B, l, mid, &(*nc), &(*nsw));
		Slianie1(B, mid + 1, r, &(*nc), &(*nsw));
		Slianie(B, mid, l, r, &(*nc), &(*nsw));
	}
	(*nc)++;
}
int BubbleSort(int* B, int n, int* nc, int* nsw)
{
	int i, tmp, j;
	int max = n - 1;
	int min = 0;
	(*nc)++;
	for (i = 0; i < n; i++)
	{
		(*nc)++;
		for (j = min; j < max; j++)
		{
			(*nc)++;
			if (B[j] > B[j + 1])
			{
				tmp = B[j];
				B[j] = B[j + 1];
				B[j + 1] = tmp;
				(*nsw)++;
			}
		}
		tmp = 0;
		for (j = max; j > min; j--)
		{
			(*nc)++;
			if (B[j] < B[j - 1])
			{
				tmp = B[j];
				B[j] = B[j - 1];
				B[j - 1] = tmp;
				(*nsw)++;
			}
		}
	}
}

int InsertSort(int* B, int n, int* nc, int* nsw)
{
	int i, j, tmp;
	(*nc)++;
	for (i = 1; i < n; i++)
	{
		tmp = B[i];
		j = i - 1;
		(*nc)++;
		while (j >= 0 && B[j] > tmp)
		{
			B[j + 1] = B[j];
			j--;
			(*nc)++;
			(*nsw)++;
		}
		B[j + 1] = tmp;
		(*nsw)++;
	}
}


void linear(int A[], int n, int* nc)
{
	int k;
	int pos = -1;
	int i;

	printf("Введите число, которое нужно найти\n");
	scanf_s("%d", &k);

	for (i = 0; i < n; i++)
	{
		*nc = *nc + 1;
		if (A[i] == k)
		{
			printf("элемент %d на позиции %d\n", k, i + 1);
			break;
		}
	}
	*nc = *nc + 1;
	if (i == n)
		printf("Элемент %d не найден\n", k);
}

void binar(int A[], int n, int* nc)
{
	int k;
	int left, right, mid;

	printf("Введите число, которое нужно найти\n");
	scanf_s("%d", &k);

	left = 0;
	right = n - 1;
	mid = (left + right) / 2;

	*nc = *nc + 1;
	while (left <= right)
	{
		*nc = *nc + 1;
		if (A[mid] < k)
		{
			left = mid + 1;
		}
		else
			*nc = *nc + 1;
		if (A[mid] == k)
		{
			printf("элемент %d на позиции %d .\n", k, mid + 1);
			break;
		}
		else
			right = mid - 1;
		mid = (left + right) / 2;
	}
	*nc = *nc + 1;
	if (left > right)
		printf("Элемент %d не найден\n", k);
}

void menu()
{
	{
		
		printf("\nMENU:\n");

		printf("\nКак задать массив?\n");
		printf("1. Сгенерировать  \n");
		printf("2. Ввести самому \n");
		printf("\n3. Вывести массив  \n");
		printf("\nКаким методом искать элемент?\n");
		printf("4. Линейный поиск\n");
		printf("5. Бинарный поиск\n");
		printf("\nВыберите метод сортировки\n");
		printf("6. Сортировка слиянием\n");
		printf("7. Сортировка пузырьком\n");
		printf("8. Сортировка вставками\n");
		printf("0. exit\n");
		
	}
}

void main()
{
	setlocale(LC_ALL, "Russian");
	int A[10];
	int n = 10;
	int t = 100;
	int left = 0, right = n - 1;
	LARGE_INTEGER start, finish, freq;
	double time;
	int l=0;
	int r=0;
	QueryPerformanceFrequency(&freq);

	while (t != 0)
	{
		menu();
		scanf_s("%d", &t);
		switch (t)
		{
		case 1:
		{
			randArray(A, n);
			break;
		}
		case 2:
		{
			vvod(A, n);
			break;
		}
		case 3:
		{
			print(A, n);
			break;
		}
		case 4:
		{
			int nc = 0;
			QueryPerformanceCounter(&start);
			linear(A, n, &nc);
			QueryPerformanceCounter(&finish);
			time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			printf("\nВремя = %lf\n", time);
			printf("Сравнения %d\n", nc);
			break;
		}
		case 5:
		{
			int nc = 0;
			QueryPerformanceCounter(&start);
			binar(A, n, &nc);
			QueryPerformanceCounter(&finish);
			time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			printf("\nВремя = %lf\n", time);
			printf("Сравнения %d\n", nc);
			break;
		}
		case 6:
		{
			int nc = 0, nsw = 0;
			QueryPerformanceCounter(&start);
			Slianie1(A, 0, n - 1, &nc, &nsw);
			print(A, n);
			QueryPerformanceCounter(&finish);
			time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			printf("\nВремя = %lf\n", time);
			printf("Перестановок: %d Сравнений: %d\n", nsw, nc);
			break;
		}
		case 7:
		{
			int nc = 0, nsw = 0;
			QueryPerformanceCounter(&start);
			BubbleSort(A, n, &nc, &nsw);
			print(A, n);
			QueryPerformanceCounter(&finish);
			time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			printf("\nВремя = %lf\n", time);
			printf("Перестановок: %d Сравнений: %d\n", nsw, nc);
			break;
		}
		case 8:
		{
			int nc = 0, nsw = 0;
			QueryPerformanceCounter(&start);
			InsertSort(A, n, &nc, &nsw);
			print(A, n);
			QueryPerformanceCounter(&finish);
			time = (double)(finish.QuadPart - start.QuadPart) / (double)freq.QuadPart;
			printf("\nВремя = %lf\n", time);
			printf("Перестановок: %d Сравнений: %d\n", nsw, nc);
			break;
		}
		}
	}
}
