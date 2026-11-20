#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/throwns?tab=metadata

int main()
{
    int n, k;
    cin >> n >> k;

    stack<int> tumpukanLemparanBola;
    int posisiBolaNaga = 0;
    for (int j = 0; j < k; j++)
    { // worst case O(km)
        string s;
        cin >> s;
        bool angkaPosisiBocil = true;
        int posisiLempar = 0;
        if (s[0] == '-')
        {
            for (int i = 1; i < s.size(); i++)
            {
                if (!isdigit(s[i]))
                {
                    angkaPosisiBocil = false;
                }
            }
        }
        else
        {
            for (int i = 0; i < s.size(); i++)
            {
                if (!isdigit(s[i]))
                {
                    angkaPosisiBocil = false;
                }
            }
        }
        if (angkaPosisiBocil)
        {
            posisiLempar = stoi(s);

            tumpukanLemparanBola.push(posisiLempar);

            posisiBolaNaga = posisiBolaNaga + posisiLempar;
            posisiBolaNaga = (posisiBolaNaga % n + n) % n;
        }
        else
        {
            cin >> posisiLempar;
            for (int i = 0; i < posisiLempar; i++)
            { // O(m), m  jumlah operasi undo
                int undoKeI = tumpukanLemparanBola.top();
                tumpukanLemparanBola.pop();

                posisiBolaNaga = posisiBolaNaga - undoKeI;
                posisiBolaNaga = (posisiBolaNaga % n + n) % n;
            }
        }
    }
    cout << posisiBolaNaga;
}