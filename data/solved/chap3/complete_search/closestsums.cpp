#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    int i = 0;
    while (cin >> n)
    {
        cout << "Case " << i + 1 << ":" << endl;

        vector<int>
            as;
        for (int i = 0; i < n; i++)
        {
            int a;
            cin >> a;
            as.push_back(a);
        }

        sort(as.begin(), as.end());

        int m;
        cin >> m;

        for (int q = 0; q < m; q++)
        {
            int query;
            cin >> query;
            int minDist = 1e9;
            int bestSum = 0;
            // O(n^2)
            for (int i = 0; i < n; i++)
            {
                int a = as[i];
                for (int j = 0; j < n; j++)
                {
                    if (i == j)
                    {
                        continue;
                    }
                    int b = as[j];
                    int sum = a + b;
                    if (abs(sum - query) < minDist)
                    {
                        minDist = abs(sum - query);
                        bestSum = sum;
                    }
                }
            }
            cout << "Closest sum to " << query << " is " << bestSum << "." << endl;
        }
        i++;
    }
}