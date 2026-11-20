#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/joinstrings?tab=metadata

int main()
{
    int n;
    cin >> n;

    vector<string> kataKata(n);
    for (int i = 0; i < n; i++)
    { // O(n)
        cin >> kataKata[i];
    }

    // pakai dfs buat concat biar gak MLE
    int concattedStringId = 0;
    vector<vector<int>> list(n);
    for (int i = 0; i < n - 1; i++)
    { // O(n)
        int a, b;
        cin >> a >> b;
        a -= 1, b -= 1;
        list[a].push_back(b);
        concattedStringId = a;
    }

    stack<int> dfsStack;
    dfsStack.push(concattedStringId);
    string stringGabungan = "";
    while (!dfsStack.empty())
    { // O(n)
        int nextStringId = dfsStack.top();
        dfsStack.pop();
        stringGabungan += kataKata[nextStringId];
        for (int i = list[nextStringId].size() - 1; i >= 0; i--)
        {
            dfsStack.push(list[nextStringId][i]);
        }
    }

    cout << stringGabungan;

    // Memory Limit Excedeed -> karena concatenated string nya gede
    // vector<string> kataKata(n);
    // for (int i = 0; i < n; i++)
    // { // O(n)
    //     cin >> kataKata[i];
    // }

    // for (int i = 0; i < n - 1; i++)
    // { // O(n)
    //     int a, b;
    //     cin >> a >> b;
    //     a -= 1, b -= 1;
    //     kataKata[a] = kataKata[a] + kataKata[b];
    //     kataKata[b] = "";
    // }
    // for (int i = 0; i < n; i++)
    // { // O(n)
    //     if (kataKata[i] != "")
    //     {
    //         cout << kataKata[i];
    //         break;
    //     }
    // }

    return 0;
}
