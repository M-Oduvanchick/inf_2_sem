#include <iostream>
using namespace std;

int board[8][8] = { 0 };//заполн€ем доску нул€ми дл€ дальнейших действий, нули обозначают пустые клетки

void setQueen(int i, int j)//функци€, котора€ ставит ферз€
{
	int d;

	for (int x = 0; x < 8; x++)
	{
		board[x][j]++;
		board[i][x]++;
		d = j - i + x;

		if ((0 <= d) && (d <= 7))
		{
			board[x][d]++;
		}

		d = j + i - x;
		if ((0 <= d) && (d <= 7))
		{
			board[x][d]++;
		}
	}
	board[i][j] = -1;//на этой €чейке стоит ферзь
	for (int i = 0; i < 8; i++)//выводит каждый вызов функции
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

void resetQueen(int i, int j)
{
	int d;

	for (int x = 0; x < 8; x++)
	{
		board[x][j]--;
		board[i][x]--;
		d = j - i + x;

		if ((0 <= d) && (d <= 7))
		{
			board[x][d]--;
		}
		d = j + i - x;
		if ((0 <= d) && (d <= 7))
		{
			board[x][d]--;
		}
	}
	board[i][j] = 0;//убирает ферз€ с €чейки
	for (int i = 0; i < 8; i++)//выводит каждый вызов функции
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool tryQueen(int i)//‘ункци€, котора€ пытаетс€ поставить ферз€ на i-тый столбец
{
	bool result = false;//¬озвращает истину, если удалось поставить ферз€ и ложь, если нет

	for (int j = 0; j < 8; j++)//ѕытаемс€ поставить ферз€ на 8 €чеек столбца
	{
		if (board[i][j] == 0)//ячейку никто не бьет, ставим королеву
		{
			setQueen(i, j);//функци€, котора€ расставл€ет королеву, и обозначает €чейки, которые она бьЄт

			if (i == 7)//если это истинна, значит, мы поставили всех королев
				result = true;//попытка успешна
			else
			{
				result = tryQueen(i+1);//пробуем поставить ферз€ на следующий столбец
				if (!result)//если не удалось поставить ферз€ на следующий столбец
					resetQueen(i, j);//функци€, котора€ убирает ферз€ с текущей позиции
			}
		}
		if (result)
			break;
	}
	return result;//если вышли из цикла, возвращаетс€ истинна, если нет, то ложь
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
				cout << board[i][j];
		}
		cout << endl;
	}
}

int main()
{
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
	tryQueen(0);
	for (int i = 0; i < 8; i++)
	{
		for (int j = 0; j < 8; j++)
		{
			if (board[i][j] == -1)
				cout << " Q ";//при значении -1 ставитс€ ферзь
			else
				cout << " _ ";//при любом другом значении остаЄтс€ пуста€ клетка
		}
		cout << endl;
	}
	return 0;
}

