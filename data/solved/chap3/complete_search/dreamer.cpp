#include <bits/stdc++.h>
using namespace std;

void permutation(vector<int> arr, int i, vector<vector<int>> &res)
{
    if (i == arr.size())
    {
        res.push_back(arr);
        return;
    }
    for (int j = i; j < arr.size(); j++)
    {
        swap(arr[j], arr[i]);
        permutation(arr, i + 1, res);
        swap(arr[j], arr[i]);
    }
}

vector<int> getDigits(int a, string type)
{
    vector<int> arr;
    while (a)
    {
        arr.push_back(a % 10);
        a /= 10;
    }

    if (type == "year")
    {
        int kurang = 4 - arr.size();
        for (int i = 0; i < kurang; i++)
        {
            arr.push_back(0);
        }
    }
    else if (type == "month" || type == "day")
    {
        int kurang = 2 - arr.size();
        for (int i = 0; i < kurang; i++)
        {
            arr.push_back(0);
        }
    }

    reverse(arr.begin(), arr.end());

    return arr;
}

struct dayt
{
    int day, month, year;
    bool operator==(const dayt &other) const
    {
        return day == other.day && month == other.month && year == other.year;
    }
};

bool isLeapYear(int year)
{
    if (year % 4 == 0)
    {

        if (year % 100 == 0)
        {
            return year % 400 == 0;
        }
        return true;
    }
    return false;
}

int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        int aa, bb, cc;
        cin >> aa >> bb >> cc;
        vector<int> arr;
        auto aaa = getDigits(aa, "day");
        arr.insert(arr.end(), aaa.begin(), aaa.end());
        auto bbb = getDigits(bb, "month");
        arr.insert(arr.end(), bbb.begin(), bbb.end());
        auto ccc = getDigits(cc, "year");
        arr.insert(arr.end(), ccc.begin(), ccc.end());

        vector<vector<int>> res;

        int q = 0;
        permutation(arr, q, res); // 8!

        vector<dayt> days;
        for (int j = 0; j < res.size(); j++)
        {

            int day = 0;
            for (int k = 0; k < 2; k++)
            {
                day *= 10;
                day += res[j][k];
            }

            int month = 0;
            for (int k = 2; k < 4; k++)
            {
                month *= 10;
                month += res[j][k];
            }

            int year = 0;
            for (int k = 4; k < 8; k++)
            {
                year *= 10;
                year += res[j][k];
            }

            if (year >= 2000 && month >= 1 && month <= 12 && day >= 1 && day <= 31)
            {
                if (isLeapYear(year) && month == 2 && day > 29 || (!isLeapYear(year) && month == 2 && day > 28))
                {
                    continue;
                }
                if (day == 31 && (month == 4 || month == 6 || month == 9 || month == 11))
                {
                    continue;
                }

                days.push_back(dayt{day, month, year});
            }
        }

        sort(days.begin(), days.end(), [](dayt a, dayt b)
             {
            if (a.year != b.year) {
                return a.year < b.year;
            }
            if (a.month != b.month) {
                return a.month < b.month;
            }
         return a.day < b.day; });

        if (days.size() == 0)
        {
            cout << 0 << endl;
            continue;
        }
        auto begin = days[0];

        string day = "";
        string month = "";
        if (begin.day < 10)
        {
            day = "0" + to_string(begin.day);
        }
        else
        {
            day = to_string(begin.day);
        }
        if (begin.month < 10)
        {
            month = "0" + to_string(begin.month);
        }
        else
        {
            month = to_string(begin.month);
        }

        days.erase(unique(days.begin(), days.end()), days.end());

        cout << days.size() << " " << day << " " << month << " " << begin.year << endl;
    }
}