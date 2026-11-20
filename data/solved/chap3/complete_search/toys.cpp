#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll josephus(ll n, ll k)
{ // O(n)
    return n > 1 ? (josephus(n - 1, k) + k - 1) % n + 1 : 1;
}

int main()
{
    int t, k;
    cin >> t >> k;
    cout << josephus(t, k) - 1 << endl;
}


