#include <iostream>
#include <math.h>
#include <ctime>
#include<chrono>

using namespace std;

const int N = 500000;


int intcmp(const void* a, const void* b)
{
	return *(int*)a - *(int*)b;
}


/////////////////////////////////////////////////////////// ЛИНЕЙНЫЙ ПОИСК //////////////////////////////////////////////////////////////////////

int LinearSearch(int A[], int n, int value) 
{
	int i = 0;
	for (i; i < n; i++) 
	{
		if (A[i] == value) 
		{
			cout << "Искомое число находится по следующему индексу: " << i << endl;
			return i;
		}
	}
	cout << "Искомое число не найдено" << endl;
	return -1;
}


//////////////////////////////////////////////////////////// ДВОИЧНЫЙ ПОИСК /////////////////////////////////////////////////////////////////

int BinarySearch(int A[], int left, int right, int value) 
{
	int mid;
	while (1) 
	{
		mid = (left + right) / 2;
		if (value == A[mid]) 
		{
			cout << "Искомое число находится по следующему индексу: " << mid << endl;
			return mid;
		}
		if (value < A[mid]) 
		{
			right = mid - 1;
		}
		if (value > A[mid]) 
		{
			left = mid + 1;
		}
		if (left > right) 
		{
			cout << "Искомое число не найдено" << endl; 
			return -1;
		}
	}
}


/////////////////////////////////////////////////////////////// ПОИСК ПРЫЖКАМИ ///////////////////////////////////////////////////////////////////////

int jumpSearch(int A[], int n, int value) 
{
	int jumpStep = (int)sqrt(n);
	if (A[jumpStep - 1] == value) 
	{
		cout << "Искомое число находится по следующему индексу: " << jumpStep - 1 << endl;
		return jumpStep - 1;
	}
	int previousStep = 0;
	while (A[(min(jumpStep, n) - 1)] < value) 
	{
		previousStep = jumpStep;
		jumpStep += (int)sqrt(n);
		if (previousStep >= n) 
		{
			cout << "Искомое число не найдено" << endl;
			return -1;
		}
	}
	while (A[previousStep] < value) 
	{
		previousStep++;
		if (previousStep == min(jumpStep, n)) 
		{
			cout << "Искомое число не найдено" << endl;
			return -1;
		}
	}
	if (A[previousStep] == value) 
	{
		cout << "Искомое число находится по следующему индексу: " << previousStep << endl;
		return previousStep;
	}
	else 
	{
		cout << "Искомое число не найдено" << endl;
		return -1;
	}
}


///////////////////////////////////////////////////////// ИНТЕРПОЛЯЦИОННЫЙ ПОИСК /////////////////////////////////////////////////////////////
 
int InterpolationSearch(int A[], int n, int value) 
{
	int start = 0;
	int end = n - 1;
	while ((start <= end) && (value >= A[start]) && (value <= A[end])) 
	{
		int pos = start + (value - A[start]) * (end - start) / (A[end] - A[start]);
		if (A[pos] == value) 
		{
			cout << "Искомое число находится по следующему индексу: " << pos << endl;
			return pos;
		}
		if (A[pos] < value) 
		{
			start = pos + 1;
		}
		else 
		{
			end = pos - 1;
		}
	}
	if (A[start] == value) 
	{
		cout << "Искомое число находится по следующему индексу: " << start << endl;
		return start;
	}
	else
		if (A[end] == value) 
		{
			return end;
			cout << "Искомое число находится по следующему индексу: " << end << endl;
		}
		else 
		{
			cout << "Искомое число не найдено" << endl;
			return -1;
		}
}


/////////////////////////////////////////////////////////// ЭКСПОНЕНЦИАЛЬНЫЙ ПОИСК /////////////////////////////////////////////////////////////////

int ExponentialSearch(int A[], int n, int value) 
{
	if (A[0] == value) 
	{
		cout << "Искомое число находится по следующему индексу: " << 0 << endl;
		return 0;
	}
	int range = 1;
	while (range < n && A[range] <= value) 
	{
		range = range * 2;
	}
	return BinarySearch(A, range / 2, min(range, n), value);
}


//////////////////////////////////////////////////////////////////////// ПОИСК ФИБОНАЧЧИ /////////////////////////////////////////////////////////////////

int FibonachiSearch(int A[], int n, int value) 
{
	int FibPrevPrev = 0;
	int FibPrev = 1;
	int Fib = FibPrevPrev + FibPrev;
	while (Fib < n) 
	{
		FibPrevPrev = FibPrev;
		FibPrev = Fib;
		Fib = FibPrevPrev + FibPrev;
	}
	int index = -1;
	while (Fib > 1) 
	{
		int i = min((index + FibPrevPrev), (n - 1));
		if (A[i] == value) 
		{
			cout << "Искомое число находится по следующему индексу: " << i << endl;
			return i;
		}
		if (A[i] < value) 
		{
			Fib = FibPrev;
			FibPrev = FibPrevPrev;
			FibPrevPrev = Fib - FibPrev;
			index = i;
		}
		if (A[i] > value) 
		{
			Fib = FibPrevPrev;
			FibPrev = FibPrev - FibPrevPrev;
			FibPrevPrev = Fib - FibPrev;
		}
	}
	if (FibPrev and index < (n - 1) and A[index + 1] == value) 
	{
		cout << "Искомое число находится по следующему индексу: " << index + 1 << endl;
		return index + 1;
	}
}


void main()
{
	setlocale(LC_ALL, "Russian");
	int* A = new int[N] {};
	//int B[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16 };
	//int nB = sizeof(B) / sizeof(B[0]);
	//int A[N] = {};
	int value;
	int val1;
	srand(time(NULL));
	for (int i = 0; i < N; i++)
	{
		A[i] = rand();
	}
	qsort(A, N, sizeof(int), intcmp); 
	//int n = sizeof(A) / sizeof(A[0]);
	int n = _msize(A) / sizeof(int);
	/*for (int k = 0; k < n; k++)
	{
		cout << A[k] << "   ";
	}*/
	cout << A[0];  
	cout << endl;
	cout << "Введите искомое значение: " << " ";
	cin >> value;
	auto begin = std::chrono::steady_clock::now();
	//LinearSearch(A, n, value); 
	//BinarySearch(A, 0, n, value); 
	//jumpSearch(A, n, value); 
	//InterpolationSearch(A, n, value);  
	//ExponentialSearch(A, n, value);
	FibonachiSearch(A, n, value);
	auto end = std::chrono::steady_clock::now();
	auto elapsed_ms = std::chrono::duration_cast<std::chrono::microseconds>(end - begin);
	cout << "The time: " << elapsed_ms.count() << " microsec" << endl;

}