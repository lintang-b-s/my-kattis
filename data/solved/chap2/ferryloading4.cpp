#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/ferryloading4

int main()
{

    int c;
    cin >> c;
    for (int i = 0; i < c; i++)
    {

        int l, m;
        cin >> l >> m;

        queue<int> kapalLeft, kapalRight;

        for (int j = 0; j < m; j++)
        { // O(m)
            int carLength;
            string carBank;

            cin >> carLength >> carBank;
            if (carBank == "left")
            {
                kapalLeft.push(carLength);
            }
            else
            {
                kapalRight.push(carLength);
            }
        }

        int side = 0;
        int jumlahNyebrang = 0;
        while (!kapalLeft.empty() || !kapalRight.empty())
        { // O(m)
            int currentDeckSize = l * 100;

            if (!side)
            {
                while (!kapalLeft.empty() && kapalLeft.front() <= currentDeckSize)
                {
                    currentDeckSize -= kapalLeft.front();
                    kapalLeft.pop();
                }
            }
            else
            {
                while (!kapalRight.empty() && kapalRight.front() <= currentDeckSize)
                {
                    currentDeckSize -= kapalRight.front();
                    kapalRight.pop();
                }
            }

            jumlahNyebrang++;
            side ^= 1;
        }

        cout << jumlahNyebrang << endl;
    }

    return 0;
}