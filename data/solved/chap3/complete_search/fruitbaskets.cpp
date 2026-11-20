#include <bits/stdc++.h>
using namespace std;

int LSONE(int s)
{ // get least significant bit dari s
    return s & -s;
}

typedef long long ll;
// O(2^n) with lots of pruning
void backtrack(int i, vector<ll> fruits, ll basket_weight, ll &tot)
{

    if (i >= fruits.size() || basket_weight >= 200)
    {
        return;
    }
    basket_weight += fruits[i];

    if (basket_weight < 200)
    {
        tot += basket_weight;
    }
    backtrack(i + 1, fruits, basket_weight, tot);
    basket_weight -= fruits[i];
    backtrack(i + 1, fruits, basket_weight, tot);
}

int main()
{

    int n;
    cin >> n;

    vector<ll> fruits;
    ll tot_all = 0;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        fruits.push_back(a);
        tot_all += (((ll)1 << (n - 1))) * a;
    }

    ll tot = 0;
    backtrack(0, fruits, 0, tot);

    cout << tot_all - tot << endl;
}

// TLE
// int main()
// {

//     int n;
//     cin >> n;

//     vector<ll> fruits;
//     ll tot_all = 0;
//     for (int i = 0; i < n; i++)
//     {
//         int a;
//         cin >> a;
//         fruits.push_back(a);
//         tot_all += (((ll)1 << (n - 1))) * a;
//     }

//     ll tot = 0;
//     for (int mask = 0; (ll)mask < ((ll)1 << n); mask++)
//     {
//         int m = mask;
//         vector<int> subset;
//         ll tots = 0;
//         int fruit_count = 0;

//         while (m)
//         {
//             if (fruit_count > 3)
//             {
//                 break;
//             }
//             int two_pow_j = LSONE(m);
//             int j = __builtin_ctz(two_pow_j);
//             subset.push_back(j);
//             tots += fruits[j];
//             if (tots >= 200)
//             {
//                 break;
//             }
//             m -= two_pow_j;
//             fruit_count++;
//         }

//         if (tots < 200)
//         {
//             tot += tots;
//         }
//     }
//     cout << tot_all - tot << endl;
// }

// WA
// int main()
// {
//     unordered_set<int> fruitSet;
//     int n;
//     cin >> n;
//     for (int i = 0; i < n; i++)
//     {
//         int a;
//         cin >> a;
//         fruitSet.insert(a);
//     }
//     vector<ll> fruits;
//     n = 0;
//     for (auto f : fruitSet)
//     {
//         fruits.push_back(f);
//         n++;
//     }

//     ll tot = 0;
//     for (int mask = 0; mask < (1 << n); mask++)
//     {
//         int m = mask;
//         vector<int> subset;
//         while (m)
//         {
//             int two_pow_j = LSONE(m);
//             int j = __builtin_ctz(two_pow_j);
//             subset.push_back(j);
//             m -= two_pow_j;
//         }

//         ll tots = 0;
//         for (auto j : subset)
//         {
//             tots += fruits[j];
//         }

//         if (tots >= 200)
//         {
//             tot += tots;
//         }
//     }
//     cout << tot << endl;
// }