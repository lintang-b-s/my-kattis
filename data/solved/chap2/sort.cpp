#include <bits/stdc++.h>

using namespace std;
// https://open.kattis.com/problems/sort?tab=metadata
int main()
{
    int N, C;
    cin >> N >> C;
    vector<int> arr(N);
    unordered_map<int, int> idmap, freq;
    int id = 0;
    for (int i = 0; i < N; i++)
    {
        cin >> arr[i];
        freq[arr[i]]++;
        if (!idmap.count(arr[i]))
        {
            idmap[arr[i]] = id++;
        }
    }

    sort(arr.begin(), arr.end(), [&](int a, int b)
         {
             if (freq[a] != freq[b])
             {
                 return freq[a] > freq[b];
             }
             return idmap[a] < idmap[b]; });

    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i];
        if (i < arr.size() - 1)
        {
            cout << " ";
        }
    }
}

// Memory limit excedeed
// int main()
// {
//     int N, C;
//     cin >> N >> C;
//     vector<int> arr(N);
//     vector<int> freq(C + 1, 0);
//     for (int i = 0; i < N; i++)
//     {
//         cin >> arr[i];
//         freq[arr[i]]++;
//     }

//     vector<vector<int>> bucket(N + 1, vector<int>(0));
//     int maxid = 0;

//     unordered_set<int> seen;

//     for (int i = 0; i < N; i++)
//     {
//         if (seen.find(arr[i]) != seen.end())
//         {
//             continue;
//         }
//         // seen[arr[i]] = true;
//         seen.insert(arr[i]);
//         bucket[freq[arr[i]]].push_back(arr[i]);
//         maxid = max(maxid, freq[arr[i]]);
//     }

//     vector<int> res;
//     for (int i = maxid; i >= 0; i--)
//     {
//         vector<int> fr = bucket[i];
//         for (int a : fr)
//         {
//             for (int j = 0; j < i; j++)
//             {
//                 res.push_back(a);
//             }
//         }
//     }

// for (int i = 0; i < res.size(); i++)
// {
//     cout << res[i];
//     if (i < res.size() - 1)
//     {
//         cout << " ";
//     }
// }
// }