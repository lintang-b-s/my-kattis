#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

/*
https://open.kattis.com/problems/froshweek

just an inversion count (number of swap/comparison in sorting algorithm, like bubble sort)

use modified merge sort

when merge count the swap:
if right element large than all current left element increment the inversion by left.size()
*/

ll merge(vector<ll> &arr, int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    vector<ll> left(n1), right(n2);

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[i + l];
    }

    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[i + mid + 1];
    }

    ll inversionCount = 0;

    int leftid = 0;
    int rightid = 0;
    int i = l;
    while (leftid < n1 && rightid < n2)
    {
        if (left[leftid] <= right[rightid])
        {
            arr[i] = left[leftid];
            leftid++;
        }
        else
        {
            arr[i] = right[rightid];
            rightid++;

            inversionCount += n1 - leftid;
        }
        i++;
    }

    if (leftid < n1)
    {
        while (leftid < n1)
        {
            arr[i] = left[leftid];
            leftid++;
            i++;
        }
    }

    if (rightid < n2)
    {
        while (rightid < n2)
        {
            arr[i] = right[rightid];
            rightid++;
            i++;
        }
    }

    return inversionCount;
}

// worst case T=  2T(n/2) + O(n) = O(nlogn)
// case 2 master theorem
ll mergeSort(vector<ll> &arr, int l, int r)
{
    if (l >= r)
    {
        return 0;
    }
    int mid = l + (r - l) / 2;

    ll icleft = mergeSort(arr, l, mid);      // sort [l, mid]  T(N/2)
    ll icright = mergeSort(arr, mid + 1, r); // sort [mid+1,r] T(N/2)
    ll icMerge = merge(arr, l, mid, r);      // O(N)
    return icleft + icright + icMerge;
}

int main()
{
    int n;
    cin >> n;

    vector<ll> arr;

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        arr.push_back(a);
    }

    cout << mergeSort(arr, 0, arr.size() - 1); // worst case O(nlogn)
}