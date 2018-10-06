#include <iostream>
#include <windows.h>
#include <time.h>

using namespace std;

void initMatrix(bool **matrix, int n, int m);
void initCache(bool **cache[], int cacheCount, int n, int m);
bool isInCache(bool **a, bool **cache[], int cacheCount, int n, int m);
void saveCache(bool **a, bool **cache[], int cacheCount, int n, int m);
void fillMatrix(bool **matrix, int n, int m);
void showMatrix(bool **matrix, int n, int m);
void nextGeneration(bool **a, bool **b, int n, int m);
bool isLife(bool **a, int row, int col, int n, int m);
void copyMatrix(bool **a, bool **b, int n, int m);
bool isMatrixSame(bool **a, bool **b, int n, int m);
bool isMatrixInCache(bool **a, bool **b, int n, int m);
bool isMatrixEmpty(bool **a, int n, int m);

int main() {
	
	int n = 20; // 25  || 60 
	int m = 20; //119  || 209
	int cacheCount = 20;

	bool **a = new bool*[n];
	bool **b = new bool*[n];
	bool ***cache = new bool**[cacheCount];
	
	initCache(cache, cacheCount, n, m);
	
	initMatrix(a, n, m);
	initMatrix(b, n, m);
	
	srand(time(NULL));
	fillMatrix(a, n, m);
	showMatrix(a, n, m);
	
	do {
		saveCache(a, cache, cacheCount, n, m);
		nextGeneration(a, b, n, m);		
		showMatrix(a, n, m);
	} while (!isMatrixEmpty(a, n, m)  && !isInCache(a,cache,cacheCount,n,m)); 

	delete[] a;
	delete[] b;
	delete[] cache;
}

void initMatrix(bool **a, int n, int m) {
	for (int i = 0; i < n; ++i) {
		a[i] = new bool[m];
	}
}

void initCache(bool **cache[], int cacheCount, int n, int m) {
	for(int i = 0; i < cacheCount; ++i) {
		cache[i] = new bool*[n];
		initMatrix(cache[i], n, m);
	}
}

void saveCache(bool **a, bool **cache[], int cacheCount, int n, int m) {
	for(int i = cacheCount - 1; i >= 0; i -= 2 ) {
		copyMatrix(cache[i], cache[i-1], n, m);
	}
	copyMatrix(cache[0], a, n, m);
}

bool isInCache(bool **a, bool **cache[], int cacheCount, int n, int m) {
	for(int i = 0; i < cacheCount; ++i) {
		if (isMatrixSame(a, cache[i], n, m))  {
			return true;
		}
	}
	return false;
}

void fillMatrix(bool **a, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			a[i][j] = rand() % 2;
		}
	}
}

void moveConsoleCursorToHome() {
	HANDLE hOut;
    COORD Position;

    hOut = GetStdHandle(STD_OUTPUT_HANDLE);

    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut, Position);
}

void showMatrix(bool **a, int n, int m) {
	moveConsoleCursorToHome();
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j]) {
				cout << char(219);
			}
			else {
				cout << " ";
			}
		}
		cout << endl;
	}
//	Sleep(200);
}

void nextGeneration(bool **a, bool **b, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			b[i][j] = isLife(a, i, j, n, m);
		}
	}
	copyMatrix(a, b, n, m);
}

bool isLife(bool **a, int row, int col, int n, int m) {
	int count = 0;
	int startRow;
	int startCol;

	if (n > row + 2) { n = row + 2; }
	if (m > col + 2) { m = col + 2;	}

	if (row - 1 < 0) { 
		startRow = 0; 
	} else {
		startRow = row - 1;	
	}

	if (col - 1 < 0) {
		startCol = 0;
	}
	else {
		startCol = col - 1;
	}

	for (int i = startRow; i < n; ++i) {
		for (int j = startCol; j < m; ++j) {
			if (a[i][j] && !(i == row && j == col)) {
				count++;
			}
		}
	}

	if (a[row][col]) {
		return !(count != 2 && count != 3);
	}
	else {
		return count == 3;
	}

}

void copyMatrix(bool **a, bool **b, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			a[i][j] = b[i][j];
		}
	}
}

bool isMatrixSame(bool **a, bool **b, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if(a[i][j] != b[i][j]) {
				return false;
			}
		}
	}
	cout << "same";
	return true;
}

bool isMatrixEmpty(bool **a, int n, int m) {
	for (int i = 0; i < n; ++i) {
		for (int j = 0; j < m; ++j) {
			if (a[i][j]) {
				return false;
			}
		}
	}
	cout << "empty";
	return true;
}
