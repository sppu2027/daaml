#include <bits/stdc++.h>
using namespace std;
#define INF INT_MAX

int n, cost[20][20], bestCost = INF;
vector<int> bestPath;

int reduce(int m[20][20]) {
    int red = 0;
    for (int k = 0; k < 2; k++) { // row & col reduction
        for (int i = 0; i < n; i++) {
            int mn = INF;
            for (int j = 0; j < n; j++)
                mn = min(mn, k ? m[j][i] : m[i][j]);
            if (mn && mn != INF) {
                red += mn;
                for (int j = 0; j < n; j++)
                    if (k ? m[j][i] != INF : m[i][j] != INF)
                        k ? m[j][i] -= mn : m[i][j] -= mn;
            }
        }
    }
    return red;
}

int bound(int s, int d, int mat[20][20], int costSoFar) {
    int t[20][20]; memcpy(t, mat, sizeof(cost));
    for (int i = 0; i < n; i++) t[s][i] = t[i][d] = INF;
    t[d][0] = INF;
    return costSoFar + reduce(t) + mat[s][d];
}

void tsp(vector<int> &path, vector<bool> &vis, int costSoFar) {
    if (path.size() == n) {
        costSoFar += cost[path.back()][0];
        if (costSoFar < bestCost) {
            bestCost = costSoFar;
            bestPath = path; bestPath.push_back(0);
        }
        return;
    }
    int last = path.back();
    for (int i = 0; i < n; i++) if (!vis[i] && cost[last][i] != INF) {
        int t[20][20]; memcpy(t, cost, sizeof(cost));
        int b = bound(last, i, t, costSoFar);
        if (b < bestCost) {
            vis[i] = 1; path.push_back(i);
            tsp(path, vis, b);
            path.pop_back(); vis[i] = 0;
        }
    }
}

int main() {
    // Valid Input Example:
    // Enter number of cities: 4
    // Enter cost matrix (4x4):
    // 0 10 15 20
    // 10 0 35 25
    // 15 35 0 30
    // 20 25 30 0
    cout << "Enter number of cities: "; cin >> n;
    cout << "Enter cost matrix (" << n << "x" << n << "):\n";
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++) {
            cin >> cost[i][j];
            if (i != j && cost[i][j] == 0) cost[i][j] = INF;
        }

    int tmp[20][20]; memcpy(tmp, cost, sizeof(cost));
    vector<int> path = {0}; vector<bool> vis(n, 0); vis[0] = 1;
    tsp(path, vis, reduce(tmp));

    cout << "\nShortest Path: ";
    for (int c : bestPath) cout << c + 1 << " ";
    cout << "\nMinimum Cost: " << bestCost << endl;
}

// Time Complexity → O(n! × n²)
// Space Complexity O(n²)
//The matrix should be symmetric (cost[i][j] = cost[j][i]) if it’s an undirected path.

//0 on the diagonal (no self-travel).

//Use INF-like large numbers (e.g., 999 or 0 converted to INF) to represent no connection.

//Keep n small (3–8) — complexity grows fast
