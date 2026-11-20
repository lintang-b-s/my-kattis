#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/freefood?tab=metadata

int main()
{
    bool hariFreeFood[366];
    memset(hariFreeFood, false, sizeof(hariFreeFood));

    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    { // O(N)
        int f, t;
        cin >> f >> t;
        for (int day = f; day <= t; day++)
        {
            hariFreeFood[day] = true;
        }
    }

    int jumlahHariMadangGratis = 0;
    for (int i = 0; i <= 365; i++)
    { // 365 ops
        if (hariFreeFood[i])
        {
            jumlahHariMadangGratis++;
        }
    }
    cout << jumlahHariMadangGratis << endl;
}