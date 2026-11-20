#include <bits/stdc++.h>

// https://open.kattis.com/problems/sidewayssorting?tab=metadata
using namespace std;
int main()
{

    int r, c;

    auto comp = [](string a, string b)
    {
        transform(a.begin(), a.end(), a.begin(), ::tolower);
        transform(b.begin(), b.end(), b.begin(), ::tolower);

        return a < b;
    };
    while (cin >> r >> c)
    {
        if (r == 0 and c == 0)
        {
            break;
        }

        vector<vector<char>> arr(r, vector<char>(c));

        for (int i = 0; i < r; i++)
        {
            string row;
            cin >> row;
            for (int j = 0; j < c; j++)
            {
                arr[i][j] = row[j];
            }
        }

        vector<string> columns(c);
        for (int j = 0; j < c; j++)
        {

            string col = "";
            for (int i = 0; i < r; i++)
            {
                col += arr[i][j];
            }
            columns[j] = col;
        }

        stable_sort(columns.begin(), columns.end(), comp);

        for (int j = 0; j < c; j++)
        {
            string col = columns[j];
            for (int i = 0; i < r; i++)
            {
                arr[i][j] = col[i];
            }
        }

        for (int i = 0; i < r; i++)
        {
            for (int j = 0; j < c; j++)
            {
                cout << arr[i][j];
            }

            cout << endl;
        }

        cout << endl;
    }
    return 0;
}