#include <iostream>
#include <time.h>

using namespace std;

int n, k;
int h[20000+1]; //habitants
pair<int, int> k1[1000000+1], k2[1000000+1];

bool checkOverlap(pair<int,int> p1, pair<int,int> p2) {
    
    if ((p1.first >= p2.first && p1.first <= p2.second) || (p1.second >= p2.first && p1.second <= p2.second))
        return true;
    
    else return false;
}

int sum(pair<int,int> p) {
    return (p.second - p.first + 1);
}

bool valid(pair<int,int> p) {
    if (p == make_pair(-1,-1))
        return false;

    else return true;
}

int main() {

    // std::ios::sync_with_stdio(false);
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    // BEGIN TIMER
    clock_t start = clock();

    // READ INPUT
    cin >> n >> k;
    for (int i=0; i<n; i++) {
        cin >> h[i];
    }

    //intitialize k1, k2 arrays
    for (int i=0; i<=k; i++) {
        k1[i] = make_pair(-1,-1);
        k2[i] = make_pair(-1,-1);
    }

    //check if k is even (special case for k/2)
    bool flag = false;
    if (k%2 == 0) flag = true;

    // 1st iteration of h
    for (int i=0; i<n; i++) {
        int count = 0;
        for (int j=i; j<n; j++) {
            count += h[j];
            if (count <= k) {   //check if count is valid
                if ((k1[count] == make_pair(-1,-1) || k1[count].second-k1[count].first > j-i)
                    && !checkOverlap(make_pair(i,j), k1[k-count])) {
                    k1[count].first = i;
                    k1[count].second = j;
                }
            }
            else break; //continue if count > k (no valid sums)
        }
    }

    // 2nd iteration of h
    for (int i=n-1; i>=0; i--) {
        int count = 0;
        for (int j=i; j<n; j++) {
            count += h[j];
            if (count <= k) {   //check if count is valid
                if (flag && count == k/2) {     //special case for k/2, k is even
                    if (make_pair(i,j) != k1[count] 
                    && (k2[count] == make_pair(-1,-1) || k2[count].second-k2[count].first > j-i)
                    && !checkOverlap(make_pair(i,j), k1[count])) {
                        k2[count].first = i;
                        k2[count].second = j;
                    }
                }
                else if ((k2[count] == make_pair(-1,-1) || k2[count].second-k2[count].first > j-i)
                    && !checkOverlap(make_pair(i,j), k2[k-count])) {
                    k2[count].first = i;
                    k2[count].second = j;
                }
            }
            else break; //continue if count > k (no valid sums)
        }
    }

    int minLength = n+5;
    int pairLength1, pairLength2;
    for (int i=1; i<=(k-1)/2; i++) {    // iteration from 1 to k/2 (all except k/2)

        if (valid(k1[i]) && valid(k1[k-i])) {
            pairLength1 = sum(k1[i]) + sum(k1[k-i]);
            minLength = min(minLength, pairLength1);
        }
            
        if (valid(k2[i]) && valid(k2[k-i])) {
            pairLength2 = sum(k2[i]) + sum(k2[k-i]);
            minLength = min(minLength, pairLength2);
        }
    }
    
    if (valid(k1[k]))   //check for unique subbarray (because k1[0] is always <-1,-1>)
        minLength = min(minLength, sum(k1[k]));

    if (flag && valid(k1[k/2]) && valid(k2[k/2]))   // check for two subbarrays with equal sums (k/2)
        minLength = min(minLength, sum(k1[k/2])+sum((k2[k/2])));

    cout << (minLength == n+5 ? -1 : minLength) << endl;


    // END TIMER
    clock_t end = clock();
    double elapsed = double(end - start)/CLOCKS_PER_SEC;
    // printf("%.3f seconds.\n", elapsed);

    return 0;
}