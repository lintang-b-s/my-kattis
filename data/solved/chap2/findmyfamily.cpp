#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/findmyfamily?tab=metadata

typedef long long valType;
class SegmentTree
{
private:
    int n;
    vector<valType> A, st, lazy;
    bool minimum;

    int leftChild(int parent)
    {
        // go to left child
        return parent << 1;
    }

    int rightChild(int parent)
    {
        return (parent << 1) + 1;
    }

    valType conquer(valType a, valType b)
    {
        if (a == -1)
        {
            return b;
        }
        if (b == -1)
        {
            return a;
        }
        if (minimum)
        {
            return min(a, b);
        }
        return max(a, b);
    }

    void build(int parent, int L, int R)
    { // O(n)
        if (L == R)
        {
            st[parent] = A[L];
        }
        else
        {
            int mid = (L + R) / 2;
            build(leftChild(parent), L, mid);
            build(rightChild(parent), mid + 1, R);
            st[parent] = conquer(st[leftChild(parent)], st[rightChild(parent)]);
        }
    }

    void propagate(int parent, int L, int R)
    {
        if (lazy[parent] != -1)
        { // parent has a lazy flag
            st[parent] = lazy[parent];

            if (L != R)
            {
                lazy[leftChild(parent)] = lazy[rightChild(parent)] = lazy[parent];
            }
            else
            {
                A[L] = lazy[parent];
            }
            lazy[parent] = -1;
        }
    }

    valType RMQ(int parent, int L, int R, int i, int j)
    { // O(log N)
        propagate(parent, L, R);
        if (i > j)
        {
            return -1;
        }
        if ((i <= L) && (j >= R))
        {
            return st[parent];
        }

        int mid = (L + R) / 2;
        return conquer(RMQ(leftChild(parent), L, mid, i, min(mid, j)),
                       RMQ(rightChild(parent), mid + 1, R, max(i, mid + 1), j));
    }

    void update(int parent, int L, int R, int i, int j, valType val)
    {
        propagate(parent, L, R);

        if (i > j)
        {
            return;
        }
        if ((i <= L) && (j >= R))
        {
            lazy[parent] = val;
            propagate(parent, L, R);
        }
        else
        {
            int mid = (L + R) / 2;
            update(leftChild(parent), L, mid, i, min(mid, j), val);
            update(rightChild(parent), mid + 1, R, max(i, mid + 1), j, val);
            valType leftSubTree = (lazy[leftChild(parent)] != -1) ? lazy[leftChild(parent)] : st[leftChild(parent)];
            valType rightSubTree = (lazy[rightChild(parent)] != -1) ? lazy[rightChild(parent)] : st[rightChild(parent)];
            st[parent] = conquer(leftSubTree, rightSubTree);
        }
    }

public:
    SegmentTree(int size, bool isMinimum) : n(size), A(n), st(4 * n), lazy(4 * n, -1), minimum(isMinimum) {}

    SegmentTree(vector<valType> &initialA, bool isMinimum) : SegmentTree(initialA.size(), isMinimum)
    {
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, valType val)
    {
        update(1, 0, n - 1, i, j, val);
    }

    valType RMQ(int i, int j)
    { // get index of max/min value over arr[i], arr[i+1], ... ,arr[j]
        return RMQ(1, 0, n - 1, i, j);
    }
};

int main()
{
    int k;
    cin >> k;

    int photosNeedToInvestigated = 0;
    vector<int> photos;
    for (int i = 0; i < k; i++)
    { // O(k * n * log n)
        int n;
        cin >> n;

        vector<valType> arr(n), sortedArr(n);
        for (int j = 0; j < n; j++)
        {
            valType a;
            cin >> a;
            arr[j] = a;
            sortedArr[j] = a;
        }

        sort(sortedArr.begin(), sortedArr.end());

        SegmentTree st(arr, false);
        vector<valType> rightMax(n);
        for (int r = n - 1; r >= 0; r--)
        {                                // O(n log n)
            int rMax = st.RMQ(r + 1, n); // O(log n)
            rightMax[r] = rMax;
        }

        vector<valType> lefts(n, INT_MAX);
        SegmentTree stLefts(lefts, true);

        auto getId = [&](valType val)
        {
            return lower_bound(sortedArr.begin(), sortedArr.end(), val) - sortedArr.begin();
        };

        bool found = false;
        for (int l = 0; l < n; l++)
        { // O(n * log n)

            valType curVal = arr[l];
            int newId = getId(curVal); // cooollll, i learn new trick haha
            // new trick: find least value to the left that higher than curVal in O(log n).

            valType leftMin = stLefts.RMQ(newId, n - 1);
            if (leftMin < rightMax[l])
            {
                found = true;
                break;
            }
            stLefts.update(newId, newId, curVal);
        }
        if (found)
        {
            photos.push_back(i + 1);
        }
    }

    cout << photos.size() << endl;
    for (auto photo : photos)
    {
        cout << photo << endl;
    }

    // TLE
    // int photosNeedToInvestigated = 0;
    // vector<int> photos;
    // for (int i = 0; i < k; i++)
    // { // O(k * n^2)
    //     int n;
    //     cin >> n;

    //     vector<valType> arr(n);
    //     for (int j = 0; j < n; j++)
    //     {
    //         valType a;
    //         cin >> a;
    //         arr[j] = a;
    //     }

    //     SegmentTree st(arr, false);
    //     vector<valType> rightMax(n);
    //     for (int r = n - 1; r >= 0; r--)
    //     {                                // O(n log n)
    //         int rMax = st.RMQ(r + 1, n); // O(log n)
    //         rightMax[r] = rMax;
    //     }

    //     bool found = false;
    //     for (int l = 0; l < n; l++)
    //     { // O(n^2)
    //         if (found)
    //         {
    //             break;
    //         }
    //         valType curVal = arr[l];
    //         for (int f = 0; f < l; f++)
    //         {
    //             if (arr[f] > curVal && arr[f] < rightMax[l])
    //             {
    //                 found = true;
    //                 break;
    //             }
    //         }
    //     }
    //     if (found)
    //     {
    //         photos.push_back(i + 1);
    //     }
    // }

    // cout << photos.size() << endl;
    // for (auto photo : photos)
    // {
    //     cout << photo << endl;
    // }

    // cout << photos.size() << endl;
    // for (auto photo : photos)
    // {
    //     cout << photo << endl;
    // }

    // TLE O(k*n^3)
    // int photosNeedToInvestigated = 0;
    // vector<int> photos;
    // for (int i = 0; i < k; i++)
    // { // O(k*n^3)
    //     int n;
    //     cin >> n;

    //     vector<int> arr(n);
    //     for (int j = 0; j < n; j++)
    //     {
    //         int a;
    //         cin >> a;
    //         arr[j] = a;
    //     }

    //     int you = 0;
    //     int bob = -1;
    //     int alice = -1;
    //     bool found = false;

    //     for (int j = 0; j < n; j++)
    //     { // O(n^3)
    //         if (found)
    //         {
    //             break;
    //         }
    //         you = arr[j];
    //         for (int q = 0; q < j; q++)
    //         { // find alice

    //             for (int f = j + 1; f < n; f++)
    //             {

    //                 if (arr[q] > you && arr[f] > you && arr[q] < arr[f])
    //                 {
    //                     alice = arr[q];

    //                     bob = arr[f];
    //                     found = true;
    //                 }
    //             }
    //         }
    //     }

    //     if (found)
    //     {
    //         photosNeedToInvestigated++;

    //         photos.push_back(i + 1);
    //     }
    // }

    // cout << photos.size() << endl;
    // for (auto photo : photos)
    // {
    //     cout << photo << endl;
    // }
}