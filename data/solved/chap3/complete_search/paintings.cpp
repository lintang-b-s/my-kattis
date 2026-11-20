#include <bits/stdc++.h>
using namespace std;

// O(n!*n). 
// n! permutation, each permutation copy the full array in O(n) works
int backtrack(int i, int n, vector<int> &output, vector<bool> &used, vector<int> &curr,
              vector<vector<bool>> &prohibited)
{
    if (i == n)
    {
        if (curr.size() == n && output.size() == 0)
        {
            for (int q = 0; q < n; q++)
            {
                output.push_back(curr[q]);
            }
        }
        if (curr.size() == n)
        {
            return 1;
        }
        return 0;
    }

    vector<string> nextProhib;

    int ans = 0;
    for (int j = 0; j < n; j++)
    {

        if (i > 0 && prohibited[curr[i - 1]][j])
        {
            continue;
        }
        if (!used[j])
        {
            used[j] = true;
            curr[i] = j;
            ans += backtrack(i + 1, n, output, used, curr, prohibited);
            used[j] = false;
        }
    }
    return ans;
}

int main()
{

    int t;
    cin >> t;

    for (int i = 0; i < t; i++)
    {
        int n, m;
        cin >> n;
        vector<string> colors(n);
        unordered_map<string, int> colorIds;

        vector<vector<bool>> prohibitedId(n, vector<bool>(n));

        for (int j = 0; j < n; j++)
        {
            string col;
            cin >> col;
            colors[j] = col;
            colorIds[col] = j;
        }

        cin >> m;
        for (int j = 0; j < m; j++)
        {
            string a, b;
            cin >> a >> b;

            int aid = colorIds[a];
            int bid = colorIds[b];
            prohibitedId[aid][bid] = true;
            prohibitedId[bid][aid] = true;
        }

        vector<int> curr(n);
        vector<int> output;
        vector<bool> used(n);
        int ans = backtrack(0, n, output, used, curr, prohibitedId);

        cout << ans << endl;
        for (int j = 0; j < output.size(); j++)
        {
            cout << colors[output[j]];
            if (j < output.size() - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}

// TLE
// void backtrack(int i, vector<string> colors, vector<vector<string>> &output, vector<string> curr,
//                vector<pair<string, string>> prohibited)
// {
//     if (i == colors.size())
//     {
//         if (curr.size() == colors.size())
//         {
//             output.push_back(curr);
//         }
//         return;
//     }

//     vector<string> nextProhib;

//     if (curr.size() > 0)
//     {
//         for (int q = 0; q < prohibited.size(); q++)
//         {
//             if (prohibited[q].first == curr[curr.size() - 1])
//             {
//                 nextProhib.push_back(prohibited[q].second);
//             }
//             else if (prohibited[q].second == curr[curr.size() - 1])
//             {
//                 nextProhib.push_back(prohibited[q].first);
//             }
//         }
//     }

//     for (int j = 0; j < colors.size(); j++)
//     {

//         bool alowedToAdd = true;
//         for (int q = 0; q < nextProhib.size(); q++)
//         {
//             if (colors[j] == nextProhib[q])
//             {
//                 alowedToAdd = false;
//             }
//         }

//         for (int q = 0; q < curr.size(); q++)
//         {
//             if (curr[q] == colors[j])
//             {
//                 alowedToAdd = false;
//             }
//         }

//         if (alowedToAdd)
//         {
//             curr.push_back(colors[j]);
//             backtrack(i + 1, colors, output, curr, prohibited);
//             curr.pop_back();
//         }
//     }
// }

// int main()
// {

//     int t;
//     cin >> t;

//     for (int i = 0; i < t; i++)
//     {
//         int n, m;
//         cin >> n;
//         vector<string> colors(n);
//         unordered_map<string, int> colorIds;

//         vector<pair<string, string>> prohibited;

//         for (int j = 0; j < n; j++)
//         {
//             string col;
//             cin >> col;
//             colors[j] = col;
//             colorIds[col] = j;
//         }

//         cin >> m;
//         for (int j = 0; j < m; j++)
//         {
//             string a, b;
//             cin >> a >> b;
//             prohibited.push_back({a, b});
//         }

//         vector<string> curr;
//         vector<vector<string>> output;
//         backtrack(0, colors, output, curr, prohibited);

//         // green red blue, 0 1 2

//         // red green blue, 1 0 2
//         // blue green red, 2 0 1

//         int k = output.size();
//         int best = 0;
//         for (int j = 1; j < k; j++)
//         {
//             for (int x = 0; x < output[j].size(); x++)
//             {
//                 auto a = output[j][x];
//                 auto b = output[best][x];
//                 if (a != b)
//                 {
//                     if (colorIds[a] < colorIds[b])
//                     {
//                         best = j;
//                         break;
//                     }
//                     else
//                     {
//                         break;
//                     }
//                 }
//             }
//         }

//         auto res = output[best];
//         cout << output.size() << endl;
//         for (int j = 0; j < res.size(); j++)
//         {
//             cout << res[j];
//             if (j < res.size() - 1)
//             {
//                 cout << " ";
//             }
//         }
//         cout << endl;
//     }
// }