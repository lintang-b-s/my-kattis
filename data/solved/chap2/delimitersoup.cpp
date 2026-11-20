#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/delimitersoup?tab=metadata
int main()
{
    int n;
    cin >> n;
    cin.ignore();
    string line;
    getline(cin, line);

    bool notOk = false;
    stack<char> tumpukan;
    for (int i = 0; i < n; i++)
    {
        char parenthese = line[i];
        if (parenthese == '(' or parenthese == '{' or parenthese == '[')
        {
            tumpukan.push(parenthese);
        }
        else if (parenthese == ' ')
        {
        }
        else
        {
            if (tumpukan.empty())
            {
                cout << parenthese << " " << i;
                notOk = true;
                break;
            }
            char topParenthese = tumpukan.top();
            if ((parenthese == ')' and topParenthese == '(') or (parenthese == '}' and topParenthese == '{') or (parenthese == ']' and topParenthese == '['))
            {
                tumpukan.pop();
            }
            else
            {
                cout << parenthese << " " << i;
                notOk = true;
                break;
            }
        }
    }

    if (!notOk)
    {
        cout << "ok so far";
    }

    return 0;
}