#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/chopwood?tab=metadata

struct node
{
    int degree;
    int id;
};

class CompareMin
{
public:
    bool operator()(node *a, node *b)
    {
        if (b->degree != a->degree)
        {
            return a->degree > b->degree;
        }
        return a->id > b->id;
    }
};

int main()
{
    int n;
    cin >> n;
    unordered_map<int, int> nodeDegree;
    unordered_map<int, node *> nodeMap;

    vector<int> vs;
    bool inconsistent = false;
    for (int i = 0; i < n; i++)
    {
        int v;
        cin >> v;

        nodeDegree[v]++;

        if (i == n - 1 && v != n + 1)
        {
            inconsistent = true;
            break;
        }
        vs.push_back(v);
    }

    priority_queue<node *, vector<node *>, CompareMin> pq;

    for (int i = 1; i <= n + 1; i++)
    {
        nodeDegree[i]++;
        node *n = new node{};
        n->id = i;
        n->degree = nodeDegree[i];

        if (n->degree == 1)
        {
            pq.push(n); // O(logN)
        }
        nodeMap[i] = n;
    }

    if (inconsistent)
    {
        cout << "Error" << endl;
        return 0;
    }

    for (int i = 1; i <= n; i++)
    {
        auto smallestLeaf = pq.top();
        cout << smallestLeaf->id << endl;
        pq.pop(); // O(logN)

        int v = vs[i - 1];

        node *updatedN = nodeMap[v];
        nodeDegree[v]--;
        updatedN->degree = nodeDegree[v];
        if (nodeDegree[v] == 1)
        {
            pq.push(updatedN); // O(logN)
        }
    }

    return 0;
}