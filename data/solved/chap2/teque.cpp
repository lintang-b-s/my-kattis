#include <bits/stdc++.h>

using namespace std;

/*
https://open.kattis.com/problems/teque?tab=metadata
*/

int main()
{
    deque<int> tequeKiri, tequeKanan;

    int n;
    cin >> n;
    string op;
    for (int i = 0; i < n; i++)
    {
        cin >> op;
        int x;
        cin >> x;
        if (op == "push_back")
        {
            tequeKanan.push_back(x); // O(1)

            if (tequeKanan.size() > tequeKiri.size())
            {
                int mid = tequeKanan.front();
                tequeKanan.pop_front();
                tequeKiri.push_back(mid); // O(1)
            }
        }
        else if (op == "push_front")
        {
            tequeKiri.push_front(x); // O(1)
            if (tequeKiri.size() > tequeKanan.size() + 1)
            {
                int mid = tequeKiri.back();
                tequeKiri.pop_back();
                tequeKanan.push_front(mid); // O(1)
            }
        }
        else if (op == "push_middle")
        {
            // push_middle
            tequeKiri.push_back(x);
            if (tequeKiri.size() > tequeKanan.size() + 1)
            {
                int mid = tequeKiri.back();
                tequeKiri.pop_back();
                tequeKanan.push_front(mid); // O(1)
            }
        }
        else
        {
            if (x >= tequeKiri.size())
            {
                cout << tequeKanan[x - tequeKiri.size()] << endl;
            }
            else
            {
                cout << tequeKiri[x] << endl;
            }
        }
    }

    return 0;
}