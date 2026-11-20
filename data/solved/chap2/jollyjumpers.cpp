#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    while (cin >> n)
    {
        vector<int> arr(n);
        for (int i = 0; i < n; i++)
        {
            cin >> arr[i];
        }

        if (n == 1)
        {
            cout << "Jolly\n";
            continue;
        }

        vector<bool> seen(n, false);

        for (int i = 0; i < arr.size() - 1; i++)
        {
            int diff = abs(arr[i] - arr[i + 1]);
            if (diff <= n - 1 && diff >= 1)
            {
                seen[diff] = true;
            }
        }

        bool jolly = true;
        for (int i = 1; i < n; i++)
        {
            if (!seen[i])
            {
                jolly = false;
                break;
            }
        }
        if (jolly)
        {
            cout << "Jolly\n";
        }
        else
        {
            cout << "Not jolly\n";
        }
    }

    return 0;
}