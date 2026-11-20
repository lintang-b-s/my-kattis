#include <bits/stdc++.h>
using namespace std;

/*
https://open.kattis.com/problems/restaurant?tab=metadata

urutan piring yang diberikan ke dishwasher harus sama dengan urutan piring yang diberikan oleh waiter


sample input 1:

DROP 100:

pile 2:
------
p .. p      100 piring. top -> bottom = last to first plates yang diberikan waiter. padahal seharusnya first to last kalau mau diberikan satu persatu ke dishwasher
------


s1 = pile 1 size.
ambil piring sebanyak min(s1,m) dari pile 1.
jika s1<m, ambil piring sebanyak s1 dari pile 1 dan pop setiap piring dari pile 2 and taruh ke pile 1:
pile 1:
------
p .. p    100 piring. top->bottom = first-> last (waiter ordering)
------

T

jika s1>=m, ambil piring dari pile 1 sebanyak m & gak perlu MOVE


*/

int main()
{

    stack<int> tumpukanSatu, tumpukanDua;

    while (true)
    {
        int n;
        cin >> n;
        if (n == 0)
        {
            break;
        }

        for (int i = 0; i < n; i++)
        {
            string op;
            cin >> op;

            int m;
            cin >> m;

            if (op == "DROP")
            {
                for (int i = 0; i < m; i++)
                {
                    tumpukanDua.push(1);
                }
                cout << "DROP 2 " << m << endl;
            }
            else
            {
                int jumlahItemTumpukanDua = 0;

                int tumpukanSatuSize = tumpukanSatu.size();
                int ambilPiringTumpukanSatuSize = min(tumpukanSatuSize, m);
                if (ambilPiringTumpukanSatuSize == tumpukanSatuSize)
                {
                    if (ambilPiringTumpukanSatuSize != 0)
                    {
                        for (int i = 0; i < ambilPiringTumpukanSatuSize; i++)
                        { // at most O(M) , M= \sum m yang di DROP
                            tumpukanSatu.pop();
                        }
                        cout << "TAKE 1 " << ambilPiringTumpukanSatuSize << endl;
                        m -= ambilPiringTumpukanSatuSize;
                        if (m == 0)
                        {
                            continue;
                        }
                    }

                    // MOVE 2->1 tumpukanDua.size()
                    while (!tumpukanDua.empty())
                    { // at most O(M) , M= \sum m yang di DROP
                        int lastItemStackTwo = tumpukanDua.top();
                        tumpukanDua.pop();

                        tumpukanSatu.push(lastItemStackTwo);
                        jumlahItemTumpukanDua++;
                    }

                    cout << "MOVE 2->1 " << jumlahItemTumpukanDua << endl;

                    for (int i = 0; i < m; i++)
                    { // O(m)
                        tumpukanSatu.pop();
                    }
                    cout << "TAKE 1 " << m << endl;
                }
                else
                {
                    for (int i = 0; i < ambilPiringTumpukanSatuSize; i++)
                    { // O(m)
                        tumpukanSatu.pop();
                    }
                    cout << "TAKE 1 " << ambilPiringTumpukanSatuSize << endl;
                }
            }
        }
        while (!tumpukanDua.empty())
        {
            tumpukanDua.pop();
        }

        while (!tumpukanSatu.empty())
        {
            tumpukanSatu.pop();
        }
        cout << endl;
    }

    return 0;
}
