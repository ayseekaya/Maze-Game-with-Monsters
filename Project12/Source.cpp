#include<iostream>
#include<stdlib.h>
#include<Windows.h>
#include<time.h>
#include<conio.h>
#include<fstream>
#include<iomanip>
#define boyut 100
using namespace std;
void labirent(int);
void letxy(int, int);
void motion(int A[][boyut], int n);
int L[boyut][boyut];
char giris;
int main()
{
	remove("Move.txt");
	int  n;
	srand(time(NULL));
	cout << "labirent boyutunu giriniz" << endl;
	cin >> n;
	labirent(n);
	motion(L, n);
	cout << endl << endl;
	system("pause");
	return 0;
}
void labirent(int n)
{
	int i, j, temp, sekil;

	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			if (i == 0 || j == 0 || i == n - 1 || j == n - 1)
			{
				if ((i == 0 && j == 1))
				{
					L[i][j] = 3;     //giris
					//cout << " ";
				}
				else if (i == n - 1 && j == n - 2)
				{
					L[i][j] = 6;     //çýkýþ
				}
				else
				{
					L[i][j] = 1;       //duvar
					//cout << char(219);
				}
			}
			else
			{
				L[i][j] = 0;     //ic
				//cout << " ";
			}
		}

	}
	for (int i = 1; i < n - 1; i++)
	{
		for (int j = 1; j < n - 1; j++)
		{

			if (i == j)
			{
				if (i != n - 2)
				{
					L[i][j] = 2;  //diagonal yol
					L[i][i + 1] = 2;
				}
			}

			else if (L[i][j] == 0)  //diagonal yol deðilse random at
			{
				L[i][j] = rand() % 2;
			}
		}
	}
	for (i = 1; i < n - 1; i++)
	{
		for (j = 1; j < n - 1; j++)
		{
			if (L[i][j] == 0)
			{
				temp = rand() % 3;
				if (temp == 0)
				{
					L[i][j] = 4;//altýn

				}
				else if (temp == 1)
				{
					L[i][j] = 5;//canavar

				}
				else if (temp == 2)
				{
					L[i][j] = 0;//boþluk
				}
			}
		}
	}
	L[n - 2][n - 2] = 7;
	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (L[i][j] == 0)
			{
				cout << " ";
			}
			else if (L[i][j] == 1)
			{
				cout << char(219);
			}
			else if (L[i][j] == 2)
			{
				cout << " ";
			}
			else if (L[i][j] == 3)
			{
				cout << " ";
			}
			else if (L[i][j] == 4)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 6);
				cout << "*";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				continue;
			}
			else if (L[i][j] == 5)
			{
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 12);
				cout << "&";
				SetConsoleTextAttribute(GetStdHandle(STD_OUTPUT_HANDLE), 15);
				continue;
			}
			else if (L[i][j] == 6)
			{
				cout << " ";
			}
			else if (L[i][j] = 7)
			{
				cout << " ";
			}
		}
		cout << endl;
	}

}
void letxy(int x, int y)
{
	COORD coord;
	coord.X = x;
	coord.Y = y + 2;
	SetConsoleCursorPosition(GetStdHandle(STD_OUTPUT_HANDLE), coord);
}
ofstream koordinatlar;
void motion(int A[][boyut], int n)
{
	cout << "Use W,A,S,D to move!" << endl;
	cout << "Info: * is a gold, & is a monster. " << endl;
	int x = 1;
	int y = 0;
	int xcln = 1;
	int ycln = 0;
	int k = 0;

	koordinatlar.open("Move.txt", ios_base::app);
	while (true)
	{
		letxy(xcln, ycln);
		cout << " ";
		letxy(x, y);
		cout << '#';
		giris = _getch();
		xcln = x;
		ycln = y;


		if (giris == 'w' || giris == 'W')
			y -= 1;
		else if (giris == 's' || giris == 'S')
			y += 1;
		else if (giris == 'a' || giris == 'A')
			x -= 1;
		else if (giris == 'd' || giris == 'D')
			x += 1;

		koordinatlar << x << "," << y << "\n";

		if (A[y][x] == 4)
		{
			A[y][x] = 0;
			k++;
		}
		if (A[y][x] == 1)
		{
			x = xcln;
			y = ycln;
		}
		else if (A[y][x] == 5)
		{
			system("cls");
			x = 1;
			y = 0;
			k = 0;
			cout << "\n\n";
			labirent(n);

		}

		else if (A[y][x] == 6)
		{
			cout << endl << endl << "\nCongratulations" << endl;
			cout << "Gold: " << k;
			system("color A");
			break;
		}
	}
}