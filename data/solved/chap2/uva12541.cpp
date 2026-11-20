#include <bits/stdc++.h>
using namespace std;

struct person
{
    string name;
    int day, month, year;
};

int main()
{

    vector<person> arr(0);
    int n;
    cin >> n;
    auto comp = [](person &a, person &b)
    {
        if (a.year == b.year)
        {
            if (a.month == b.month)
            {
                return a.day < b.day;
            }

            return a.month < b.month;
        }
        else
        {
            return a.year < b.year;
        }
    };

    for (int i = 0; i < n; i++)
    {
        person p;
        cin >> p.name >> p.day >> p.month >> p.year;
        arr.push_back(p);
        sort(arr.begin(), arr.end(), comp);
    }

    cout << arr[arr.size() - 1].name << endl;
    cout << arr[0].name << endl;
}