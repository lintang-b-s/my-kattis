#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/contests/robjga/problems/height?tab=metadata

// O(N^2)
int insertionSort(vector<int> arr)
{
    int cnt = 0;
    for (int i = 1; i < arr.size(); i++)
    {
        int key = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > key)
        {
            arr[j + 1] = arr[j];
            cnt++;
            j = j - 1;
        }
        arr[j + 1] = key;
    }

    return cnt;
}
int main()
{

    int P;
    cin >> P;

    for (int i = 0; i < P; i++)
    {
        int K;
        cin >> K;
        vector<int> arr;

        int digit;
        for (int j = 0; j < 20; j++)
        {
            cin >> digit;
            arr.push_back(digit);
        }

        cout << i + 1 << " " << insertionSort(arr) << endl;
    }
}