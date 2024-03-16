#include <iostream>
#include <iomanip>

/* Sample input
0 0 0 5 8 0 0 0 2
8 2 9 3 7 0 6 5 0
0 3 6 1 9 0 7 4 8
0 0 0 0 3 0 1 6 0
0 1 0 0 0 8 0 0 0
6 0 2 0 0 0 4 0 3
1 0 8 0 0 3 0 7 0
0 0 0 0 6 0 0 0 4
0 6 5 0 2 7 0 0 0
*/

using namespace std;

bool InitiateSolver(int Matrix[9][9]);
bool Solver(int Matrix[9][9], int x, int y);
bool TestFit(int Matrix[9][9], int x, int y, int key);	//sample calling TestFit(Matrix, x-coordinate, y-coordinate)



void Swap(int &x, int &y);

int main()
{
	int MainMatrix[9][9];
	int cfm = 0;

	while (cfm != 1)
	{
		cout << "Enter the sudoku matrix here to solve:" << endl;

		for (int x = 0; x < 9; x++)
		{
			if (x == 3 || x == 6)
			{
				cout << endl;
			}
			for (int y = 0; y < 9; y++)
			{
				cin >> MainMatrix[x][y];
			}
		}
		cout << endl << "------------------------------------" << endl;

		for (int x = 0; x < 9; x++)
		{
			if (x == 3 || x == 6)
			{
				cout << endl;
			}
			for (int y = 0; y < 9; y++)
			{
				if (y == 3 || y == 6)
				{
					cout << "  ";
				}
				cout << MainMatrix[x][y] << " ";
			}
			cout << endl;
		}

		cout << "Pls enter 1 to proceed: ";
		cin >> cfm;
	}

	if (InitiateSolver(MainMatrix))
	{
		for (int x = 0; x < 9; x++)
		{
			if (x == 3 || x == 6)
			{
				cout << endl;
			}
			for (int y = 0; y < 9; y++)
			{
				if (y == 3 || y == 6)
				{
					cout << "  ";
				}
				cout << MainMatrix[x][y] << " ";
			}
			cout << endl;
		}
		system("pause");

		return 1;
	}
	else
	{
		cout << "solution not found!";
		system("pause");

		return 0;
	}
}

bool InitiateSolver(int Matrix[9][9])
{
	return Solver(Matrix, 0, 0);
}

bool Solver(int Matrix[9][9], int x, int y)
{
	if (y >= 9)
	{
		y = 0;
		x++;
	}

	/*for (int xtemp = 0; xtemp < 9; xtemp++)
	{
		for (int ytemp = 0; ytemp < 9; ytemp++)
		{
			cout << Matrix[xtemp][ytemp] << " ";
		}
		cout << endl;
	}
	cout << y << "," << x << endl;*/

	if (Matrix[x][y] != 0)
	{
		if (y == 8 && x == 8)
		{
			return true;
		}
		else
		{
			if (Solver(Matrix, x, y + 1))
			{
				return true;
			}
		}
	}
	else
	{
		for (int i = 1; i <= 9; i++)
		{
			//cout << TestFit(Matrix, y, x, i) << " " << i << endl;
			if (TestFit(Matrix, y, x, i))
			{
				//cout << y << "," << x << endl;
				Matrix[x][y] = i;
				if (y == 8 && x == 8)
				{

					return true;
				}
				else
				{
					if (Solver(Matrix, x, y + 1))
					{
						return true;
					}
					//cout << y << "," << x << endl;
				}
			}
		}
		Matrix[x][y] = 0;
	}

	return false;
}

bool TestFit(int Matrix[9][9], int x, int y, int key)
{
	Swap(x, y);	//swap as 2d array value stored as [y][x]

	int xSeg;
	int ySeg;

	int b9x[9] = { 0, 1, 0, -1, 0, 1, -1, -1, 1 };     //9 box for x
	int b9y[9] = { 0, 0, 1, 0, -1, 1, -1, 1, -1 };     //9 box for y

	//finding which segment the value is in
	if (x >= 0 && x <= 2) { xSeg = 1; }
	else if (x >= 3 && x <= 5) { xSeg = 2; }
	else if (x >= 6 && x <= 8) { xSeg = 3; }

	if (y >= 0 && y <= 2) { ySeg = 1; }
	else if (y >= 3 && y <= 5) { ySeg = 2; }
	else if (y >= 6 && y <= 8) { ySeg = 3; }

	for (int i = 0; i < 8; i++)
	{
		if (Matrix[b9x[i] + xSeg * 3 - 2][b9y[i] + ySeg * 3 - 2] == key)
		{
			return false;
		}
	}



	for (int ycoord = 0; ycoord < 9; ycoord++)	//test y-axis
	{
		if (ycoord != y)
		{
			if (key == Matrix[x][ycoord])
			{
				return false;
			}
		}
	}
	for (int xcoord = 0; xcoord < 9; xcoord++)	//test x-axis
	{
		if (xcoord != x)
		{
			if (key == Matrix[xcoord][y])
			{
				return false;
			}
		}
	}
	return true;
}

void Swap(int &x, int &y)
{
	int temp = x;
	x = y;
	y = temp;
}
