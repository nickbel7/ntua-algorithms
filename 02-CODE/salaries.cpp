#include <iostream>  
#include <stack>  
#include <vector>  
  
using namespace std;  
  
#define MAXN 200000+1  
int n,k,p[MAXN];    // For storing input data  
int maxLIS = 0, maxLDS = 0; // maximum LIS length  
int dpArray[MAXN], dpRevArray[MAXN]; // For LIS, LDS functions (O(nlogn))  
stack<int> stArray[MAXN];   // For LIS array of stacks  
stack<int> stArrRev[MAXN];  // For LDS array of stacks  
  
int binSearch(int number, int lower, int upper) {  
    if (lower > upper)  
        return lower;  
      
    else {  
        int middle = (lower + upper) / 2;  
  
        if (stArray[middle].empty())  
            return middle;  
        else if (stArray[middle].top() < number)  
            return binSearch(number, middle + 1, upper);  
        else if (stArray[middle].top() > number)  
            return binSearch(number, lower, middle - 1);  
        else   
            return middle;  
    }  
}  
  
int binSearchLDS(int number, int lower, int upper) {  
    if (lower > upper)  
        return lower;  
      
    else {  
        int middle = (lower + upper) / 2;  
  
        if (stArrRev[middle].empty())  
            return middle;  
        else if (stArrRev[middle].top() > number)  
            return binSearchLDS(number, middle + 1, upper);  
        else if (stArrRev[middle].top() < number)  
            return binSearchLDS(number, lower, middle - 1);  
        else   
            return middle;  
    }  
  
}  
  
void lis() {  
    int pSize = n;  
  
    for (int i=0; i<pSize; i++) {  
        int pos = binSearch(p[i], 0, maxLIS);   // find the appropriate stack for current element  
        stArray[pos].push(p[i]);    // place the element on the stack  
        dpArray[i] = pos + 1;   // for element p[i] set the LIS length including p[i]  
        maxLIS = (maxLIS == pos ? maxLIS+1 : maxLIS);   // check if bigger LIS length was found  
  
    }  
}  
  
void lds() {  
    int pSize = n;  
  
    for (int i=pSize-1; i>=0; i--) {  
        int pos = binSearchLDS(p[i], 0, maxLDS);    // find the appropriate stack for current element  
        stArrRev[pos].push(p[i]);   // place the element on the stack  
        dpRevArray[i] = pos + 1;    // for element p[i] set the LDS length including p[i]  
        maxLDS = (maxLDS == pos ? maxLDS+1 : maxLDS);   // check if bigger LDS length was found  
  
    }  
}  
  
int solve() {  
  
    int ans = 0;  
  
    for (int i=n-1; i>=0; i--) {  
        // Pop element p[i] from stack in position dpArray[i]  
        stArray[dpArray[i]-1].pop();  
        if (stArray[dpArray[i]-1].empty()) maxLIS-- ;  
  
        int curr = p[i] + k;    // increment p[i] by k  
        int lisLeft = binSearch(curr, 0, maxLIS);   // search where it fits in the stack array  
  
        ans = max(ans, lisLeft + dpRevArray[i]);    // update the global max  
    }  
  
    return ans;  
}  
  
int main() {  
  
    std::ios::sync_with_stdio(false);  
  
    // READ INPUT  
    cin >> n >> k;  
    for (int i=0; i<n; i++)  
        cin >> p[i];  
  
    lis();  
    lds();  
    cout << solve() << endl;  
      
}  