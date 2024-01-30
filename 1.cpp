#include <iostream>
#include <stdlib.h>
using namespace std; 
const int n = 10;
int main()
{
	setlocale(LC_ALL, "RU");
	int max;
	int s = 0;
	int j = 0;
	int a[n];
	srand(time(NULL));

	for (int i = 0; i < n; i++)
	{
		a[i] = rand() % 200 - 100 ;
	}
	
	max = a[0];

	for (int i = 0; i < n; i++)
	{
		if (a[i] > max)
		{
			max = a[i];
			s = 1;
			j = i;
		}
		else
			if (a[i] == max)
				s++;
	}

	for (int i = 0; i < n; i++)
	{
		cout << a[i] << endl;
	}

	cout << "Максимальный элемент = " << max << endl;
	cout << "Номер = " << j + 1 << endl;
	cout << "Количество максимиальных элементов = " << s << endl;

	return 0;
}