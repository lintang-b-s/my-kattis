#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/financialplanning

typedef long long ll;

ll untung(ll profit, ll cost, ll d)
{
    return profit * d - cost;
}

bool investasi_menguntungkan(vector<ll> &profits, vector<ll> &costs, ll d, ll M)
{
    int n = profits.size();
    ll cuan_cuan = 0;
    for (int i = 0; i < n; i++)
    {
        ll cuan = untung(profits[i], costs[i], d);
        if (cuan > 0)
        {
            cuan_cuan += cuan;
            if (cuan_cuan >= M)
            {
                return true;
            }
        }
    }
    return cuan_cuan >= M;
}

ll bsta_hari_cuan(vector<ll> &profits, vector<ll> &costs, ll M)
{
    int n = profits.size();

    ll low = 0, high = (ll)3 * (ll) 1e9;
    ll hari_menguntungkan = 0;
    while (abs(high - low) > 1)
    { // O(log(high))
        ll mid = (low + high) / 2;
        if (investasi_menguntungkan(profits, costs, mid, M))
        {
            hari_menguntungkan = mid;
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    return hari_menguntungkan;
}

int main()
{
    ll n, M;
    cin >> n >> M;

    vector<ll> profits(n), costs(n);

    for (int i = 0; i < n; i++)
    {
        cin >> profits[i] >> costs[i];
    }

    cout << bsta_hari_cuan(profits, costs, M) << endl;
}

