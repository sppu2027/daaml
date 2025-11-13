#include <bits/stdc++.h>
using namespace std;
int knapsack_dp(int n, int M, int w[], int p[]) {
	int i, j;
	int knapsack[n+1][M+1];
	for (j = 0; j <= M; j++)
		knapsack[0][j] = 0;
	for (i = 0; i <= n; i++)
		knapsack[i][0] = 0;
	for (i = 1; i <= n; i++) {
		for (j = 1; j <= M; j++) {
			if (w[i-1] <= j) {
				knapsack[i][j] = max(knapsack[i-1][j],
				p[i-1] + knapsack[i-1][j - w[i-1]]);
			}
			else {
				knapsack[i][j] = knapsack[i-1][j];
			}
		}
	}
	return knapsack[n][M];
}
int main() {
	int n = 4;
	int M = 5;
	int w[] = {2, 1, 3, 2};
	int p[] = {12, 10, 20, 15};
	cout << "Maximum profit = " << knapsack_dp(n, M, w, p);
	return 0;
}

// Time Complexity and Space O(n × M)
// Space Complexity O(n × M)

