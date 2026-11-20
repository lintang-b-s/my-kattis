#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/circuitmath?tab=metadata
/*
ini cuma postfix notation

*/
int main()
{
    int n;
    cin >> n;
    bool nilaiVar[n];
    for (int i = 0; i < n; i++)
    {
        char nilai;
        cin >> nilai;
        if (nilai == 'T')
        {
            nilaiVar[i] = true;
        }
        else
        {
            nilaiVar[i] = false;
        }
    }

    char op;
    stack<bool> tumpukanPostfix;
    while (cin >> op)
    {
        if (op - 'A' >= 0 && op - 'A' < n)
        {
            int a = op - 'A';
            tumpukanPostfix.push(nilaiVar[a]);
        }
        else
        {
            if (op == '*')
            {
                bool operandSatu = tumpukanPostfix.top();
                tumpukanPostfix.pop();
                bool operandDua = tumpukanPostfix.top();
                tumpukanPostfix.pop();
                tumpukanPostfix.push(operandDua & operandSatu);
            }
            else if (op == '+')
            {
                bool operandSatu = tumpukanPostfix.top();
                tumpukanPostfix.pop();
                bool operandDua = tumpukanPostfix.top();
                tumpukanPostfix.pop();
                tumpukanPostfix.push(operandDua | operandSatu);
            }
            else
            {
                bool operandSatu = tumpukanPostfix.top();
                tumpukanPostfix.pop();
                tumpukanPostfix.push(!operandSatu);
            }
        }
    }

    cout << (tumpukanPostfix.top() ? 'T' : 'F');

    return 0;
}