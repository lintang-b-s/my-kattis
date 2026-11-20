#include <bits/stdc++.h>
using namespace std;

/*
https://open.kattis.com/problems/jugglingpatterns?tab=metadata

let x_i=durasi bola di udara dari pattern-i,
b_i=beat dari pattern-i
t_i= waktu bola mendarat dari pattern-i,
n = pattern.size()
c = cylce dari inf pattern

for each 1<=i<=n:
x_i + b_i + n*c = t_i + n*c


let q_i = t_i + n*c
q_i = q_j, for i != j if only if: 


(x_i + b_i) % n  = (x_j + b_j ) % n, i != j, contoh:

"543":
(5+1) % 3 = 0
(4+1) % 3 = 0 
5 dan 4 invalid karena waktu bola mendarat sama


buat array dg index = (x_i + b_i) % n  , for each 1<=i<=n

if the index already true untuk next i, pattern invalid
*/

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);

    string pattern;
    while (cin >> pattern)
    {
        bool invalid = false;

        float balls = 0;
        for (int i = 0; i < pattern.size(); i++)
        {
            char p = pattern[i];
            int pint = p - '0';
            balls += pint;
        }
        balls /= pattern.size();

        if (floor(balls) != balls)
        {
            invalid = true;
        }

        if (invalid)
        {
            cout << pattern << ": invalid # of balls" << endl;
        }

        vector<bool> waktuTangkap(pattern.size());
        if (!invalid)
        {
            for (int i = 0; i < pattern.size(); i++)
            { // O(len(pattern))
                char p = pattern[i];
                int pint = p - '0';
                if (waktuTangkap[(pint + i) % pattern.size()] == true)
                {
                    invalid = true;
                    break;
                }
                waktuTangkap[(pint + i) % pattern.size()] = true;
            }

            if (invalid)
            {
                cout << pattern << ": invalid pattern" << endl;
            }else {
                cout << pattern << ": valid with " << (int) balls << " balls" << endl;
            }
        }

    
    }
}