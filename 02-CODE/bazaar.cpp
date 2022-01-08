#include <iostream>
#include <vector>
#include <map>

using namespace std;

#define MAXN 5000+1
#define INF INT32_MAX
int n,m;
// 1. We need a 3x3 grid of vectors to store all the offers for each item of each vendor
vector<pair<int,int>> offers[4][4]; // 1st dimension : Vendors, 2nd dimenstion : Items
// 2. We need 3 temporary arrays (1 dimensio) to calculate the DP for each item {A,B,C} -> DP_A[i] : min cost for qnty i of item A
int DP_A[MAXN], DP_B[MAXN], DP_C[MAXN];
// 3. We need 3 permanent arrays (1 dimension) to store the cost for each amount of sets of each vendor -> cost1[i] : min cost for i sets from vendor 1
int cost_1[MAXN], cost_2[MAXN], cost_3[MAXN];

map<char, int> item = {
    {'A', 1},
    {'B', 2},
    {'C', 3}
};

map<int, int*> itemDP = {
    {1, DP_A},
    {2, DP_B},
    {3, DP_C}
};

map<int, int*> costArr = {
    {1, cost_1},
    {2, cost_2},
    {3, cost_3}
};

// THE 'knapsack()' FUNCTION FILLS A 1D TABLE FOR ITEM 'item' OF VENDOR 'vendor' WITH THE MIN COST FOR EACH AMOUNT OF IT
void knapsack(int *dpArray, int vendor, int item) {
    vector<pair<int,int>> offersList = offers[vendor][item];

    dpArray[0] = 0; // 0 amount of that item costs 0
    for (int i=1; i<=n; i++)
        dpArray[i] = INF;  // any other amount initially costs infinity

    // cout << "Test : " << dpArray[0] << " " << dpArray[1] << endl;

    int itemsAmount = 0;

    for (int i=0; i<offersList.size(); i++) {    // for each offer on each item
        int itemQty = offersList[i].first;
        int itemPrice = offersList[i].second;
        itemsAmount += itemQty;
        for (int j=min(n, itemsAmount); j>=1; j--) {
            // Apply recursive function to 1D array
            dpArray[j] = min(dpArray[j], dpArray[max(j-itemQty, 0)] + itemPrice);
        }
    }
}

// THE 'fillCost()' FUNCTION FILLS THE 'cost_x' TABLES WHICH STORE THE COST FOR EACH AMOUNT OF SETS FOR EACH VENDOR
void fillCost(int *costArray) {
    for (int i=0; i<=n; i++) {
        if (DP_A[i] == INF || DP_B[i] == INF || DP_C[i] == INF)
            costArray[i] = INF;
        else    
            costArray[i] = DP_A[i] + DP_B[i] + DP_C[i];
    }
}

int main() {

    char y;
    int x, A, P;

    // INPUT
    cin >> n >> m;
    for (int i=0; i<m; i++) {
        scanf("%d %c %d %d", &x, &y, &A, &P);
        offers[x][item[y]].push_back(make_pair(A,P));
    }

    // We want to fill 1 knapsack table for each item of each vendor (9 in total)
    for (int vendorN=1; vendorN<4; vendorN++) {
        for(int itemN=1; itemN<4; itemN++)
            knapsack(itemDP[itemN], vendorN, itemN);
        fillCost(costArr[vendorN]);
    }
        
    // We check all possible combinations of a and b (0<a,b<=N)
    int minCost = INF;
    for (int i=0; i<=n; i++) {
        if (cost_1[i] == INF) continue;
        for (int j=n-i; j>=0; j--) {
            if (cost_2[j] == INF || cost_3[n-i-j] == INF) continue;
            minCost = min(cost_1[i] + cost_2[j] + cost_3[n-i-j], minCost);
            // if (minCost > cost_1[i] + cost_2[j] + cost_3[n- j - i]) minCost = cost_1[i] + cost_2[j] + cost_3[n - j - i];
        }
    }
        
    cout << (minCost == INF ? -1 : minCost) << endl;

    return 0;
}