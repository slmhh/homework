// C++ program to check if a given instance of N*N-1
// puzzle is solvable or not
#include <iostream>
#define N 3
const int n = 3;
using namespace std;

bool isSolvable(int arr[3][3])
{
	int inv_count = 0;
	for (int i = 0; i < N * N - 1; i++)
		for (int j = i + 1; j < N * N; j++)
			if (arr[j / n][j % n] && arr[i / n][j % n] && arr[i / n][j % n]  > arr[j / n][j % n])
				inv_count++;
	return inv_count & 1;
}

/* Driver program to test above functions */
int main()
{

	int puzzle[N][N] = { {1,2,3},
						 {8,0,4},
						 {7,6,5} };
	/*
	int puzzle[N][N] = {{1, 8, 2},
					{0, 4, 3},
					{7, 6, 5}};

	int puzzle[N][N] = {
					{13, 2, 10, 3},
					{1, 12, 8, 4},
					{5, 0, 9, 6},
					{15, 14, 11, 7},
				};

	int puzzle[N][N] = {
					{6, 13, 7, 10},
					{8, 9, 11, 0},
					{15, 2, 12, 5},
					{14, 3, 1, 4},
				};


	int puzzle[N][N] = {
					{3, 9, 1, 15},
					{14, 11, 4, 6},
					{13, 0, 10, 12},
					{2, 7, 8, 5},
				};
	*/

	isSolvable(puzzle)? cout << "Solvable":
						cout << "Not Solvable";
	return 0;
}

