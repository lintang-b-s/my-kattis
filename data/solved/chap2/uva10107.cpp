#include <bits/stdc++.h>
using namespace std;
#include <random>
int getRandom(int low, int high)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(low, high);

    return dist(gen);
}

void quickSort(vector<int> &arr, int low, int high)
{
    if (low >= high)
    {
        return;
    }

    int p = getRandom(low, high);
    swap(arr[p], arr[high]);

    int i = low - 1;
    int j = low;

    for (; j < high; j++)
    {
        if (arr[j] < arr[high])
        {
            i++;
            swap(arr[j], arr[i]);
        }
    }

    swap(arr[i + 1], arr[high]);

    quickSort(arr, low, i);
    quickSort(arr, i + 2, high);
}

void sorting(vector<int> &arr)
{
    quickSort(arr, 0, arr.size() - 1);
}

int main()
{
    random_device rd;
    mt19937 gen(rd());
    int q;
    vector<int> arr(0);
    while (cin >> q)
    {
        arr.push_back(q);
        // sorting(arr);// O(NlogN)
        sort(arr.begin(), arr.end());
        if (arr.size() % 2 == 1)
        {
            int mid = arr.size() / 2;
            cout << arr[mid] << endl;
        }
        else
        {

            int mid = arr.size() / 2;
            cout << (arr[mid] + arr[mid - 1]) / 2 << endl;
        }
    }
}