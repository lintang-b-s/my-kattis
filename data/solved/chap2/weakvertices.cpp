#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == -1)
        {
            break;
        }
        // int adjM[n][n];
        vector<vector<int>> adjList(n, vector<int>(0));

        vector<unordered_set<int>> adjListSet(n);

        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                // cin >> adjM[i][j];
                int edge;
                cin >> edge;
                if (edge)
                {
                    adjList[i].push_back(j);
                    adjListSet[i].insert(j);
                }
            }
        }

        set<int> weakVertices;
        for (int u = 0; u < n; u++)
        {
            bool thisIsWeakVertex = true;
            for (auto v : adjList[u])
            {
                for (auto q : adjList[v])
                {
                    if (adjListSet[u].count(q))
                    {
                        thisIsWeakVertex = false;
                        break;
                    }
                }
            }
            if (thisIsWeakVertex)
            {
                weakVertices.insert(u);
            }
        }

        int i = 0;
        for (auto v : weakVertices)
        {
            cout << v;
            if (i < weakVertices.size() - 1)
            {
                cout << " ";
            }
            i++;
        }
        cout << endl;
    }
}