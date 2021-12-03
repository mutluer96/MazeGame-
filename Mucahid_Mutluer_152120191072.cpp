#include<iostream>
#include<cstdlib> 
#include<conio.h>
#include<ctime>
#include<fstream>
#include<Windows.h>
using namespace std;

ofstream cikti;

int fRand(int fMax, int fMin)//once ust sonra alt siniri parametre al
{
	int f = ((rand() % (fMax - fMin + 1)) + fMin);
	return f;
}

void imlecGizle()
{
	HANDLE stout = GetStdHandle(STD_OUTPUT_HANDLE);
	CONSOLE_CURSOR_INFO cursorInfo;

	GetConsoleCursorInfo(stout, &cursorInfo);
	cursorInfo.bVisible = false;
	SetConsoleCursorInfo(stout, &cursorInfo);
}

void schreibe_karte(char** &karte, int n)
{
	int i, j;

	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			if (i == 0 || j == 0 || i == n - 1 || j == n - 1)
			{
				if ((i == 0 && j == 1) || (i == n - 1 && j == n - 2))
				{
					karte[i][j] = char(32);
				}
				else
				{
					karte[i][j] = char(178);
				}
			}
		}
	}


	int modulo, scenerio;
	for (i = 1; i < n - 1; i++)
	{
		for (j = 1; j < n - 1; j++)
		{
			if ((i == j) || (i == j + 1))
			{
				karte[i][j] = 'k';
			}
			else if ((i == 1) || (j == n - 2))
			{
				karte[i][j] = 'a';
			}
			else
			{
				modulo = fRand(1, 0);

				if (modulo == 0)
				{
					karte[i][j] = char(178);
				}
				if (modulo == 1)
				{
					karte[i][j] = char(32);
				}
			}
		}
	}

	scenerio = fRand(1, 0);

	if (scenerio == 0)
	{
		for (i = 1; i < n - 1; i++)
		{
			for (j = 1; j < n - 1; j++)
			{
				if (karte[i][j] == char(32))
				{
					modulo = fRand(2, 0);

					if (modulo == 0)
					{
						continue;
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
					else if (modulo == 2)
					{
						karte[i][j] = char(64);
					}
				}
				else if (karte[i][j] == 'k')
				{
					int modulo = fRand(2, 0);

					if (modulo == 0)
					{
						karte[i][j] = char(32);
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
					else if ((modulo == 2))
					{
						karte[i][j] = char(64);
					}
				}
				else if (karte[i][j] == 'a')
				{
					int modulo = fRand(1, 0);
					if (modulo == 0)
					{
						karte[i][j] = char(32);
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
				}
			}
		}
	}
	if (scenerio == 1)
	{
		for (i = 1; i < n - 1; i++)
		{
			for (j = 1; j < n - 1; j++)
			{
				if (karte[i][j] == char(32))
				{
					modulo = fRand(2, 0);

					if (modulo == 0)
					{
						continue;
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
					else if (modulo == 2)
					{
						karte[i][j] = char(64);
					}
				}
				else if (karte[i][j] == 'k')
				{
					int modulo = fRand(1, 0);

					if (modulo == 0)
					{
						karte[i][j] = char(32);
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
				}
				else if (karte[i][j] == 'a')
				{
					int modulo = fRand(2, 0);

					if (modulo == 0)
					{
						karte[i][j] = char(32);
					}
					else if (modulo == 1)
					{
						karte[i][j] = char(42);
					}
					else if (modulo == 2)
					{
						karte[i][j] = char(64);
					}
				}
			}
		}
	}

	karte[1][1] = char(32);//this and the below evaluating to char(32)
	karte[2][1] = char(32);// are aiming to avoid deadend at maze
	karte[n - 2][n - 2] = char(32);//because the two different scenerio 
	karte[n - 2][n - 3] = char(32);//can collide and create unexpected obstuctions at map
	karte[n - 1][n - 2] = char(32);//escape from maze


	for (i = 0; i < n; i++)
	{
		for (j = 0; j < n; j++)
		{
			cout << karte[i][j];
		}
		cout << endl;
	}
}

void setpos(int x, int y)
{
	HANDLE sth = GetStdHandle(STD_OUTPUT_HANDLE);
	COORD pos;
	pos.X = x;
	pos.Y = y + 2;
	SetConsoleCursorPosition(sth, pos);
}

void spiel(char** &karte, int n)
{
	char bak;
	int x = 1, y = 0;
	int bellekx = 1, belleky = 0;
	int Au = 0;

	cikti.open("ciktilar.txt");

	while (true)
	{
		setpos(bellekx, belleky);
		cout << " ";
		setpos(x, y);
		cout << "0";
		bak = _getch();
		bellekx = x;
		belleky = y;

		if ((bak == char('W')) || (bak == char('w')))
		{
			if (y <= 0) //in this condition giving 'w' command causes access violation
			{
				y = belleky;
			}
			else
			{ 
				y = y - 1;
			}
		}
		else if ((bak == char('S')) || (bak == char('s')))
		{
			y = y + 1;
		}
		else if ((bak == char('D')) || (bak == char('d')))
		{
			x = x + 1;
		}
		else if ((bak == char('A')) || (bak == char('a')))
		{
			x = x - 1;
		}

		cikti << x << "," << y << "\n";

		if (karte[y][x] == char(42))
		{
			karte[y][x] = char(32);
			Au++;
		}
		if (karte[y][x] == char(178))
		{
			x = bellekx;
			y = belleky;
		}
		if (karte[y][x] == char(64))
		{
			x = 1;
			y = 0;
			Au = 0;
		}
		if ((y == (n - 1)) && (x == (n - 2)))
		{
			system("Cls");
			cout << endl << "You Are Victorious\n";
			cout << "You Have " << Au << " Coins";
			//PlaySound("AoE2Victory.wav", NULL, SND_SYNC);//by adding to linker input Winmm.lib
			break;
		}
	}
}


int main()
{
	imlecGizle();
	int n;
	srand(time(NULL));
	cout << "Please enter size: ";
	cin >> n;
	while ((n > 100) || (n < 3))
	{
		if (n < 3)
		{
			cout << "To avoid access violation please enter size in between 3-100 :\t";
		}
		else
		{
			cout << "Oops please enter size again in between 3-100 :\t";
		}
		cin >> n;
	}
	system("Cls");

	char** karte = new char*[n];
	for (int i = 0; i < n; i++)
	{
		karte[i] = new char[n];
	}

	cout << endl << endl;//the number of endl is crucial to avoid bug after calling Cls
	schreibe_karte(karte, n);

	cout << "Avoid monsters (@), they steal your gold and throw you beginning\n";
	cout << "Controls WASD";

	spiel(karte, n);

	for (int i = 0; i < n; i++)
	{
		delete[] karte[i];
	}
	delete[] karte;
	karte = NULL;

	cout << endl;
	system("pause");
	return 0;
}







