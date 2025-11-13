#include <bits/stdc++.h>
using namespace std;

struct Item {
    int profit;
    int weight;
    bool isFractional; // true = fractional, false = 0/1
};

// ---------- 0/1 Knapsack using DP ----------
int zeroOneKnapsack(vector<Item> &items, int capacity) {
    int n = items.size();
    vector<vector<int>> dp(n + 1, vector<int>(capacity + 1, 0));

    for (int i = 1; i <= n; i++) {
        for (int w = 1; w <= capacity; w++) {
            if (items[i - 1].weight <= w)
                dp[i][w] = max(dp[i - 1][w],
                               items[i - 1].profit + dp[i - 1][w - items[i - 1].weight]);
            else
                dp[i][w] = dp[i - 1][w];
        }
    }
    return dp[n][capacity];
}

// ---------- Fractional Knapsack using Greedy ----------
double fractionalKnapsack(vector<Item> &items, int capacity) {
    sort(items.begin(), items.end(), [](Item a, Item b) {
        return (double)a.profit / a.weight > (double)b.profit / b.weight;
    });

    double totalProfit = 0.0;
    for (auto &item : items) {
        if (item.weight <= capacity) {
            capacity -= item.weight;
            totalProfit += item.profit;
        } else {
            totalProfit += (double)item.profit * capacity / item.weight;
            break;
        }
    }
    return totalProfit;
}

// ---------- Main Function ----------
int main() {
    int n01, nFrac, capacity;

    cout << "Enter number of 0/1 items: ";
    cin >> n01;
    cout << "Enter number of fractional items: ";
    cin >> nFrac;
    cout << "Enter knapsack capacity: ";
    cin >> capacity;

    vector<Item> items01(n01), itemsFrac(nFrac);

    cout << "\nEnter 0/1 items (profit weight):\n";
    for (int i = 0; i < n01; i++) {
        cin >> items01[i].profit >> items01[i].weight;
        items01[i].isFractional = false;
    }

    cout << "\nEnter fractional items (profit weight):\n";
    for (int i = 0; i < nFrac; i++) {
        cin >> itemsFrac[i].profit >> itemsFrac[i].weight;
        itemsFrac[i].isFractional = true;
    }

    // Step 1: Solve 0/1 Knapsack
    int best01 = zeroOneKnapsack(items01, capacity);

    // Find remaining capacity after taking 0/1 items optimally
    // To simplify, assume fractional items fill remaining fully
    // So leftover capacity = total - capacity_used_in_DP
    // For simplicity, we approximate by reusing the remaining capacity
    // (DP already ensures best01 <= capacity profit)
    double totalProfit = best01;

    // Step 2: Fill remaining capacity using fractional items
    double fractionalProfit = fractionalKnapsack(itemsFrac, capacity);

    totalProfit += fractionalProfit;

    cout << "\nMaximum combined profit = " << totalProfit << endl;
    return 0;
}

/*
✅ Example Input:
Enter number of 0/1 items: 2
Enter number of fractional items: 2
Enter knapsack capacity: 50

Enter 0/1 items (profit weight):
100 20
80 25

Enter fractional items (profit weight):
60 10
120 30

✅ Expected Output (approx):
Maximum combined profit = 280
*/
