#include <bits/stdc++.h>
using namespace std;

int LSONE(int s)
{
    return s & -(s);
}
typedef long long ll;

int main()
{
    string input;
    cin >> input;

    ll n = 0;

    vector<ll> numbers;
    for (int i = 0; i < input.size(); i++)
    {
        if (input[i] == '+')
        {
            n++;
        }
        else
        {
            string aa = "";

            for (int j = i; j < input.size(); j++)
            {
                if (input[j] == '+')
                {
                    i = j - 1;
                    break;
                }
                aa += input[j];
                if (j == input.size() - 1)
                {
                    i = j + 1;
                }
            }

            ll a = stoll(aa);

            numbers.push_back(a);
        }
    }

    vector<vector<ll>> subsets;
    for (ll mask = 0; mask < (1ll << n); mask++)
    { // O(2^n)
        vector<ll> subset;
        ll m = mask;
        while (m)
        {
            ll two_pow_j = LSONE(m);
            ll j = __builtin_ctz(two_pow_j);
            subset.push_back(j);
            m -= two_pow_j;
        }
        subsets.push_back(subset);
    }

    set<ll> angkas;
    for (int i = 0; i < subsets.size(); i++)
    { // O(2^n * n)
        auto subset = subsets[i];
        bool adds[n];
        memset(adds, false, sizeof adds);
        for (int j = 0; j < subset.size(); j++)
        {
            adds[subset[j]] = true;
        }

        vector<ll> summ;
        string cur = "";
        vector<bool> used(numbers.size(), false);

        for (int j = 0; j < n; j++)
        {
            if (!adds[j])
            {
                if (cur == "")
                {
                    cur = to_string(numbers[j]);
                    used[j] = true;
                }

                cur += to_string(numbers[j + 1]);
                used[j + 1] = true;
            }
            else
            {

                if (cur == "")
                {
                    cur = to_string(numbers[j]);
                    used[j] = true;
                }
                ll ao = stoll(cur);
                summ.push_back(ao);
                cur = "";
            }
        }
        if (cur != "")
        {
            ll ao = stoll(cur);
            summ.push_back(ao);
        }

        for (int j = 0; j < numbers.size(); j++)
        {
            if (!used[j])
            {
                summ.push_back(numbers[j]);
            }
        }

        ll angka = 0;
        for (int j = 0; j < summ.size(); j++)
        {

            angka += summ[j];
        }
        angkas.insert(angka);
    }

    cout << angkas.size() << endl;
}