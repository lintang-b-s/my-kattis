#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/bits?tab=metadata
int main()
{
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        long long a;
        cin >> a;
        int maxbits = 0;

        // O(d * ceil(log2(a))), d=number of digits dari a
        while (a > 0)
        {
            maxbits = max(maxbits, __builtin_popcount(a));  // builtin_popcount = O(ceil(log2(a)))
            a /= 10;
        }
        cout << maxbits<<endl;
    }
}