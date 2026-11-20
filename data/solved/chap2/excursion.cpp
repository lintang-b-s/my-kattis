#include <bits/stdc++.h>
typedef long long ll;

using namespace std;

// https://open.kattis.com/problems/excursion?tab=metadata

ll merge(string &arr, int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - (mid + 1) + 1;
    string left = "", right = "";

    for (int i = 0; i < n1; i++)
    {
        left += arr[l + i];
    }

    for (int i = 0; i < n2; i++)
    {
        right += arr[i + mid + 1];
    }

    int leftid = 0, rightid = 0;
    int i = l;
    ll inversionCount = 0;

    while (leftid < n1 && rightid < n2)
    {
        if (left[leftid] <= right[rightid])
        {
            arr[i++] = left[leftid];
            leftid++;
        }
        else
        {
            arr[i++] = right[rightid];
            rightid++;
            inversionCount += n1 - leftid;
        }
    }

    while (leftid < n1)
    {
        arr[i++] = left[leftid++];
    }

    while (rightid < n2)
    {
        arr[i++] = right[rightid++];
    }

    return inversionCount;
}

// worst case T(n) = 2T(n/2) + O(n)  = O(nlogn)
// case 2 master theorem
ll mergeSort(string &arr, int l, int r)
{
    if (l >= r)
    {
        return 0;
    }

    int mid = l + (r - l) / 2;

    ll leftInversionCount = mergeSort(arr, l, mid);      // [l,mid]
    ll rightInversionCount = mergeSort(arr, mid + 1, r); // [mid+1,r]

    ll inversionCount = merge(arr, l, mid, r); // merge left arr[l,..,mid] and right arr[mid+1,..,r]
    return inversionCount + leftInversionCount + rightInversionCount;
}

int main()
{
    string s;
    cin >> s;
    int n = s.size();

    cout << mergeSort(s, 0, s.size() - 1);
}