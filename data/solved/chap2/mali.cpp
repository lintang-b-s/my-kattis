#include <bits/stdc++.h>

using namespace std;

/*
https://open.kattis.com/problems/mali?tab=metadata

intuisi:

A= a1,....,an  and a1 < a2 < ... < an
B= b1,....,bn  and b1 < b2 < ... < bn

maximal of ai + bj is minimal when:
max_{1 \leq i \leq n} a[i] + b[n-i-1]

for example:
A = [10, 40, 80, 100]
B = [1, 30, 40, 50]
A[i] + B[n-i-1] = [51, 80, 110, 101]

karena setiap integer <= 100
bisa pake counting sort biar worst case O(n+k)
*/

// O (100 + N)
vector<int> countingSort(vector<int> arr)
{
    vector<int> freq(100);
    int n = arr.size();
    for (int i = 0; i < n; i++)
    {
        freq[arr[i] - 1]++;
    }

    vector<int> res(n);
    // prefix sum
    for (int i = 1; i < 100; i++) // 100 ops
    {
        freq[i] = freq[i - 1] + freq[i];
    }

    for (int i = n - 1; i >= 0; i--) // O(N)
    {
        res[freq[arr[i] - 1] - 1] = arr[i];
        freq[arr[i] - 1]--;
    }

    return res;
}

int findMinMax(vector<int> freqA, vector<int> freqB)
{
    int a = 1, b = 100;
    int minmaxsum = 0;
    while (a <= 100 && b >= 1)
    {
        if (freqA[a] == 0)
        {
            a++;
            continue;
        }
        if (freqB[b] == 0)
        {
            b--;
            continue;
        }

        int k = min(freqA[a], freqB[b]);
        freqA[a] -= k; // skip k equal elements
        freqB[b] -= k;

        minmaxsum = max(minmaxsum, a + b);
    }
    return minmaxsum;
}

int main()
{
    int N;
    cin >> N;
    vector<int> arrA(0);
    vector<int> arrB(0);

    vector<int> freqA(101, 0);
    vector<int> freqB(101, 0);

    for (int i = 0; i < N; i++)
    {
        int a, b;
        cin >> a >> b;
        arrA.push_back(a);
        arrB.push_back(b);

        /*
        TLE
        vector<int> arrASorted = countingSort(arrA);
        vector<int> arrBSorted = countingSort(arrB);
        int n = arrBSorted.size();
        for (int i = 0; i < n; i++)
        {
            minmaxsum = max(minmaxsum, arrASorted[i] + arrBSorted[n - i - 1]);
        }

        */

        freqA[arrA[i]]++;
        freqB[arrB[i]]++;

        int minmaxsum = findMinMax(freqA, freqB);

        cout << minmaxsum << endl;
    }

    return 0;
}