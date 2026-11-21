#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

const double a2_short_tape = 0.42044820762;
const double a2_long_tape = 0.5946035575;
const double sqrt2 = sqrt(2);

double find_tape_length(vector<ll> &sizes, int i, ll &sisa)
{
    if (i == sizes.size())
    {
        return 0;
    }

    double tape_length = 0;
    int count = sisa / 2;
    tape_length = count * (a2_long_tape / pow(sqrt2, i));
    sisa = sisa - min(sisa, sizes[i]);
    if (sisa > 0)
    {
        sisa *= 2;
        return tape_length + find_tape_length(sizes, i + 1, sisa);
    }
    return tape_length;
}

int main()
{
    cout.precision(12);
    int n;
    cin >> n;
    vector<ll> sizes(n - 1);

    for (int i = 0; i < n - 1; i++)
    {
        cin >> sizes[i];
    }
    ll sisa = 2;
    double tape_length = find_tape_length(sizes, 0, sisa); // O(n)
    if (sisa > 0)
    {
        cout << "impossible" << endl;
    }
    else
    {
        cout << tape_length << endl;
    }
}
