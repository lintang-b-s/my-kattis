#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ull;

// https://open.kattis.com/problems/abinitio?tab=metadata
int main()
{
    int v, e, q;
    cin >> v >> e >> q;

    vector<vector<int>> adjM(v, vector<int>(v, 0));
    vector<vector<int>> adjMTransposed(v, vector<int>(v, 0));
    vector<vector<int>> adjMComplement(v, vector<int>(v, 1));
    vector<vector<int>> adjMComplementTransposed(v, vector<int>(v, 1));

    for (int i = 0; i < e; i++)
    {
        int from, to;
        cin >> from >> to;
        adjM[from][to] = 1;
        adjMTransposed[to][from] = 1;
        adjMComplement[from][to] = 0;
        adjMComplementTransposed[to][from] = 0;
    }

    for (int i = 0; i < q; i++)
    {
        int queryType;
        cin >> queryType;
        if (queryType == 1)
        {
            for (int j = 0; j < v; j++)
            { // O(v)
                adjM[j].push_back(0);
                adjMTransposed[j].push_back(0);
                adjMComplement[j].push_back(1);
                adjMComplementTransposed[j].push_back(1);
            }
            vector<int> tempAdjV(v + 1, 0);
            adjM.push_back(tempAdjV);
            adjMTransposed.push_back(tempAdjV);

            vector<int> tempAdjvCompl(v + 1, 1);
            adjMComplement.push_back(tempAdjvCompl);
            adjMComplementTransposed.push_back(tempAdjvCompl);
            v++;
        }
        else if (queryType == 2)
        {
            int from, to;
            cin >> from >> to;

            adjM[from][to] = 1;
            adjMTransposed[to][from] = 1;
            adjMComplement[from][to] = 0;
            adjMComplementTransposed[to][from] = 0;
        }
        else if (queryType == 3)
        {
            int vertex;
            cin >> vertex;
            // O(v)
            for (int j = 0; j < v; j++)
            {
                adjM[vertex][j] = 0;
                adjMTransposed[j][vertex] = 0;
                adjMComplement[vertex][j] = 1;
                adjMComplementTransposed[j][vertex] = 1;
            }

            for (int j = 0; j < v; j++)
            {
                adjM[j][vertex] = 0;
                adjMTransposed[vertex][j] = 0;
                adjMComplement[j][vertex] = 1;
                adjMComplementTransposed[vertex][j] = 1;
            }
        }
        else if (queryType == 4)
        {
            // O(1)
            int from, to;
            cin >> from >> to;
            adjM[from][to] = 0;
            adjMTransposed[to][from] = 0;
            adjMComplement[from][to] = 1;
            adjMComplementTransposed[to][from] = 1;
        }
        else if (queryType == 5)
        {

            swap(adjM, adjMTransposed);                     // O(1)
            swap(adjMComplement, adjMComplementTransposed); // O(1)
        }
        else
        {

            swap(adjM, adjMComplement);                     // O(1)
            swap(adjMTransposed, adjMComplementTransposed); // O(1)
        }
    }

    v = adjM.size();
    cout << v << endl;

    vector<vector<int>> adjL(v, vector<int>(0));
    for (int i = 0; i < v; i++)
    {
        for (int j = 0; j < v; j++)
        {
            if (i == j)
            {
                continue;
            }
            if (adjM[i][j])
            {
                adjL[i].push_back(j);
            }
        }
    }
    ull moddd = 1e9 + 7;

    for (int i = 0; i < v; i++)
    {
        int m = adjL[i].size();
        cout << m << " ";

        ull hash = 0;
        int power = 0;
        ull sevenPow = 1;
        for (int j = 0; j < m; j++)
        {
            hash += sevenPow * adjL[i][j];
            sevenPow *= 7;
            hash = hash % moddd;
            sevenPow = sevenPow % moddd;
        }
        cout << hash << endl;
    }

    // TLE (sebelum tambahin adjMTransposed & adjMComplement)
    // vector<vector<int>> adjM(v, vector<int>(v, 0));
    // vector<vector<int>> adjMTransposed(v, vector<int>(v, 0));
    // vector<vector<int>> adjMComplement(v, vector<int>(v, 0));

    // for (int i = 0; i < e; i++)
    // {
    //     int from, to;
    //     cin >> from >> to;
    //     adjM[from][to] = 1;
    // }

    // for (int i = 0; i < q; i++)
    // {
    //     int queryType;
    //     cin >> queryType;
    //     if (queryType == 1)
    //     {
    //         for (int j = 0; j < v; j++)
    //         { // O(v)
    //             adjM[j].push_back(0);
    //             adjMTransposed[j].push_back(0);
    //             adjMComplement[j].push_back(1);
    //         }
    //         vector<int> tempAdjV(v + 1, 0);
    //         adjM.push_back(tempAdjV);
    //         adjMTransposed.push_back(tempAdjV);

    //         vector<int> tempAdjvCompl(v + 1, 1);
    //         adjMComplement.push_back(tempAdjvCompl);

    //         v++;
    //     }
    //     else if (queryType == 2)
    //     {
    //         int from, to;
    //         cin >> from >> to;

    //         adjM[from][to] = 1;
    //         adjMTransposed[to][from] = 1;
    //         adjMComplement[from][to] = 0;
    //     }
    //     else if (queryType == 3)
    //     {
    //         int vertex;
    //         cin >> vertex;
    //         for (int j = 0; j < v; j++)
    //         {
    //             adjM[vertex][j] = 0;
    //             adjMTransposed[j][vertex] = 0;
    //             adjMComplement[vertex][j] = 1;
    //         }

    //         for (int j = 0; j < v; j++)
    //         {
    //             adjM[j][vertex] = 0;
    //             adjMTransposed[vertex][j] = 0;
    //             adjMComplement[vertex][j] = 1;
    //         }
    //     }
    //     else if (queryType == 4)
    //     {
    //         int from, to;
    //         cin >> from >> to;
    //         adjM[from][to] = 0;
    //     }
    //     else if (queryType == 5)
    //     {

    //         for (int j = 0; j < v; j++)
    //         { // O(v^2)
    //             for (int k = j + 1; k < v; k++)
    //             {
    //                 if (j == k)
    //                 {
    //                     continue;
    //                 }
    //                 swap(adjM[j][k], adjM[k][j]);
    //             }
    //         }
    //     }
    //     else
    //     {
    //         vector<vector<int>> adjMTemp(v, vector<int>(v, 0));
    //         for (int j = 0; j < v; j++)
    //         { // O(v^2)
    //             for (int k = 0; k < v; k++)
    //             {
    //                 if (j == k)
    //                 {
    //                     continue;
    //                 }
    //                 if (adjM[j][k])
    //                 {
    //                     adjMTemp[j][k] = 0;
    //                 }
    //                 else
    //                 {
    //                     adjMTemp[j][k] = 1;
    //                 }
    //             }
    //         }

    //         adjM = adjMTemp;
    //     }
    // }

    // v = adjM.size();
    // cout << v << endl;

    // vector<vector<int>> adjL(v, vector<int>(0));
    // for (int i = 0; i < v; i++)
    // {
    //     for (int j = 0; j < v; j++)
    //     { // O(v^2)
    //         if (adjM[i][j])
    //         {
    //             adjL[i].push_back(j);
    //         }
    //     }
    // }
    // ull moddd = 1e9 + 7;

    // for (int i = 0; i < v; i++)
    // {
    //     int m = adjL[i].size();
    //     cout << m << " ";

    //     ull hash = 0;
    //     int power = 0;
    //     ull sevenPow = 1;
    //     for (int j = 0; j < m; j++)
    //     {
    //         hash += sevenPow * adjL[i][j];
    //         sevenPow *= 7;
    //         hash = hash % moddd;
    //         sevenPow = sevenPow % moddd;
    //     }
    //     cout << hash << endl;
    // }
}