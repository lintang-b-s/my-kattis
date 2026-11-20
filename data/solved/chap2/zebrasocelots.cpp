#include <bits/stdc++.h>

using namespace std;

/*

Z= 0
O= 1

dari atas ke bawah -> MSB to LSB dari bits
sample input 2:
1001 -> 1000 -> 0111 -> 0110 -> ..... -> 0000
9 kali bel berbunyi

*/

int main()
{

    long long bits = 0;
    int N;
    cin >> N;
    for (int i = 0; i < N; i++)
    { // O(N)
        char binatang;
        cin >> binatang;
        if (binatang == 'O')
        {
            bits |= 1LL << (N - i - 1);
        }

        // max digit with N bits
    }
    cout << bits << endl;

    // TLE
    // long long jumlahBelBerbunyi = 0;

    // while (true)
    // {
    //     int bitCounter = __builtin_popcount(bits);

    //     if (bitCounter == N)
    //     {
    //         break;
    //     }

    //     bits += 1;
    //     jumlahBelBerbunyi++;
    // }

    // cout << jumlahBelBerbunyi << endl;

    return 0;
}