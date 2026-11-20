#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/snapperhard?tab=metadata
/*

N=4
0000
0001
0010
.
.
.
.
1111 -> ON K=15
0001 -> 16 = 0 = 16%16
0010 -> 16 = 1 = 17%16
.
.
.


jadi basically:
C = K % 2^N

cek apakah semua N bit pada C sama dengan 1.
kalau ya -> ON
else: OFF

*/

int main()
{

    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int N, K;
        cin >> N >> K;
        int C = K % (1 << N);
        bool afkhSemuaON = true;

        // O(N)
        for (int j = 0; j < N; j++)
        {
            if ((C & (1 << j)) == 0)
            {
                afkhSemuaON = false;
            }
        }

        if (afkhSemuaON)
        {
            cout << "Case #" << i + 1 << ": ON" << endl;
        }
        else
        {
            cout << "Case #" << i + 1 << ": OFF" << endl;
        }
    }
}