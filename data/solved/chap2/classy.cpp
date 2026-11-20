#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/classy

struct manungsa
{
    string jeneng;
    int biji;
};

int gawekkeAngkaNgawur(int min, int max)
{
    return min + (rand() % (max - min + 1));
}

vector<manungsa> ngurutkeCepetlanStabil(vector<manungsa> uwongs)
{
    if (uwongs.size() <= 1)
    {
        return uwongs;
    }

    int pivot = gawekkeAngkaNgawur(0, uwongs.size() - 1);

    vector<manungsa> uwongUwongGede;
    vector<manungsa> uwongCiliks;

    for (int i = 0; i < uwongs.size(); i++)
    {
        if (i == pivot)
        {
            continue;
        }
        if (uwongs[i].biji > uwongs[pivot].biji)
        {
            uwongUwongGede.push_back(uwongs[i]);
        }
        else if (uwongs[i].biji < uwongs[pivot].biji)
        {
            uwongCiliks.push_back(uwongs[i]);
        }
        else
        {
            if (uwongs[i].jeneng < uwongs[pivot].jeneng)
            {
                uwongUwongGede.push_back(uwongs[i]);
            }
            else
            {
                uwongCiliks.push_back(uwongs[i]);
            }
        }
    }

    vector<manungsa> uwongUwongGedeWisUrut = ngurutkeCepetlanStabil(uwongUwongGede);
    vector<manungsa> uwongCiliksWisUrut = ngurutkeCepetlanStabil(uwongCiliks);

    vector<manungsa> jawaban;

    for (int i = 0; i < uwongUwongGedeWisUrut.size(); i++)
    {
        jawaban.push_back(uwongUwongGedeWisUrut[i]);
    }
    jawaban.push_back(uwongs[pivot]);

    for (int i = 0; i < uwongCiliksWisUrut.size(); i++)
    {
        jawaban.push_back(uwongCiliksWisUrut[i]);
    }

    return jawaban;
}

int main()
{
    srand(time(0));
    int T;
    cin >> T;
    for (int i = 0; i < T; i++)
    {
        int n;
        cin >> n;

        vector<manungsa> uwongs;
        for (int j = 0; j < n; j++)
        {
            string jeneng, kastaneUwong, rapenting;
            cin >> jeneng >> kastaneUwong >> rapenting;
            manungsa uwong;
            uwong.jeneng = jeneng.substr(0, jeneng.size() - 1);

            vector<int> kastaRenking;

            istringstream ss(kastaneUwong);
            string kasta;
            while (getline(ss, kasta, '-'))
            {
                if (kasta == "middle")
                {
                    kastaRenking.push_back(1);
                }
                else if (kasta == "lower")
                {
                    kastaRenking.push_back(0);
                }
                else
                {
                    kastaRenking.push_back(2);
                }
            }

            int renking = 0;
            reverse(kastaRenking.begin(), kastaRenking.end());
            for (int k = 0; k < 10; k++)
            {
                if (k < kastaRenking.size())
                {
                    renking = renking * 3 + kastaRenking[k];
                }
                else
                {
                    renking = renking * 3 + 1;
                }
            }

            uwong.biji = renking;
            uwongs.push_back(uwong);
        }

        vector<manungsa> uwongsWisUrut = ngurutkeCepetlanStabil(uwongs); // expected run time O(nlogn), worst case O(n^2) space O(n)

        for (int i = 0; i < uwongsWisUrut.size(); i++)
        {
            cout << uwongsWisUrut[i].jeneng << endl;
        }
        cout << "==============================" << endl;
    }
}