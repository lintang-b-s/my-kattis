#include <bits/stdc++.h>
using namespace std;

int main()
{
    string line;
    vector<vector<string>> mat(8, vector<string>(8));
    vector<pair<int, int>> queens;
    int n = 0;
    for (int i = 0; i < 8; i++)
    {
        getline(cin, line);

        int j = 0;
        for (auto el : line)
        {
            mat[n][j] = el;
            if (el == '*')
            {
                queens.push_back({n, j});
            }
            j++;
        }
        n++;
    }

    if (queens.size() != 8)
    {
        cout << "invalid" << endl;
        return 0;
    }

    bool salah = false;
    for (int q = 0; q < queens.size(); q++)
    {
        // T(q) <= c*q = O(q). c=8*8
        auto queen = queens[q];
        // cek kanan
        for (int j = queen.second + 1; j < 8; j++)
        {
            if (mat[queen.first][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
        }

        if (salah)
        {
            break;
        }

        // cek kiri
        for (int j = queen.second - 1; j >= 0; j--)
        {
            if (mat[queen.first][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
        }

        if (salah)
        {
            break;
        }

        // cek atas
        for (int i = queen.first - 1; i >= 0; i--)
        {
            if (mat[i][queen.second] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
        }

        if (salah)
        {
            break;
        }

        // cek bawah
        for (int i = queen.first + 1; i < 8; i++)
        {
            if (mat[i][queen.second] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
        }

        if (salah)
        {
            break;
        }

        int j = queen.second + 1;
        // cek diagonally atas right
        for (int i = queen.first - 1; i >= 0; i--)
        {
            if (j >= 8)
            {
                break;
            }
            if (mat[i][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
            j++;
        }

        if (salah)
        {
            break;
        }

        j = queen.second - 1;
        // cek diagonally atas kiri
        for (int i = queen.first - 1; i >= 0; i--)
        {
            if (j < 0)
            {
                break;
            }
            if (mat[i][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
            j--;
        }

        if (salah)
        {
            break;
        }

        j = queen.second + 1;
        // cek bawah kanan
        for (int i = queen.first + 1; i < 8; i++)
        {
            if (j >= 8)
            {
                break;
            }

            if (mat[i][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
            j++;
        }

        if (salah)
        {
            break;
        }

        j = queen.second - 1;
        // cek bawah kanan
        for (int i = queen.first + 1; i < 8; i++)
        {
            if (j < 0)
            {
                break;
            }
            if (mat[i][j] == "*")
            {
                cout << "invalid" << endl;
                salah = true;
                break;
            }
            j--;
        }

        if (salah)
        {
            break;
        }
    }

    if (!salah)
    {
        cout << "valid" << endl;
    }
}