#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/integerlists?tab=metadata
int main()
{
    int t;
    cin >> t;
    for (int i = 0; i < t; i++)
    {
        string perintah;
        cin >> perintah;
        int n;
        cin >> n;
        cin.ignore();

        deque<int> daftarBilanganBulat;

        int num = 0;
        bool inNumber = false;
        string line;
        getline(cin, line);

        for (int j = 0; j < line.size(); j++)
        {
            char a = line[j];
            if (a == '[' or a == ']' or a == ',')
            {
                if (inNumber)
                {
                    daftarBilanganBulat.push_back(num);
                    num = 0;
                    inNumber = false;
                }
                continue;
            }
            else
            {
                num = num * 10 + a - '0';
                inNumber = true;
            }
        }

        bool kebalik = false;
        bool ngaco = false;

        for (int j = 0; j < perintah.size(); j++)
        { // O(length(p)), p = BAPC program
            if (perintah[j] == 'R')
            {
                kebalik = !kebalik;
            }
            else if (perintah[j] == 'D' and kebalik)
            {
                if (daftarBilanganBulat.size() == 0)
                {
                    ngaco = true;
                    break;
                }
                daftarBilanganBulat.pop_back();
            }
            else if (perintah[j] == 'D' and !kebalik)
            {
                if (daftarBilanganBulat.size() == 0)
                {
                    ngaco = true;
                    break;
                }
                daftarBilanganBulat.pop_front();
            }
        }

        if (ngaco)
        {
            cout << "error" << endl;
            continue;
        }
        cout << "[";
        int newN = daftarBilanganBulat.size();
        for (int j = 0; j < newN; j++)
        { // O(n), n jumlah integer di list
            if (kebalik)
            {
                cout << daftarBilanganBulat.back();
                daftarBilanganBulat.pop_back();
            }
            else
            {
                cout << daftarBilanganBulat.front();
                daftarBilanganBulat.pop_front();
            }

            if (j < newN - 1)
            {
                cout << ",";
            }
        }
        cout << "]" << endl;
    }
}