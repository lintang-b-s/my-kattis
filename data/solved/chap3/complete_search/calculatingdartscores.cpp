#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n;
    cin >> n;
    int d1type = 0, d2type = 0, d3type = 0;
    int d1num = 0, d2num = 0, d3num = 0;
    if (n == 0 || n > 180)
    {
        cout << "impossible" << endl;
        return 0;
    }
    else if (n == 2)
    {
        cout << "double 1" << endl;
        return 0;
    }
    else if (n == 1)
    {
        cout << "single 1" << endl;
        return 0;
    }

    auto solve = [&]()
    {
        // 20^3 * 3^3
        for (int d1 = 1; d1 <= 20; d1++)
        {
            for (int d2 = 1; d2 <= 20; d2++)
            {
                for (int d3 = 1; d3 <= 20; d3++)
                {
                    for (int i = 1; i <= 3; i++)
                    {
                        for (int j = 1; j <= 3; j++)
                        {
                            for (int k = 1; k <= 3; k++)
                            {
                                if (d1 * i + d2 * j + d3 * k == n)
                                {
                                    d1num = d1, d2num = d2, d3num = d3;
                                    d1type = i, d2type = j, d3type = k;
                                    return 0;
                                }
                            }
                        }
                    }
                }
            }
        }
        return 0;
    };
    solve();

    auto getType = [](int dtype)
    {
        switch (dtype)
        {
        case 1:

            return "single";
        case 2:

            return "double";
        case 3:

            return "triple";
        default:
            break;
        }
        return "";
    };

    if (d1type != 0)
    {
        cout << getType(d1type) << " " << d1num << endl;
    }
    if (d2type != 0)
    {
        cout << getType(d2type) << " " << d2num << endl;
    }
    if (d3type != 0)
    {
        cout << getType(d3type) << " " << d3num << endl;
    }
    if (d1type == 0 && d2type == 0 && d3type == 0)
    {
        cout << "impossible" << endl;
    }
}
