#include <iostream>
#include <string.h>
#include <algorithm>
#include <time.h>

using namespace std;

#define MAXN 100000+5

struct portal {
    int x; //universe 1
    int y; //universe 2
    int w; //weight
};

int n, m;
int c[MAXN]; //table for storing input (1..N)
int A[MAXN]; //table for union find (1..N)
portal P[MAXN]; //portals (1..M)

//UNION FIND IMPLEMENTATION
int findRoot(int x) {
    if (A[x] != -1)
        return A[x] = findRoot(A[x]); //path compression
    else
        return x;
}

void unionTree(int x, int y) {

    int xroot = findRoot(x);
    int yroot = findRoot(y);

    if (xroot != yroot) 
        A[yroot] = xroot;
    
    return;
}

bool comparator(portal a, portal b) {
    return (a.w > b.w);
}

bool checkMultiverse() {
    for (int i=1; i<=n; i++)
        if (findRoot(c[i]) != findRoot(i)) 
            return false;
        
    return true;
}

int binSearch(int lower, int upper) {
    if (lower > upper)
        return lower;

    else {
        int middle = (lower + upper) / 2;
        memset(A, -1, sizeof(A)); //reset table A

        for (int i=0; i<=middle; i++) { //rebuild the portals
            unionTree(P[i].x, P[i].y);
        }

        if (checkMultiverse()) 
            return (binSearch(lower, middle-1));
            
        else 
            return (binSearch(middle+1, upper));
            
    }
}

int main() {

    std::ios::sync_with_stdio(false);

    // BEGIN TIMER
    clock_t start = clock();

    cin >> n >> m;
    for (int i=1; i<=n; i++)
        cin >> c[i];

    int a,b,w;

    for (int i=0; i<m; i++) {
        cin >> a >> b >> w;
        portal p; //store info for each portal
        p.x = a;
        p.y = b;
        p.w = w;
        P[i] = p;
    }

    //reverse sort table P with weights as key
    sort(P, P+m, comparator);

    //run binary search on table P (1..M)
    int low = 0; 
    int up = m-1;
    int answer = binSearch(low, up);
    
    cout << P[answer].w << endl;

    // END TIMER
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    // printf("%.3f seconds.\n", elapsed);

    return 0;

}