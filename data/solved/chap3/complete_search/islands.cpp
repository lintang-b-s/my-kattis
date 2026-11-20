#include <bits/stdc++.h>
using namespace std;

int LSONE(int s)
{
    return s & -s;
}

int main()
{
    int p;
    cin >> p;
    for (int i = 0; i < p; i++)
    {
        int k;
        cin >> k;
        vector<int> arr;
        for (int j = 0; j < 12; j++)
        {
            int a;
            cin >> a;
            arr.push_back(a);
        }

        vector<vector<int>> subsets;

        for (int mask = 0; mask < (1 << 12); mask++)
        {
            int m = mask;
            vector<int> subset;
            bool skip = false;
            while (m)
            {
                int two_pow_j = LSONE(m);
                int j = __builtin_ctz(two_pow_j);
                if (subset.size() > 0)
                {
                    auto last = subset.back();
                    if (last + 1 != j)
                    {
                        skip = true;
                        break;
                    }
                }
                subset.push_back(j);
                m -= two_pow_j;
            }
            if (skip)
            {
                continue;
            }
            subsets.push_back(subset);
        }

        int count = 0;
        for (int j = 0; j < subsets.size(); j++)
        {
            auto subsetid = subsets[j];
            if (subsetid.size() == 0 || subsetid[0] == 0 || subsetid[subsetid.size() - 1] == 11)
            {
                continue;
            }
            vector<int> subset;
            for (int k = 0; k < subsetid.size(); k++)
            {
                subset.push_back(arr[subsetid[k]]);
            }

            int mini = numeric_limits<int>::max();
            for (int k = 0; k < subset.size(); k++)
            {
                mini = min(mini, subset[k]);
            }
            int left = arr[subsetid[0] - 1];
            int right = arr[subsetid[subsetid.size() - 1] + 1];
            if (mini > left && mini > right)
            {
                count++;
            }
        }
        cout << i + 1 << " " << count << endl;
    }
}