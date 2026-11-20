#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/flyingsafely?tab=metadata

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<int>> adjList(n);
        for (int i = 0; i < m; i++)
        {
            int from, to;
            cin >> from >> to;
            adjList[from - 1].push_back(to - 1);
            adjList[to - 1].push_back(from - 1);
        }

        unordered_set<int> visited;

        int nodeId = 0;
        int minimumNumberOfPilots = 0;

        stack<int> tumpukan;

        tumpukan.push(nodeId);

        cout << n - 1 << endl;

        // TLE
        // while (!tumpukan.empty())
        // {
        //     int curNodeId = tumpukan.top();
        //     tumpukan.pop();
        //     visited.insert(curNodeId);
        //     bool useAnyEdge = false;
        //     for (auto adjNodeId : adjList[curNodeId])
        //     {
        //         if (!visited.count(adjNodeId))
        //         {
        //             useAnyEdge = true;
        //             tumpukan.push(adjNodeId);
        //         }
        //     }

        //     if (useAnyEdge)
        //     {
        //         minimumNumberOfPilots++;
        //     }
        // }

        // cout << minimumNumberOfPilots << endl;
    }
}