#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long ll;

int main()
{
    ll N;
    cin >> N;

    set<ll> numPpl;
    ll nSqrt = sqrt(N);
    for (int d = 1; d <= nSqrt; d++)
    { // O(sqrt(N))
        if ((N % d) == 0)
        {
            // N habis dibagi d
            numPpl.insert(d);
        }
        ll ndivD = (N / d);
        if (N % ndivD == 0)
        {
            numPpl.insert(N / d);
        }
    }

    int i = 0;
    for (auto d : numPpl)
    { // O(sqrt(N))

        cout << d - 1;

        if (i < numPpl.size() - 1)
        {
            cout << " ";
        }
        i++;
    }

    // // cek d|N, for each 1<=d<=N
    //  TLE
    // set<int> numPpl;
    // for (int d = 1; d <= N; d++)
    // { // O(N)
    //     if ((N % d) == 0)
    //     {
    //         // N habis dibagi d
    //         numPpl.insert(d);
    //     }
    // }

    // int i = 0;
    // for (auto d : numPpl)
    // { // O(N)

    //     cout << d - 1;

    //     if (i < numPpl.size() - 1)
    //     {
    //         cout << " ";
    //     }
    //     i++;
    // }
}