#include <bits/stdc++.h>
using namespace std;

void permutation(vector<int> arr, int i, vector<vector<int>> &res)
{
    if (i == arr.size())
    {
        res.push_back(arr);
        return;
    }

    for (int j = i; j < arr.size(); j++)
    {
        swap(arr[j], arr[i]);
        permutation(arr, i + 1, res);
        swap(arr[j], arr[i]);
    }
}

int main()
{
    vector<int> arr(3);
    vector<pair<int, int>> rects;
    int totalArea = 0;
    for (int i = 0; i < 3; i++)
    {
        arr[i] = i;
        int h, w;
        cin >> h >> w;
        rects.push_back({h, w});
        totalArea += h * w;
    }

    int root = sqrt(totalArea);
    if (root * root != totalArea)
    {
        cout << "NO" << endl;
        return 0;
    }

    vector<vector<int>> perms;
    permutation(arr, 0, perms); // 3!

    bool can = false;
    for (int i = 0; i < perms.size(); i++) // 3! * 2^3
    {
        auto perm = perms[i];

        for (int ori1 = 0; ori1 < 2; ori1++)
        { // 0 horizontal, 1 vertical
            for (int ori2 = 0; ori2 < 2; ori2++)
            {
                for (int ori3 = 0; ori3 < 2; ori3++)
                {
                    auto a = rects[perm[0]];
                    auto b = rects[perm[1]];
                    auto c = rects[perm[2]];

                    int awidth = 0, aheight = 0;
                    int bwidth = 0, bheight = 0;
                    int cwidth = 0, cheight = 0;

                    int totalHeight = 0;
                    int totalWidth = 0;
                    if (ori1 == 0)
                    {
                        aheight = a.second;
                        awidth = a.first;
                    }
                    if (ori1 == 1)
                    {
                        aheight = a.first;
                        awidth = a.second;
                    }

                    if (ori2 == 0)
                    {
                        bheight = b.second;
                        bwidth = b.first;
                    }
                    if (ori2 == 1)
                    {
                        bheight = b.first;
                        bwidth = b.second;
                    }

                    if (ori3 == 0)
                    {
                        cheight = c.second;
                        cwidth = c.first;
                    }
                    if (ori3 == 1)
                    {
                        cheight = c.first;
                        cwidth = c.second;
                    }

                    if (ori1 == 0 && ori2 == 0 && ori3 == 0 &&
                        a.first == root && b.first == root && c.first == root)
                    {
                        if (a.second + b.second + c.second == root)
                        {
                            can = true;
                        }
                    }

                    if (ori1 == 1 && ori2 == 1 && ori3 == 1 &&
                        a.second == root && b.second == root && c.second == root)
                    {
                        if (a.first + b.first + c.first == root)
                        {
                            can = true;
                        }
                    }

                    if (cheight == root && aheight + bheight == root && cwidth + bwidth == root)
                    {
                        can = true;
                    }
                }
            }
        }
    }

    if (can)
    {
        cout << "YES" << endl;
    }
    else
    {
        cout << "NO" << endl;
    }
}

// WA
// int main()
// {
//     vector<int> arr(3);
//     vector<pair<int, int>> rects;
//     int totalArea = 0;
//     for (int i = 0; i < 3; i++)
//     {
//         arr[i] = i;
//         int h, w;
//         cin >> h >> w;
//         rects.push_back({h, w});
//         totalArea += h * w;
//     }

//     int root = sqrt(totalArea);
//     if (root * root != totalArea)
//     {
//         cout << "NO" << endl;
//         return 0;
//     }

//     vector<vector<int>> perms;
//     permutation(arr, 0, perms);

//     bool can = false;
//     for (int i = 0; i < perms.size(); i++)
//     {
//         auto perm = perms[i];

//         for (int ori1 = 0; ori1 < 2; ori1++)
//         { // 0 horizontal, 1 vertical
//             for (int ori2 = 0; ori2 < 2; ori2++)
//             {
//                 for (int ori3 = 0; ori3 < 2; ori3++)
//                 {
//                     auto a = rects[perm[0]];
//                     auto b = rects[perm[1]];
//                     auto c = rects[perm[2]];

//                     int totalHeight = 0;
//                     int totalWidth = 0;
//                     if (ori1 == 0)
//                     {
//                         totalHeight += a.second;
//                     }
//                     if (ori1 == 1)
//                     {
//                         totalWidth += a.first;
//                     }

//                     if (ori2 == 0)
//                     {
//                         totalHeight += b.second;
//                     }
//                     if (ori2 == 1)
//                     {
//                         totalWidth += b.first;
//                     }

//                     if (ori3 == 0)
//                     {
//                         totalHeight += c.second;
//                     }
//                     if (ori3 == 1)
//                     {
//                         totalWidth += c.first;
//                     }

//                     if (ori1 == 0 && ori2 == 0 && ori3 == 0 &&
//                         a.first == root && b.first == root && c.first == root)
//                     {
//                         if (a.second + b.second + c.second == root)
//                         {
//                             can = true;
//                         }
//                     }

//                      if (ori1 == 1 && ori2 == 1 && ori3 == 1 &&
//                         a.second == root && b.second == root && c.second == root)
//                     {
//                         if (a.first + b.first + c.first == root)
//                         {
//                             can = true;
//                         }
//                     }

//                     if (totalWidth * totalHeight == totalArea)
//                     {
//                         can = true;
//                     }
//                 }
//             }
//         }
//     }

//     if (can)
//     {
//         cout << "YES" << endl;
//     }
//     else
//     {
//         cout << "NO" << endl;
//     }
// }
