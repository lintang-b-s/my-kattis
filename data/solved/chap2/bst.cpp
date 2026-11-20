#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
int main()
{
    int N;
    cin >> N;

    set<int> bbst;
    unordered_map<int, int> depth;

    ll C = 0;

    for (int i = 0; i < N; i++)
    { // O(NlogN)
        int node;
        cin >> node;

        int cur_depth = 0;
        set<int>::iterator successorIt = bbst.lower_bound(node); // O(logN)
        if (successorIt != bbst.end())
        {
            // successor depth
            int successor = *successorIt;
            cur_depth = max(cur_depth, depth[successor] + 1);
        }
        if (successorIt != bbst.begin())
        {
            // predecessor depth
            cur_depth = max(cur_depth, depth[*(--successorIt)] + 1);
        }
        depth[node] = cur_depth;
        C += cur_depth;
        cout << C << endl;

        bbst.insert(node); // O(logN)
    }
}