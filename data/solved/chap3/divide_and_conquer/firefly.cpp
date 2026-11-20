#include <bits/stdc++.h>
using namespace std;

int main()
{
    int n, h;
    cin >> n >> h;
    vector<int> stalagmites;
    vector<int> stalactites;
    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        if (i % 2 == 0)
        {
            stalagmites.push_back(a);
        }
        else
        {
            stalactites.push_back(a);
        }
    }

    auto my_lower_bound = [](vector<int> &arr, int target)
    {
        int i = 0;
        int j = arr.size() - 1;
        int ans = arr.size();
        while (i <= j)
        {
            int m = i + (j - i) / 2;
            if (arr[m] >= target)
            {
                ans = m;
                j = m - 1;
            }
            else
            {
                i = m + 1;
            }
        }

        return ans;
    };

    auto my_upper_bound = [](vector<int> &arr, int target)
    {
        int i = 0;
        int j = arr.size() - 1;
        int ans = arr.size();
        while (i <= j)
        {
            int m = i + (j - i) / 2;
            if (arr[m] > target)
            {
                ans = m;
                j = m - 1;
            }
            else
            {
                i = m + 1;
            }
        }

        return ans;
    };

    sort(stalagmites.begin(), stalagmites.end()); // O((n/2) * log(n/2))
    sort(stalactites.begin(), stalactites.end()); // O((n/2) * log(n/2))

    int obstacle_hits = 999999999;
    int num_levels = 0;
    int m = n / 2;
    for (int i = 1; i <= h; i++)
    { // O(h * log n)

        int j = my_lower_bound(stalagmites, i);
        int stalag_count = m - 1 - j + 1;

        j = my_upper_bound(stalactites, h - i);
        int stalac_count = m - 1 - j + 1;

        if (stalac_count + stalag_count < obstacle_hits)
        {
            obstacle_hits = stalac_count + stalag_count;
            num_levels = 1;
        }
        else if (stalac_count + stalag_count == obstacle_hits)
        {
            num_levels++;
        }
    }

    cout << obstacle_hits << " " << num_levels << endl;
}

// tle
// int main()
// {
//     int n, h;
//     cin >> n >> h;
//     vector<int> stalagmites;
//     vector<int> stalactites;
//     for (int i = 0; i < n; i++)
//     {
//         int a;
//         cin >> a;
//         if (i % 2 == 0)
//         {
//             stalagmites.push_back(a);
//         }
//         else
//         {
//             stalactites.push_back(a);
//         }
//     }

//     sort(stalagmites.begin(), stalagmites.end());
//     sort(stalactites.begin(), stalactites.end());

//     int obstacle_hits = 999999999;
//     int num_levels = 0;
//     int m = n / 2;
//     for (int i = 1; i <= h; i++)
//     { // O(h * n)
//         int stalag_count = 0;
//         for (int j = m - 1; j >= 0; j--)
//         {
//             if (stalagmites[j] >= i)
//             {
//                 stalag_count++;
//             }
//             else
//             {
//                 break;
//             }
//         }
//         int stalac_count = 0;
//         for (int j = m - 1; j >= 0; j--)
//         {
//             if (stalactites[j] > h - i)
//             {
//                 stalac_count++;
//             }
//             else
//             {
//                 break;
//             }
//         }
//

//         if (stalac_count + stalag_count < obstacle_hits)
//         {
//             obstacle_hits = stalac_count + stalag_count;
//             num_levels = 1;
//         }
//         else if (stalac_count + stalag_count == obstacle_hits)
//         {
//             num_levels++;
//         }
//     }

//     cout << obstacle_hits << " " << num_levels << endl;
// }