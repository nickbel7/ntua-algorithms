#include <iostream>
#include <string.h>
#include <algorithm>
#include <time.h>

using namespace std;

#define MAXN 1000000+5

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

void reverse(portal arr[], int n)
{
    for (int low = 0, high = n - 1; low < high; low++, high--) {
        swap(arr[low], arr[high]);
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
    if (n<=100000 || m<=100000)
        sort(P, P+m, comparator);
    else
        reverse(P, m);

    memset(A, -1, sizeof(A)); //reset table A

    int i=1;
    int j=0;
    while (i<=n) {
        while (findRoot(c[i]) != findRoot(i)) {
            unionTree(P[j].x, P[j].y);
            j++;
        }

        i++;
    }

    cout << P[j-1].w << endl;

    // END TIMER
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    // printf("%.3f seconds.\n", elapsed);

    return 0;

}