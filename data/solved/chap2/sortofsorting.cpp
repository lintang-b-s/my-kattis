#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/sortofsorting?tab=metadata

int generaterand(int min, int max)
{
    int rr = rand();
    return min + (rr % (max - min + 1)); // [min,max]
}

int partition(vector<string> &arr, int l, int r)
{

    int pivot = generaterand(l, r);
    swap(arr[pivot], arr[r]);

    int i = l - 1;
    for (int j = l; j < r; j++)
    {
        if (arr[j].substr(0, 2) < arr[r].substr(0, 2))
        {
            i++;
            swap(arr[i], arr[j]);
        }
    }

    i++;
    swap(arr[i], arr[r]);
    return i;
}

// expected runtime O(N log N)
// worst case O(N^2)
vector<string> quickSortStable(vector<string> &arr)
{
    if (arr.size() <= 1)
    {
        return arr;
    }

    int pivot = generaterand(0, arr.size() - 1);

    vector<string> small;
    vector<string> large;

    for (int j = 0; j < arr.size(); j++)
    {
        if (j == pivot)
        {
            continue;
        }
        if (arr[j].substr(0, 2) < arr[pivot].substr(0, 2))
        {
            small.push_back(arr[j]);
        }
        else if (arr[j].substr(0, 2) > arr[pivot].substr(0, 2))
        {
            large.push_back(arr[j]);
        }
        else
        {
            if (j < pivot)
            {
                small.push_back(arr[j]);
            }
            else
            {
                large.push_back(arr[j]);
            }
        }
    }

    vector<string> sorted1 = quickSortStable(small);
    vector<string> sorted2 = quickSortStable(large);

    vector<string> ans(0);
    for (int i = 0; i < sorted1.size(); i++)
    {
        ans.push_back(sorted1[i]);
    }

    ans.push_back(arr[pivot]);
    
    for (int i = 0; i < sorted2.size(); i++)
    {
        ans.push_back(sorted2[i]);
    }

    return ans;
}

// expected runtime O(N log N)
// worst case O(N^2)
void quickSort(vector<string> &arr, int l, int r)
{
    if (r <= l)
    {
        return;
    }
    int p = partition(arr, l, r);
    quickSort(arr, l, p - 1);
    quickSort(arr, p + 1, r);
}

// worst case O(N^2)
void bubbleSort(vector<string> &arr, int l, int r)
{
    int n = arr.size();
    for (int i = 0; i < n - 1; i++)
    {
        for (int j = n - 1; j > i; j--)
        {
            if (arr[j].substr(0, 2) > arr[i].substr(0, 2))
            {
                swap(arr[j], arr[i]);
            }
        }
    }
}

int main()
{
    srand(time(0));
    int n;
    while (true)
    {
        cin >> n;
        if (n == 0)
        {
            break;
        }
        cout << endl;

        vector<string> arr;
        for (int i = 0; i < n; i++)
        {
            string lastName;
            cin >> lastName;
            arr.push_back(lastName);
        }

        vector<string> ans = quickSortStable(arr);

        for (int i = 0; i < ans.size(); i++)
        {
            cout << ans[i] << endl;
        }
    }

    return 0;
}