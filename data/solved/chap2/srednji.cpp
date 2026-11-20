#include <bits/stdc++.h>
using namespace std;

int main()
{
    int N, B;
    cin >> N >> B;
    vector<int> arr;

    int BId = 0;
    for (int i = 0; i < N; i++)
    {
        int a;
        cin >> a;
        arr.push_back(a);
        if (a == B)
        {
            BId = i;
        }
    }

    int mid = BId;

    // store delta(P), where P is subsequence
    // delta(P) = # higher than B - #less than B
    map<int, int> deltaFreq;
    deltaFreq[0] = 1;

    int delta = 0;
    for (int l = BId - 1; l >= 0; l--)
    { // O(NlogN)
        if (arr[l] > B)
        {
            delta++;
        }
        else
        {
            delta--;
        }
        deltaFreq[delta]++; // O(logN)
    }

    int count = deltaFreq[0];
    delta = 0;
    for (int r = BId + 1; r < N; r++)
    { // O(N)
        if (arr[r] > B)
        {
            delta++;
        }
        else
        {
            delta--;
        }
        count += deltaFreq[-delta];
    }
    cout << count << endl;

    // for (int l = BId; l >= 0; l--)
    // { // O(N^2) TLE
    //     for (int r = BId; r < N; r++)
    //     {
    //         if ((r - l) % 2 == 0)
    //         {
    //             int higher = 0;
    //             int lower = 0;
    //             for (int i = l; i <= r; i++)
    //             {

    //                 if (arr[i] == B)
    //                 {
    //                     continue;
    //                 }
    //                 else if (arr[i] > B)
    //                 {
    //                     higher++;
    //                 }
    //                 else
    //                 {
    //                     lower++;
    //                 }
    //             }

    //             if (higher - lower == 0)
    //             {
    //                 count++;
    //             }
    //         }
    //     }
    // }
    // cout << count << endl;

    // for (int l = BId; l >= 0; l--)
    // { // O(N^2 logN) TLE
    //     for (int r = BId; r < N; r++)
    //     {
    //         if ((r - l) % 2 == 0)
    //         {
    //             vector<int> subseq;
    //             for (int i = l; i <= r; i++)
    //             {
    //                 subseq.push_back(arr[i]);
    //             }
    //             sort(subseq.begin(), subseq.end());

    //             if (subseq[subseq.size() / 2] == B)
    //             {
    //                 count++;
    //             }
    //         }
    //     }
    // }
    // cout << count << endl;
}
