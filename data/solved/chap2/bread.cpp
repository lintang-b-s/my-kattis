#include <bits/stdc++.h>

using namespace std;

/*
https://open.kattis.com/problems/bread?tab=metadata

michael allowed operation:
(a,b,c) -> (c,a,b)

which is two swaps
swap(a,c) -> (c,b,a)
swap(b,a) -> (c,a,b)

this operation is even permutation

even permutation * any number of operations = even permutation

check if inversion count from unsorted to boss sorted = even

i use merge sort for counting  the inversion count

how to count inversion count from unsorted to boss sorted array?
example A=[1,3,4,2] (unsorted)
S = [4,3,2,1] (sorted)


P = [3, 2, 1, 0] (position of each number 1 to N in S)
or Pmap = [1:3, 2: 2, 3: 1, 4: 0]

we need to map A to S coordinate:
AS = [ Pmap[A[i]] ] for i=0,...,N-1

AS = [3, 1, 0, 2]

if we sort AS
AS = [0,1,2,3]

as Pmap is map from idx of array S to S[idx]
then S = S[AS[i]], for i=0,...,N-1

so we need to count inversion count of (sorting asceding) array AS (using modified merge sort)

*/

int merge(vector<int> &arr, int l, int mid, int r)
{
    int n1 = mid - l + 1;
    int n2 = r - mid;
    vector<int> left(n1), right(n2);

    for (int i = 0; i < n1; i++)
    {
        left[i] = arr[i + l];
    }

    for (int i = 0; i < n2; i++)
    {
        right[i] = arr[i + mid + 1];
    }

    int inversionCount = 0;

    int leftid = 0;
    int rightid = 0;
    int i = l;
    while (leftid < n1 && rightid < n2)
    {
        if (left[leftid] < right[rightid])
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
int mergeSort(vector<int> &arr, int l, int r)
{
    if (l >= r)
    {
        return 0;
    }
    int mid = l + (r - l) / 2;

    int icleft = mergeSort(arr, l, mid);      // sort [l, mid]  T(N/2)
    int icright = mergeSort(arr, mid + 1, r); // sort [mid+1,r] T(N/2)
    int icMerge = merge(arr, l, mid, r);      // O(N)
    return icleft + icright + icMerge;
}

int main()
{
    int n;
    cin >> n;

    vector<int> unsorted(0);
    vector<int> sortedBoss(0);

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        unsorted.push_back(a);
    }

    for (int i = 0; i < n; i++)
    {
        int a;
        cin >> a;
        sortedBoss.push_back(a);
    }

    unordered_map<int, int> Pmap;
    for (int i = 0; i < sortedBoss.size(); i++)
    {
        Pmap[sortedBoss[i]] = i;
    }

    vector<int> unsortedSCoord; // unsorted in sorted coordinate
    for (int i = 0; i < unsorted.size(); i++)
    {
        unsortedSCoord.push_back(Pmap[unsorted[i]]);
    }

    int inversionCount = mergeSort(unsortedSCoord, 0, unsortedSCoord.size() - 1); // worst case T=  2T(n/2) + O(n) = O(nlogn)
    
    if (inversionCount % 2 == 0)
    {
        cout << "Possible";
    }
    else
    {
        cout << "Impossible";
    }
}