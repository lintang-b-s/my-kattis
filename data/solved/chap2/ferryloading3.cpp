

#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/ferryloading3?tab=metadata

int main()
{
    int c;
    cin >> c;

    for (int i = 0; i < c; i++)
    {
        int n, m, t;
        cin >> n >> t >> m;
        vector<queue<pair<int, int>>> queueKapal(2);

        for (int j = 0; j < m; j++)
        {
            int waktuTibaKapal = 0;
            string posisi;
            cin >> waktuTibaKapal >> posisi;
            if (posisi == "left")
            {
                queueKapal[0].push({waktuTibaKapal, j});
            }
            else
            {
                queueKapal[1].push({waktuTibaKapal,j});
            }
        }

        int waktu = 0;
        bool sebelahKosong = false;

        vector<int> ans(m);

        int side = 0;
        while (!queueKapal[0].empty() || !queueKapal[1].empty())
        { // O(m), m= jumlah kapal utk case-i

            int nextLeft = queueKapal[0].empty() ? INT_MAX : queueKapal[0].front().first;
            int nextRight = queueKapal[1].empty() ? INT_MAX : queueKapal[1].front().first;

            int nextKapalArrival = min(nextLeft, nextRight);
            if (nextKapalArrival > waktu && (queueKapal[side].empty() ||
                                             queueKapal[side].front().first > waktu))
            {
                waktu = nextKapalArrival;
            }

            int jumlahJemput = 0;

            while (!queueKapal[side].empty() && waktu >= queueKapal[side].front().first && jumlahJemput < n)
            {

                ans[queueKapal[side].front().second] = waktu + t; // + t waktu buat nyebrang
                jumlahJemput++;
                queueKapal[side].pop();
            }

            waktu += t;
            side ^= 1;
        }

        for (int time : ans)
        {
            cout << time << endl;
        }
        if (i < c - 1)
        {
            cout << endl;
        }
    }

    return 0;
}

// WA bukan di sample input
// #include <bits/stdc++.h>

// using namespace std;

// int main()
// {
//     int c;
//     cin >> c;

//     for (int i = 0; i < c; i++)
//     {
//         int n, m, t;
//         cin >> n >> t >> m;
//         queue<pair<int, string>> queueKapal;

//         for (int j = 0; j < m; j++)
//         {
//             int waktuTibaKapal = 0;
//             string posisi;
//             cin >> waktuTibaKapal >> posisi;

//             queueKapal.push({waktuTibaKapal, posisi});
//         }

//         int waktu = 0;

//         bool left = true;
//         while (!queueKapal.empty())
//         {
//             if (left)
//             {
//                 auto kapalTerlama = queueKapal.front();
//                 int jumlahJemput = 0;
//                 while (waktu >= kapalTerlama.first &&
//                        kapalTerlama.second == "left" && jumlahJemput < n)
//                 {
//                     jumlahJemput++;
//                     queueKapal.pop();
//                     if (queueKapal.empty())
//                     {
//                         break;
//                     }
//                     kapalTerlama = queueKapal.front();
//                 }

//                 if (jumlahJemput == 0 && kapalTerlama.first > waktu)
//                 {

//                     waktu = kapalTerlama.first;

//                     if (kapalTerlama.second == "left")
//                     {
//                         continue;
//                     }
//                 }

//                 waktu += t;
//                 for (int k = 0; k < jumlahJemput; k++)
//                 {
//                     cout << waktu << endl;
//                 }
//                 left = !left;
//             }
//             else
//             {
//                 auto kapalTerlama = queueKapal.front();
//                 int jumlahJemput = 0;
//                 while (waktu >= kapalTerlama.first &&
//                        kapalTerlama.second == "right" && jumlahJemput < n)
//                 {
//                     jumlahJemput++;
//                     queueKapal.pop();
//                     if (queueKapal.empty())
//                     {
//                         break;
//                     }
//                     kapalTerlama = queueKapal.front();
//                 }

//                 if (jumlahJemput == 0 && kapalTerlama.first > waktu)
//                 {

//                     waktu = kapalTerlama.first;

//                     if (kapalTerlama.second == "right")
//                     {
//                         continue;
//                     }
//                 }

//                 waktu += t;
//                 for (int k = 0; k < jumlahJemput; k++)
//                 {
//                     cout << waktu << endl;
//                 }
//                 left = !left;
//             }
//         }
//         if (i < c - 1)
//         {
//             cout << endl;
//         }
//     }

//     return 0;
// }
