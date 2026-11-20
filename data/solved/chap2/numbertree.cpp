#include <bits/stdc++.h>

using namespace std;
/*
https://open.kattis.com/problems/numbertree?tab=metadata

misal perfect binary tree h=3 (1-indexed).

root ori=1
leaves paling kanan ori=15

di soal ini:
root = 15 = (2^(h+1))-1 - root ori + 1
leaves paling kanan = 1 = (2^(h+1))-1 - leaves paling kanan ori + 1
*/

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);

    int tinggiPohon;
    string cmd;
    cin >> tinggiPohon >> cmd;

    int simpul = 1;
    for (int i = 0; i < cmd.size(); i++)
    { // O(len(H))
        if (cmd[i] == 'L')
        {
            simpul *= 2;
        }
        else
        {
            simpul = simpul * 2 + 1;
        }
    }

    int jumlahSimpul = (1 << (tinggiPohon + 1) )- 1;
    cout << jumlahSimpul - simpul + 1;
}