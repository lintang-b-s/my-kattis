#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/server?tab=metadata
int main()
{

    int n;
    int T;
    cin >> n >> T;
    queue<int> tasks;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        tasks.push(a);
    }

    int count = 0;
    while (!tasks.empty() && tasks.front() <= T)
    { // O(n)
        T -= tasks.front();
        tasks.pop();
        count++;
    }

    cout << count;

    return 0;
}