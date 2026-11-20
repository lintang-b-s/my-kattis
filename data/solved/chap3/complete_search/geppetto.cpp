#include <bits/stdc++.h>
using namespace std;

int LSONE(int s)
{
    return (s) & -(s);
}

int main()
{
    int n, m;
    cin >> n >> m;
    vector<pair<int, int>> prohib;
    for (int i = 0; i < m; i++)
    {
        int a, b;
        cin >> a >> b;
        prohib.push_back({a, b});
    }

    vector<vector<int>> res;
    for (int mask = 0; mask < (1 << n); mask++)
    {
        vector<int> arr;
        int m = mask;
        while (m)
        {
            int two_pow_j = LSONE(m);
            int j = __builtin_ctz(two_pow_j) + 1;
            arr.push_back(j);
            m -= two_pow_j;
        }
        res.push_back(arr);
    }

    int counter = 0;
    for (int i = 0; i < res.size(); i++)
    {
        auto cur = res[i];
        bool valid = true;

        for (int j = 0; j < prohib.size(); j++)
        {
            int counter = 0;
            for (int k = 0; k < cur.size(); k++)
            {
                auto curProhib = prohib[j];
                if (curProhib.first == cur[k] || curProhib.second == cur[k])
                {
                    counter++;
                }
            }
            if (counter == 2)
            {
                valid = false;
                break;
            }
        }
        if (valid)
        {
            counter++;
        }
    }
    cout << counter << endl;
}
