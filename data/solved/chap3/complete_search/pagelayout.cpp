#include <bits/stdc++.h>
using namespace std;

struct rectangle
{
    int height, width;
    int x, y;
};

int LSONE(int S)
{ // least significant bit
    return ((S) & -(S));
}

bool isOverlap(rectangle a, rectangle b)
{

    if (a.y + a.height <= b.y || b.y + b.height <= a.y)
    {
        return false;
    }

    if (a.x >= b.x + b.width || b.x >= a.x + a.width)
    {
        return false;
    }

    return true;
}

// O(2^n).
// 2^n number of all possible subsets. binomial theorem with a=b=1.
void backtrack(int i, vector<rectangle> &rects, vector<int> overlaping_rects, int bitset, int area, int &maxi)
{

    int n = rects.size();
    if (i == n)
    {
        maxi = max(maxi, area);
        return;
    }

    bool valid = (overlaping_rects[i] & bitset) == 0;
    if (valid)
    {
        bitset = bitset | (1 << i);
        backtrack(i + 1, rects, overlaping_rects, bitset, area + rects[i].height * rects[i].width, maxi);
        bitset = bitset & ~(1 << i);
    }

    backtrack(i + 1, rects, overlaping_rects, bitset, area, maxi);
}

int main()
{

    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }

        vector<rectangle> rects;

        for (int i = 0; i < n; i++)
        {
            int h, w, x, y;
            cin >> w >> h >> x >> y;
            rectangle rect{h, w, x, y};
            rects.push_back(rect);
        }

        vector<int> overlaping_rects(n);
        for (int j = 0; j < n; j++)
        {

            for (int k = 0; k < n; k++)
            {
                if (j == k)
                {
                    continue;
                }

                if (isOverlap(rects[j], rects[k]))
                {
                    overlaping_rects[j] |= (1 << k);
                }
            }
        }

        int maxi = 0;
        backtrack(0, rects, overlaping_rects, 0, 0, maxi);
        cout << maxi << endl;
    }
}

// TLE lagi
// // O(2^n * n).
// // 2^n number of all possible subsets
// // O(n) works per each subset
// void backtrack(int i, vector<rectangle> &rects, int bitset, int &maxi)
// {

//     int n = rects.size();
//     if (i == n)
//     {
//         vector<bool> used(n);
//         while (bitset)
//         {
//             int jv = LSONE(bitset);
//             int j = __builtin_ctz(jv);
//             used[j] = true;
//             bitset -= jv;
//         }

//         int area = 0;
//         for (int j = 0; j < n; j++)
//         {
//             if (used[j])
//             {
//                 area += rects[j].height * rects[j].width;
//             }
//         }
//         maxi = max(maxi, area);
//         return;
//     }

//     vector<bool> used(n);
//     int bs = bitset;
//     while (bs)
//     {
//         int jv = LSONE(bs);
//         int j = __builtin_ctz(jv);
//         used[j] = true;
//         bs -= jv;
//     }

//     bool valid = true;
//     for (int j = 0; j < n; j++)
//     {
//         if (!used[j])
//         {
//             continue;
//         }
//         if (isOverlap(rects[j], rects[i]))
//         {
//             valid = false;
//         }
//     }

//     if (valid)
//     {
//         bitset = bitset | (1 << i);
//         backtrack(i + 1, rects, bitset, maxi);
//         bitset = bitset & ~(1 << i);
//     }

//     backtrack(i + 1, rects, bitset, maxi);
// }

// int main()
// {

//     int n;
//     while (cin >> n)
//     {
//         if (n == 0)
//         {
//             break;
//         }

//         vector<rectangle> rects;

//         for (int i = 0; i < n; i++)
//         {
//             int h, w, x, y;
//             cin >> h >> w >> x >> y;
//             rectangle rect{h, w, x, y};
//             rects.push_back(rect);
//         }

//         int maxi = 0;
//         backtrack(0, rects, 0, maxi);
//         cout << maxi << endl;
//     }
// }

// TLE
// // O(2^n * n^2).
// // 2^n number of all possible subsets
// // n^2 cek overlap
// void backtrack(int i, vector<rectangle> rects, int bitset, int &maxi)
// {

//     int n = rects.size();
//     if (i == n)
//     {
//         vector<bool> used(n);
//         while (bitset)
//         {
//             int jv = LSONE(bitset);
//             int j = __builtin_ctz(jv);
//             used[j] = true;
//             bitset -= jv;
//         }

// for (int j = 0; j < n; j++)
// {
//     if (!used[j])
//     {
//         continue;
//     }
//     for (int k = 0; k < n; k++)
//     {
//         if (j == k || !used[k])
//         {
//             continue;
//         }

//         if (isOverlap(rects[j], rects[k]))
//         {
//             used[j] = false;
//         }
//     }
// }

//         int area = 0;
//         for (int j = 0; j < n; j++)
//         {
//             if (used[j])
//             {
//                 area += rects[j].height * rects[j].width;
//             }
//         }
//         maxi = max(maxi, area);
//         return;
//     }

//     bitset = bitset | (1 << i);
//     backtrack(i + 1, rects, bitset, maxi);
//     bitset = bitset & ~(1 << i);
//     backtrack(i + 1, rects, bitset, maxi);
// }

// int main()
// {

//     int n;
//     while (cin >> n)
//     {
//         if (n == 0)
//         {
//             break;
//         }

//         vector<rectangle> rects;

//         for (int i = 0; i < n; i++)
//         {
//             int h, w, x, y;
//             cin >> h >> w >> x >> y;
//             rectangle rect{h, w, x, y};
//             rects.push_back(rect);
//         }

//         int maxi = 0;
//         backtrack(0, rects, 0, maxi);
//         cout << maxi << endl;
//     }
// }
