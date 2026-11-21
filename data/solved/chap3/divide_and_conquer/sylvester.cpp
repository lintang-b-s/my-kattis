#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
int hadamard_dvq(ll n, ll i, ll j)
{
    if (n == 1)
    {
        return 1;
    }
    ll mid = n / 2;
    if (i < mid && j < mid)
    {
        return hadamard_dvq(n / 2, i, j);
    }
    else if (i < mid && j >= mid)
    {
        return hadamard_dvq(n / 2, i, j - mid);
    }
    else if (i >= mid && j < mid)
    {
        return hadamard_dvq(n / 2, i - mid, j);
    }
    else
    {
        return -hadamard_dvq(n / 2, i - mid, j - mid);
    }
}

// WA
// int hadamard_dvq(int n, int i, int j)
// {
//     if (n == 1)
//     {
//         return 1;
//     }
//     int mid = n / 2;
//     if (i < mid && j < mid)
//     {
//         return hadamard_dvq(n / 2, i, j);
//     }
//     else if (i < mid && j >= mid)
//     {
//         return hadamard_dvq(n / 2, i, j - mid);
//     }
//     else if (i >= mid && j < mid)
//     {
//         return hadamard_dvq(n / 2, i - mid, j);
//     }
//     else
//     {
//         return -hadamard_dvq(n / 2, i - mid, j - mid);
//     }
// }

// WA
// int hadamard_dvq(int n, int i, int j)
// {
//     if (n == 1)
//     {
//         return 1;
//     }
//     int mid = n / 2;
//     if (i < mid && j < mid)
//     {
//         return hadamard_dvq(n / 2, i, j);
//     }
//     else if (i < mid && j >= mid)
//     {
//         return hadamard_dvq(n / 2, i, j - 2);
//     }
//     else if (i >= mid && j < mid)
//     {
//         return hadamard_dvq(n / 2, i - 2, j);
//     }
//     else
//     {
//         return -hadamard_dvq(n / 2, i - 2, j - 2);
//     }
// }

int main()
{
    int t;
    cin >> t;
    while (t--)
    {
        ll n, x, y, w, h;
        cin >> n >> x >> y >> w >> h;
        // O(w*h*lgn)
        for (int i = y; i < y + h; i++)
        {
            for (int j = x; j < x + w; j++)
            {
                // T(n)=T(n/2)+1
                // case 2 master theorem O(lgn)
                cout << hadamard_dvq(n, i, j) << " "; // O(lgn)
            }
            cout << endl;
        }
    }
}