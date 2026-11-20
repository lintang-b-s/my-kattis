#include <bits/stdc++.h>
using namespace std;
// https://open.kattis.com/problems/mjehuric?tab=metadata
void printArr(vector<int> arr)
{
    for (int i = 0; i < arr.size(); i++)
    {
        cout << arr[i] << " ";
    }
    cout << endl;
}

using namespace std;
int main()
{

    int digit;
    vector<int> arr;
    for (int i = 0; i < 5; i++)
    {
        cin >> digit;
        arr.push_back(digit);
    }

    // O(N^2) bubble sort
    for (int i = arr.size() - 1; i >= 0; i--)
    {
        for (int j = 0; j <= i - 1; j++)
        {
            if (arr[j] > arr[j + 1])
            {
                swap(arr[j], arr[j + 1]);
                // print the array
                printArr(arr);
            }
        }
    }
}