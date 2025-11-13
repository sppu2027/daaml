#include <iostream>
#include <cmath>
using namespace std;
int x[20]; // x[k] = column position of queen in row k
int solutionCount = 0;
// Function to check if a queen can be placed at row k, column i
bool Place(int k, int i) {
	for (int j = 1; j < k; j++) {
		if (x[j] == i || abs(x[j] - i) == abs(j - k)) {
			return false; // same column or diagonal
		}
	}
	return true;
}
// Recursive function to solve N-Queens
void NQueens(int k, int n) {
	for (int i = 1; i <= n; i++) {
		if (Place(k, i)) {
			x[k] = i;
			if (k == n) {
				solutionCount++;
				cout << "Solution " << solutionCount << ": ";
				for (int j = 1; j <= n; j++) {
					cout << x[j] << " ";
				}
				cout << endl;
			} else {
				NQueens(k + 1, n);
			}
		}
	}
}
int main() {
	int n; //4 ≤ n ≤ 10
	cout << "Enter number of queens: ";
	cin >> n;
	NQueens(1, n);
	cout << "Total number of solutions = " << solutionCount << endl;
	return 0;
}
// TC : O(n x n!)
// SC : O(n)
//Uses Backtracking