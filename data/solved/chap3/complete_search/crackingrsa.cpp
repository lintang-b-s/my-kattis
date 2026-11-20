#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
vector<ll> sieves_of_erathostenes(ll n)
{ // O(n log logn) https://cp-algorithms.com/algebra/sieve-of-eratosthenes.html

    vector<bool> is_prime(n + 1, true);
    is_prime[0] = false, is_prime[1] = false;
    for (int i = 2; i <= n; i++)
    {
        if (is_prime[i] && (ll)i * i <= n)
        {
            for (int j = i * i; j <= n; j += i)
            {
                is_prime[j] = false;
            }
        }
    }

    vector<ll> primes;
    for (ll p = 0; p < is_prime.size(); p++)
    {
        if (is_prime[p])
        {
            primes.push_back(p);
        }
    }
    return primes;
}

vector<ll> totient(ll n)
{
    vector<ll> primes = sieves_of_erathostenes(1000);

    vector<ll> totients;

    for (int i = 0; i < primes.size(); i++)
    {
        auto p = primes[i];
        for (int j = 0; j < primes.size(); j++)
        {
            auto q = primes[j];
            if (p * q == n)
            {
                totients.push_back((p - 1) * (q - 1));
            }
        }
    }

    return totients;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        ll n, e;
        cin >> n >> e;

        auto totients = totient(n);
        bool udah_bang = false;
        for (ll d = 1; d <= n; d++)
        {
            for (auto tot : totients)
            {
                if ((d * e - 1) % tot == 0)
                {
                    cout << d << endl;
                    udah_bang = true;
                    break;
                }
            }
            if (udah_bang)
            {
                break;
            }
        }
    }
}

