#include <iostream>
#include <algorithm>
#include <string.h>
#include <vector>
#include <stack>

using namespace std;

#define MAXN 3000+1
#define MAXM 100000+1

struct road {
    int x;  // vertex x
    int y;  // vertex y
    int d;  // edge weight
};

int n,m,q; // n : towns, m : roads
int UF[MAXN]; // table for union find (1..N)
road *R; // table for roads 
vector<pair<int,int>> msTree[MAXN]; // MST tree of graph : each pair (child, weight)

// UNION FIND IMPLEMENTATION
int findRoot(int x) {
    if (UF[x] != -1)
        return UF[x] = findRoot(UF[x]); //path compression
    else
        return x;
}

void unionTree(int x, int y) {

    int xroot = findRoot(x);
    int yroot = findRoot(y);

    if (xroot != yroot) 
        UF[yroot] = xroot;
    
    return;
}

bool comparator(road a, road b) {
    return (a.d < b.d);
}

void mst() {

    int edge_count = 0;  // counter for edges in mst
    int edge_i = 0; // counter for edges in sorted array

    while (edge_count < n-1) {
        int node_x = R[edge_i].x;
        int node_y = R[edge_i].y;
        int edge_w = R[edge_i].d;

        if (findRoot(node_x) != findRoot(node_y)) {
            unionTree(node_x, node_y);
            msTree[node_x].push_back(make_pair(node_y, edge_w));
            msTree[node_y].push_back(make_pair(node_x, edge_w));
            edge_count ++;
        }

        edge_i ++;
    }
}

int dfs(int x, int y) {
    int maxD = 0; // maximum edge (u,v) weight in x -> path
    int visited[MAXN] = {0};

    stack<pair<int, pair<int,int>>> lifoStack;  // (parent, (node, weight))
    lifoStack.push(make_pair(-1, make_pair(x, 0)));
    stack<pair<int,int>> path;  // (node, weight)
    // path.push(make_pair(x, 0));

    while (!lifoStack.empty()) {
        pair<int, pair<int,int>> curr_node = lifoStack.top();   // takes top element in stack
        while (!path.empty() && curr_node.first != path.top().first)
            path.pop();
        path.push(curr_node.second);
        lifoStack.pop();
        visited[curr_node.second.first] = 1;    // mark current node as visited

        if (curr_node.second.first == y) break;     // if it is the goal node then stop
        for (auto i : msTree[curr_node.second.first]) {
            if (!visited[i.first])
                lifoStack.push(make_pair(curr_node.second.first, i));    // push (parent, (child, weight togoto child))
        }
    }

    while (!path.empty()) {
        maxD = max(maxD, path.top().second);
        path.pop();
    }

    return maxD;
}

int main() {

    std::ios::sync_with_stdio(false);

    // INPUT
    cin >> n >> m;
    R = new road[m];

    for (int i=0; i<m; i++) {
        road new_road;
        cin >> new_road.x >> new_road.y >> new_road.d;
        R[i] = new_road;
    }

    // Sort the edges (for the MST algorithm - Kruzkal)
    sort(R, R+m, comparator);

    // Initialize the union find array (Kruzkal)
    memset(UF, -1, sizeof(UF)); //reset table A

    // Create MST tree
    mst();

    pair<int,int> query;
    cin >> q;
    for (int i=0; i<q; i++) {
        cin >> query.first >> query.second;
        cout << dfs(query.first, query.second) << endl;
    }

    return 0;
}