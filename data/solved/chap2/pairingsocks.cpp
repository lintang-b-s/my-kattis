#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/pairingsocks?tab=metadata

int main()
{
    int n;
    cin >> n;

    stack<int> tumpukanOri, tumpukanAux;
    for (int i = 0; i < 2 * n; i++)
    { // O(2n)
        int a;
        cin >> a;
        tumpukanOri.push(a);
    }

    int jumlahMoves = 0;

    while (!tumpukanOri.empty())
    { // O(2n)
        if (tumpukanAux.empty())
        {
            int lastItemOri = tumpukanOri.top();
            tumpukanOri.pop();
            tumpukanAux.push(lastItemOri);
            jumlahMoves++;
            continue;
        }

        if (tumpukanOri.top() == tumpukanAux.top())
        {
            tumpukanOri.pop();
            tumpukanAux.pop();
            jumlahMoves++;
        }
        else
        {
            int lastItemOri = tumpukanOri.top();
            tumpukanOri.pop();
            tumpukanAux.push(lastItemOri);
            jumlahMoves++;
        }
    }

    if (tumpukanOri.empty() && tumpukanAux.empty())
    {
        cout << jumlahMoves;
    }
    else
    {
        cout << "impossible";
    }
}