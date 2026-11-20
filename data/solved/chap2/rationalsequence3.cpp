#include <bits/stdc++.h>
using namespace std;

/*
https://open.kattis.com/problems/rationalsequence3

representasi biner:
root: 00000001: (b1,b2,...., b7, 1)
left child dari root: 00000010: (b1,b2,...., b7,1,0) (or bit shift to the left 1 time)
right child dari root: 00000011: (b1,b2,...., b7,1,1) (or bit right to the right 1 time)

jadi given N:
binary representation dari N:
MSB dari binary representation dari N adalah bit 1 dari root
jika kita remove msb, dari left to right adalah path dari root ke n
misal N= 11: 1011
011 adalah hasil dari traverse dari root->left->right->right

*/

int main()
{
    int P;
    cin >> P;

    for (int i = 0; i < P; i++)
    {
        int K, n;
        cin >> K >> n;

        long long p = 1, q = 1;
        long long mask = 1 << 30;
        if (n == 1)
        {
            cout << K << " " << "1/1" << endl;
            continue;
        }

        // dapetin msb
        while (mask && (n & mask) == 0)
        { // 30 ops
            mask >>= 1;
        }

        n &= ~mask;
        mask >>= 1;

        while (mask)
        { // O (30)
            if ((n & mask) != 0)
            {
                p = p + q;
            }
            else
            {

                q = p + q;
            }
            mask >>= 1;
        }

        cout << K << " " << p << "/" << q << endl;
    }

    // TLE
    // for (int i = 0; i < P; i++)
    // {
    //     int K, n;
    //     cin >> K >> n;

    //     vector<pair<int, int>> pohon(0);
    //     pohon.push_back({0,0}); // dummy
    //     pohon.push_back({1,1}); // akar

    //     for (int j = 2; j <= n; j++)
    //     { O(n), tapi n up to 2 147 483 647
    //         if (j % 2 == 0)
    //         {
    //             auto [p, q] = pohon[j / 2];
    //             pohon.push_back(make_pair(p, p + q));
    //         }
    //         else
    //         {
    //             auto [p, q] = pohon[(j - 1) / 2];
    //             pohon.push_back(make_pair(p + q, q));
    //         }
    //     }

    //     auto [p, q] = pohon[n];
    //     cout << K << " " << p << "/" << q << endl;
    // }
}
