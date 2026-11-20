#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/railroad?tab=metadata

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        int n, m;
        cin >> n >> m;

        vector<vector<pair<int, int>>> adjList(n, vector<pair<int, int>>(0));

        for (int i = 0; i < m; i++)
        {
            int from, to, length;
            cin >> from >> to >> length;
            adjList[from - 1].push_back({to - 1, length});
            adjList[to - 1].push_back({from - 1, length});
        }

        // worst case: ketika graph adalah complete graph dengan jumlah edge setiap node= n-1
        for (int v = 0; v < n; v++)
        { // worst case: O(n^3)
            if (adjList[v].size() == 2)
            {
                auto vertexA = adjList[v][0];
                auto vertexB = adjList[v][1];

                for (auto it = adjList[vertexA.first].begin(); it != adjList[vertexA.first].end();)
                { // worst case ketika graph adalah complete graph, O(n^2), iterate semua edge & delete one edge dari node suatu complete graph
                    if (it->first == v)
                    {
                        adjList[vertexA.first].erase(it); // O(n)
                    }
                    else
                    {
                        ++it;
                    }
                }

                for (auto it = adjList[vertexB.first].begin(); it != adjList[vertexB.first].end();)
                {
                    if (it->first == v)
                    {
                        adjList[vertexB.first].erase(it);
                    }
                    else
                    {
                        ++it;
                    }
                }

                adjList[vertexA.first].push_back({vertexB.first, vertexB.second + vertexA.second});
                adjList[vertexB.first].push_back({vertexA.first, vertexA.second + vertexB.second});

                adjList[v].clear();
            }
        }

        int edgeCounts = 0;

        vector<vector<pair<int, int>>> results(n);

        for (int v = 0; v < n; v++)
        { // worst case: O(n^2), complete graph
            for (auto adjNode : adjList[v])
            {

                bool adaEdgeKebalik = false;
                for (auto to : results[adjNode.first])
                {
                    if (to.first == v)
                    {
                        adaEdgeKebalik = true;
                    }
                }
                if (!adaEdgeKebalik)
                {
                    edgeCounts += 1;

                    results[v].push_back({adjNode.first, adjNode.second});
                }
            }
        }

        cout << edgeCounts << endl;
        for (int v = 0; v < results.size(); v++)
        {
            auto edges = results[v];
            for (auto edge : edges)
            {
                cout << v + 1 << " " << edge.first + 1 << " " << edge.second << endl;
            }
        }
        cout << endl;
    }
    return 0;
}