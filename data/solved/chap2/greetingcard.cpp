#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;
// https://open.kattis.com/problems/greetingcard?tab=metadata

int main()
{
    int n;
    cin >> n;

    unordered_set<ll> pointsSet(0);
    vector<pair<int, int>> points;

    int pp[8][2] = {{1118, 1680}, {-1118, -1680}, {-1118, 1680}, {1118, -1680}, {1680, 1118}, {-1680, 1118}, {1680, -1118}, {-1680, -1118}};
    // diff = 2018 if only if
    // 1. x2-x1= 2018 or y2-y1=2018
    // 2. (x2-x1=1680 and y2-y1=1118) or (x2-x1=1118 and y2-y1=1680)

    // {(x+2018, y), (x,y+2018), (x-2018, y), (x,y-2018),
    // (x+1118, y+1680), (x+1680, x+1118), (x-1118, y-1680),
    // (x-1118, y+1680), (x+1118, y-1680), (x-1680, x+1118), (x+1680, y-1118),
    // (x-1680, y-1118)}

    auto bitpack = [](ll x, ll y)
    {
        return (x << 32) | (y);
    };

    int patterns = 0;

    for (int i = 0; i < n; i++)
    { // T(n)<= c*n =O(n). c=8.
        ll x, y;
        cin >> x >> y;

        int xPlusA = x + 2018;

        int xMinA = x - 2018;

        int yPlusA = y + 2018;

        int yMinA = y - 2018;
        if (pointsSet.find(bitpack(xPlusA, y)) != pointsSet.end())
        {
            patterns++;
        }

        if (pointsSet.find(bitpack(xMinA, y)) != pointsSet.end())
        {
            patterns++;
        }
        if (pointsSet.find(bitpack(x, yPlusA)) != pointsSet.end())
        {
            patterns++;
        }
        if (pointsSet.find(bitpack(x, yMinA)) != pointsSet.end())
        {
            patterns++;
        }

        for (int j = 0; j < 8; j++)
        {
            auto p = pp[j];

            if (pointsSet.find(bitpack(x + p[0], y + p[1])) != pointsSet.end())
            {
                patterns++;
            }
        }
        pointsSet.insert(bitpack(x, y));
    }

    cout << patterns << endl;

    // TLE O(n^2)
    // int pattern = 0;
    // for (int i = 0; i < n; i++)
    // {
    //     for (int j = i + 1; j < n; j++)
    //     {
    //         auto p1 = points[i];
    //         auto p2 = points[j];

    //         ll xdiff = (p2.first - p1.first) * (p2.first - p1.first);
    //         ll ydiff = (p2.second - p1.second) * (p2.second - p1.second);

    //         ll dist = xdiff + ydiff;
    //         if (dist == 2018ULL * 2018ULL)
    //         {
    //             pattern++;
    //         }
    //     }
    // }
    // cout << pattern << endl;
}