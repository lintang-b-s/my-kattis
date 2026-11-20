#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/foosball?tab=metadata

int main()
{

    int n;
    cin >> n;

    map<string, int> playerArrivalAtTable;

    deque<string> timPutih, timIreng, timPengganti;
    // front = offense, back = defense (buat pemain utama)
    // tim pengganti.front() (yang paling cepat jadi pemain utama)

    for (int i = 0; i < n; i++)
    { // O(n)
        string nama;
        cin >> nama;
        if (i == 0 || i == 2)
        {
            timPutih.push_back(nama);
        }
        else if (i == 1 || i == 3)
        {
            timIreng.push_back(nama);
        }
        else
        {
            timPengganti.push_back(nama);
        }
        playerArrivalAtTable[nama] = -1;
    }

    cin.ignore();

    string line;
    getline(cin, line);

    struct dinasti
    {
        char team;
        pair<string, string> anggota;
        int points;
    };
    vector<dinasti> leaderBoard(0);

    int maxscore = 1;
    for (int i = 0; i < line.size(); i++)
    {// O(m), jumlah points foosball

        char pemenang = line[i];
        playerArrivalAtTable[timPengganti.front()] = i; // When displaying a team, names should be displayed in the order in which the players arrived at the table for that team. dengan kata lain: urutan nama sesuai dengan urutan pemain pengganti menjadi pemain utama

        if (pemenang == 'W')
        {

            dinasti *prevWinner = nullptr;
            if (!leaderBoard.empty())
            {
                prevWinner = &leaderBoard.back();
            }
            if (prevWinner && prevWinner->team == 'W')
            {
                prevWinner->points++;
                maxscore = max(prevWinner->points, maxscore);
            }
            else
            {
                if (playerArrivalAtTable[timPutih[0]] > playerArrivalAtTable[timPutih[1]])
                {
                    dinasti d;
                    d.anggota = {timPutih[1], timPutih[0]};
                    d.team = 'W';
                    d.points = 1;
                    leaderBoard.push_back(d);
                }
                else
                {
                    dinasti d;
                    d.anggota = {timPutih[0], timPutih[1]};
                    d.team = 'W';
                    d.points = 1;
                    leaderBoard.push_back(d);
                }
            }

            swap(timPutih[0], timPutih[1]);

            // tim hytam rotasi pemain
            string oldIrengPelindung = timIreng.back(); // Old BD
            timIreng.pop_back();

            string pemainPengganti = timPengganti.front();
            timPengganti.pop_front();

            timIreng.push_front(pemainPengganti);
            timPengganti.push_back(oldIrengPelindung);
        }
        else
        {
            dinasti *prevWinner = nullptr;
            if (!leaderBoard.empty())
            {
                prevWinner = &leaderBoard.back();
            }
            if (prevWinner && prevWinner->team == 'B')
            {
                prevWinner->points++;
                maxscore = max(prevWinner->points, maxscore);
            }
            else
            {
                if (playerArrivalAtTable[timIreng[0]] > playerArrivalAtTable[timIreng[1]])
                {
                    dinasti d;
                    d.anggota = {timIreng[1], timIreng[0]};
                    d.team = 'B';
                    d.points = 1;
                    leaderBoard.push_back(d);
                }
                else
                {
                    dinasti d;
                    d.anggota = {timIreng[0], timIreng[1]};
                    d.team = 'B';
                    d.points = 1;
                    leaderBoard.push_back(d);
                }
            }

            // rotasi pemain
            swap(timIreng[0], timIreng[1]);

            // tim putih rotasi pemain
            string oldPutihPelindung = timPutih.back();
            timPutih.pop_back();

            string pemainPengganti = timPengganti.front();
            timPengganti.pop_front();

            timPutih.push_front(pemainPengganti);
            timPengganti.push_back(oldPutihPelindung);
        }
    }

    for (auto d : leaderBoard)
    {
        if (d.points == maxscore)
        {
            cout << d.anggota.first << " " << d.anggota.second << endl;
        }
    }

    return 0;
}

// WA bukan di sample input
// int main()
// {

//     int n;
//     cin >> n;

//     deque<string> timPutih, timIreng, timPengganti;
//     // front = offense, back = defense (buat pemain utama)
//     // tim pengganti.front() (yang paling cepat jadi pemain utama)

//     for (int i = 0; i < n; i++)
//     {
//         string nama;
//         cin >> nama;
//         if (i == 0 || i == 2)
//         {
//             timPutih.push_back(nama);
//         }
//         else if (i == 1 || i == 3)
//         {
//             timIreng.push_back(nama);
//         }
//         else
//         {
//             timPengganti.push_back(nama);
//         }
//     }

//     cin.ignore();

//     string line;
//     getline(cin, line);

//     set<pair<string, string>> pasangan;
//     string pemainPutihSatu = timPutih[0], pemainPutihDua = timPutih[1];
//     string pemainHitamSatu = timIreng[0], pemainHitamDua = timIreng[1];

//     pasangan.insert({pemainPutihSatu, pemainPutihDua});
//     pasangan.insert({pemainHitamSatu, pemainHitamDua});

//     int winStreakPutih = 0, winStreakHitam = 0;
//     int hitamBestStreak = 0, putihBestStreak = 0;

//     pair<string, string> putihWinner, hitamWinner;

//     for (int i = 0; i < line.size(); i++)
//     {

//         char pemenang = line[i];
//         if (pemenang == 'W')
//         {
//             swap(timPutih[0], timPutih[1]);

//             // tim hytam rotasi pemain
//             swap(timIreng[0], timIreng[1]); // BO<->BD
//             string oldIrengPelindung = timIreng.front();
//             timIreng.pop_front(); // remove old BD

//             string pemainPengganti = timPengganti.front();
//             timPengganti.pop_front();

//             timIreng.push_front(pemainPengganti);
//             timPengganti.push_back(oldIrengPelindung);
//             winStreakPutih++;
//             winStreakHitam = 0;
//         }
//         else
//         {

//             swap(timIreng[0], timIreng[1]);

//             // tim putih rotasi pemain
//             swap(timPutih[0], timPutih[1]); // WO<->WD
//             string oldPutihPelindung = timPutih.front();
//             timPutih.pop_front(); // remove old WD

//             string pemainPengganti = timPengganti.front();
//             timPengganti.pop_front();

//             timPutih.push_front(pemainPengganti);
//             timPengganti.push_back(oldPutihPelindung);
//             winStreakHitam++;
//             winStreakPutih = 0;
//         }

//         string pemainPutihSatu = timPutih[0], pemainPutihDua = timPutih[1];
//         string pemainHitamSatu = timIreng[0], pemainHitamDua = timIreng[1];

//         if (pasangan.find({pemainPutihSatu, pemainPutihDua}) == pasangan.end() &&
//             pasangan.find({pemainPutihDua, pemainPutihSatu}) == pasangan.end())
//         {
//             pasangan.insert({pemainPutihSatu, pemainPutihDua});
//         }

//         if (pasangan.find({pemainHitamSatu, pemainHitamDua}) == pasangan.end() &&
//             pasangan.find({pemainHitamDua, pemainHitamSatu}) == pasangan.end())
//         {
//             pasangan.insert({pemainHitamSatu, pemainHitamDua});
//         }

//         if (winStreakPutih > putihBestStreak)
//         {
//             if (pasangan.find({pemainPutihSatu, pemainPutihDua}) != pasangan.end())
//             {
//                 putihWinner = {pemainPutihSatu, pemainPutihDua};
//             }
//             else
//             {
//                 putihWinner = {pemainPutihDua, pemainPutihSatu};
//             }
//         }
//         else if (winStreakHitam > hitamBestStreak)
//         {
//             if (pasangan.find({pemainHitamSatu, pemainHitamDua}) != pasangan.end())
//             {
//                 hitamWinner = {pemainHitamSatu, pemainHitamDua};
//             }
//             else
//             {
//                 hitamWinner = {pemainHitamDua, pemainHitamSatu};
//             }
//         }
//         putihBestStreak = max(putihBestStreak, winStreakPutih);
//         hitamBestStreak = max(hitamBestStreak, winStreakHitam);
//     }

//     if (putihBestStreak == hitamBestStreak)
//     {
//         cout << putihWinner.first << " " << putihWinner.second << endl;
//         cout << hitamWinner.first << " " << hitamWinner.second << endl;
//     }
//     else if (putihBestStreak > hitamBestStreak)
//     {
//         cout << putihWinner.first << " " << putihWinner.second << endl;
//     }
//     else
//     {
//         cout << hitamWinner.first << " " << hitamWinner.second << endl;
//     }
// }