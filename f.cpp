#include <iostream>
using namespace std;

int board[8][8] = { 0 };//��������� ����� ������ ��� ���������� ��������, ���� ���������� ������ ������

void setQueen(int i, int j)//�������, ������� ������ �����
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
	board[i][j] = -1;//�� ���� ������ ����� �����
	for (int i = 0; i < 8; i++)//������� ������ ����� �������
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
	board[i][j] = 0;//������� ����� � ������
	for (int i = 0; i < 8; i++)//������� ������ ����� �������
	{
		for (int j = 0; j < 8; j++)
		{
			cout << board[i][j];
		}
		cout << endl;
	}
	cout << endl;
}

bool tryQueen(int i)//�������, ������� �������� ��������� ����� �� i-��� �������
{
	bool result = false;//���������� ������, ���� ������� ��������� ����� � ����, ���� ���

	for (int j = 0; j < 8; j++)//�������� ��������� ����� �� 8 ����� �������
	{
		if (board[i][j] == 0)//������ ����� �� ����, ������ ��������
		{
			setQueen(i, j);//�������, ������� ����������� ��������, � ���������� ������, ������� ��� ����

			if (i == 7)//���� ��� �������, ������, �� ��������� ���� �������
				result = true;//������� �������
			else
			{
				result = tryQueen(i+1);//������� ��������� ����� �� ��������� �������
				if (!result)//���� �� ������� ��������� ����� �� ��������� �������
					resetQueen(i, j);//�������, ������� ������� ����� � ������� �������
			}
		}
		if (result)
			break;
	}
	return result;//���� ����� �� �����, ������������ �������, ���� ���, �� ����
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
				cout << " Q ";//��� �������� -1 �������� �����
			else
				cout << " _ ";//��� ����� ������ �������� ������� ������ ������
		}
		cout << endl;
	}
	return 0;
}

