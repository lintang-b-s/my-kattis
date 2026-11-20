#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int main()
{
    int n;
    cin >> n;
    vector<ll> universe(n);
    for (int i = 0; i < universe.size(); i++)
    {
        cin >> universe[i];
    }

    ll killcount = 0;
    bool udah_mas = false;
    ll dunia_terkecil = universe[n - 1];
    vector<ll> suffixmin(n);
    for (int i = n - 1; i >= 0; i--)
    { // O(n)
        dunia_terkecil = min(dunia_terkecil, universe[i]);
        suffixmin[i] = dunia_terkecil;
    }

    for (int i = n - 1; i >= 0; i--)
    {
        if (suffixmin[i] < universe[i])
        {

            killcount += universe[i] - (suffixmin[i] - 1);
            universe[i] = (suffixmin[i] - 1);

            if (i > 0)
            {
                suffixmin[i - 1] = min(suffixmin[i - 1], universe[i]);
            }
        }
    }

    if (universe[0] == 0)
    {
        cout << 1 << endl;
        return 0;
    }

    for (int i = 1; i < n; i++)
    { // O(n)
        if (universe[i] <= universe[i - 1] || universe[i] == 0)
        {
            cout << 1 << endl;
            return 0;
        }
    }
    cout << killcount << endl;
}

// TLE
// int main()
// {
//     int n;
//     cin >> n;
//     vector<ll> universe(n);
//     for (int i = 0; i < universe.size(); i++)
//     {
//         cin >> universe[i];
//     }

//     ll killcount = 0;
//     bool udah_mas = false;
//     for (int i = 0; i < universe.size(); i++)
//     { // O(n^2)
//         ll dunia_terkecil = numeric_limits<ll>::max();
//         for (int j = i + 1; j < universe.size(); j++)
//         {
//             if (universe[j] < universe[i])
//             {
//                 dunia_terkecil = min(dunia_terkecil, universe[j]);
//             }
//         }

//         if (dunia_terkecil < numeric_limits<ll>::max())
//         {
//             killcount += universe[i] - (dunia_terkecil - 1);
//             universe[i] = dunia_terkecil - 1;
//         }
//     }
//     for (int i = 1; i < universe.size(); i++)
//     { // O(n)
//         if (universe[i] <= universe[i - 1])
//         {
//             cout << 1 << endl;
//             return 0;
//         }
//     }
//     cout << killcount << endl;
// }