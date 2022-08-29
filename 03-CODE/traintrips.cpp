#include <iostream>
#include <queue>

using namespace std;

/*
**Γενική ιδέα**

Θα εφαρμόσουμε Dijkstra όπου κάθε κόμβος θα αναπαριστά το modulo του 
αθροίσματος κάποιων στάσεων με το μήκος της μικρότερης απόστασης στάσης ($d_k$)
. Θεωρούμε ότι για να πάμε από το σημείο 0 μέχρι κάποιο $d_j$ θα κάνουμε συνέχεια
 τις μικρότερες δυνατές στάσεις επί όσες φορές μπορούμε (δηλαδή $n*d_k$) και μετά 
 θα κάνουμε κάποια μεγαλύτερη διαδρομή $d_i$ οπου $d_i \% d_k \geq 0$.
 Άμα καταφέρουμε να βρούμε από την αφαιτηριά τη μικρότερη απόσταση για κάθε 
 τέτοιο modulo τότε για κάθε δοσμένο $d_j$ θα κάνουμε modulo με το $d_k $ και 
 θα αναζητήσουμε την απόσταση αυτή. Αν είναι μικρότερη από $d_j$ τότε μπορούμε να 
 βρεθούμε σε αυτό το σταθμό με κάποιο πολλαπλάσιο του $d_k$ + κάποια άλλη απόσταση. 
 Διαφορετικά δεν μπορούμε να φτάσουμε σε αυτό το σταθμό.
*/

#define INF 10e8+1

int n, q, // inputs N, Q
*d, // di..dN discrete distances 
*dist, // distance for di mod min_d (dk is min(di))
min_d = 10000+1;    // min_d is min(di)

class myComparator
{
public:
    int operator() (const pair<int,int>& p1, const pair<int,int>& p2)
    {
        return p1.first > p2.first;
    }
};

// Dijkstra implementation with priority queue
void dijkstra () {

    priority_queue<pair<int,int>, vector<pair<int,int>>, myComparator> pq;

    pair<int,int> u = make_pair(0, 0);    // start node (dist, node_num)
    pq.push(u);

    while (!pq.empty())
    {
        pair<int,int> top = pq.top();   // take top node
        // cout << top.first << " " << top.second << endl;
        
        for (int i=0; i<n; i++) {
            int v = (top.second + d[i]) % min_d;  //node_num for v
            int dist_v = top.first + d[i];  // dist for v

            if (dist_v < dist[v]) {
                pq.push(make_pair(dist_v, v)); 
                dist[v] = dist_v;
                // cout << "New dist for : " << v << " " << dist[v] << endl;
            }
        }

        pq.pop();   // delete top node from stack
    }
    
}

int main() {

    // INPUT
    cin >> n >> q;
    d = new int[n+1];
    for (int i=0; i<n; i++) {
        cin >> d[i];
        min_d = min(min_d, d[i]);
    }    
    dist = new int[min_d+1];
    dist[0] = 0;    // start node
    for (int i=1; i<min_d; i++)
        dist[i] = INF;   // set all distances equal to INF
    
    // Calculate min distances
    dijkstra();

    // Print outputs
    int query;
    for (int i=0; i<q; i++) {
        cin >> query;
        cout << (dist[query % min_d] <= query ? "YES" : "NO") << endl;
    }

    return 0;
}