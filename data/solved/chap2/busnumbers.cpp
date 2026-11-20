#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/busnumbers?tab=metadata

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);

    int N;
    cin >> N;

    bool busStops[1002];

    memset(busStops, false, sizeof(busStops));

    int maxBusNum = 0;

    for (int i = 0; i < N; i++)
    { // O(n)
        int busnum;
        cin >> busnum;
        busStops[busnum] = true;
        maxBusNum = max(maxBusNum, busnum);
    }

    int j = 1, i = 0;

    vector<string> res;

    bool newCombin = true;
    while (j <= maxBusNum + 1)
    { // worst case O((maxBusNum + 1)^2)
        if (!busStops[j] && j > 0 && busStops[j - 1])
        {
            if (j - 1 - i + 1 > 2)
            {
                res.push_back(to_string(i) + "-" + to_string(j - 1));
            }
            else
            {
                for (int k = i; k < j; k++)
                {
                    res.push_back(to_string(k));
                }
            }
            newCombin = true;
        }

        if (newCombin && busStops[j])
        {
            newCombin = false;
            i = j;
        }

        j++;
    }

    for (int q = 0; q < res.size(); q++)
    {
        cout << res[q];
        if (q < res.size() - 1)
        {
            cout << " ";
        }
    }
}