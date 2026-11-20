#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/evenup?tab=metadata
int main()
{
    int n;
    cin >> n;
    stack<int> tumpukan;
    for (int i = 0; i < n; i++)
    { // O(n)
        int a;
        cin >> a;
        if (!tumpukan.empty())
        {
            int lastItem = tumpukan.top();
            if ((lastItem + a) % 2 == 0)
            {
                tumpukan.pop();
            }
            else
            {
                tumpukan.push(a);
            }
        }
        else
        {
            tumpukan.push(a);
        }
    }
    cout << tumpukan.size();
}