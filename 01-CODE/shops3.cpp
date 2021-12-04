#include <iostream>

using namespace std;

#define MAXN 100000

int n, k, answer=MAXN;
int h[20000+1]; //habitants
pair<int,int> sums[1000000+1];
bool sumsSeen[1000000+1] = {0};
// pair<int, int> k1[1000000+1], k2[1000000+1];
// bool k1Seen[1000000+1] = {0}, k2Seen[1000000+1] = {0};

int len(pair<int,int> p) {
    return (p.second - p.first + 1);
}

int main() {

    std::ios::sync_with_stdio(false);

    //READ INPUT
    cin >> n >> k;
    for (int i=0; i<n; i++) {
        cin >> h[i];
    }

    //iterate the array h and store only the sums that appear on the left
    for (int i=0; i<n; i++) {
        int count = 0;
        for (int j=i; j>=0; j--) {
            count += h[j];
            if (count > k) break;
            pair<int, int> new_pair = make_pair(j, i);
            if (sumsSeen[count] == false) {
                sums[count] = new_pair;
                sumsSeen[count] = true;
            }
            else {
                if (len(sums[count]) > len(new_pair)) {
                    sums[count] = new_pair;
                }
            }
        }
        count = 0;
        for (int j=i+1; j<n; j++) {
            count += h[j];
            if (count > k) break; 
            if (sumsSeen[k-count]) {
                int current_length = len(sums[k-count]) + len(make_pair(i+1, j));
                answer = min(answer, current_length);
            }
        }
    }

    //final check for length = k
    if (sumsSeen[k])
        answer = min(answer, len(sums[k]));

    if (answer == MAXN)
        cout << -1 << endl;
    else
        cout << answer << endl;
    
    return 0;
}
