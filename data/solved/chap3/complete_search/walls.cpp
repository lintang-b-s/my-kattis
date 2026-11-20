#include <bits/stdc++.h>
using namespace std;

int main()
{
    int l, w, n, r;
    cin >> l >> w >> n >> r;
    vector<pair<double, double>> cranes;

    for (int i = 0; i < n; i++)
    {
        double x, y;
        cin >> x >> y;
        cranes.push_back({x, y});
    }

    vector<pair<double, double>> walls;
    walls.push_back({-l / 2.0, 0});
    walls.push_back({l / 2.0, 0});
    walls.push_back({0, w / 2.0});
    walls.push_back({0, -w / 2.0});

    vector<vector<int>> covers;

    vector<int> combinations;

    for (int i = 0; i < n; i++)
    { // O(n^4)
        auto crane = cranes[i];

        int mask1 = 0;

        for (int q = 0; q < 4; q++)
        {
            auto wall = walls[q];
            bool isInCircle = (crane.first - wall.first) * (crane.first - wall.first) + (crane.second - wall.second) * (crane.second - wall.second) <= r * r;
            if (isInCircle)
            {
                mask1 |= 1 << q;
            }
        }

        if (mask1 == 15)
        {
            cout << 1 << endl;
            return 0;
        }

        for (int j = 0; j < n; j++)
        {
            if (j == i)
            {
                continue;
            }
            int mask2 = 0;
            auto crane2 = cranes[j];

            for (int q = 0; q < 4; q++)
            {

                auto wall = walls[q];
                bool isInCircle = (crane2.first - wall.first) * (crane2.first - wall.first) + (crane2.second - wall.second) * (crane2.second - wall.second) <= r * r;
                if (isInCircle)
                {
                    mask2 |= 1 << q;
                }
            }

            if ((mask1 | mask2) == 15)
            {
                combinations.push_back(2);
            }

            for (int k = 0; k < n; k++)
            {
                if (k == i || k == j)
                {
                    continue;
                }
                auto crane3 = cranes[k];
                int mask3 = 0;

                for (int q = 0; q < 4; q++)
                {
                    auto wall = walls[q];
                    bool isInCircle = (crane3.first - wall.first) * (crane3.first - wall.first) + (crane3.second - wall.second) * (crane3.second - wall.second) <= r * r;
                    if (isInCircle)
                    {
                        mask3 |= 1 << q;
                    }
                }

                if ((mask1 | mask2 | mask3) == 15)
                {
                    combinations.push_back(3);
                }

                for (int l = 0; l < n; l++)
                {

                    if (l == i || l == j || l == k)
                    {
                        continue;
                    }
                    auto crane4 = cranes[l];
                    int mask4 = 0;
                    for (int q = 0; q < 4; q++)
                    {

                        auto wall = walls[q];
                        bool isInCircle = (crane4.first - wall.first) * (crane4.first - wall.first) + (crane4.second - wall.second) * (crane4.second - wall.second) <= r * r;
                        if (isInCircle)
                        {
                            mask4 |= 1 << q;
                        }
                    }

                    if ((mask1 | mask2 | mask3 | mask4) == 15)
                    {
                        combinations.push_back(4);
                    }
                }
            }
        }
    }
    if (combinations.size() > 0)
    {
        sort(combinations.begin(), combinations.end());
        cout << combinations[0] << endl;
        return 0;
    }
    cout << "Impossible" << endl;
}


