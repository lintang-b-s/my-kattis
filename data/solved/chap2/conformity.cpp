#include <bits/stdc++.h>

using namespace std;

typedef unsigned long long ll;

int main()
{
    cin.tie(NULL);
    cout.tie(NULL);
    int n;
    cin >> n;
    cin.ignore();

    unordered_map<ll, int> popularitasKelas;
    for (int i = 0; i < n; i++)
    {
        string line;
        getline(cin, line);

        istringstream ss(line);

        string angka;

        vector<ll> courseComb;
        while (getline(ss, angka, ' '))
        {
            int num = stoi(angka);
            courseComb.push_back(num);
        }
        sort(courseComb.begin(), courseComb.end());

        ll courseCombKey = 0;
        for (int j = 0; j < courseComb.size(); j++)
        {
            courseCombKey |= courseComb[j] << (9 * j);
        }
        popularitasKelas[courseCombKey]++;
    }

    string kelasTerpopuler = "";
    int maxStud = -1;
    int totalStudTakePopularCourseComb = 0;
    for (auto [kelas, jumlahStudents] : popularitasKelas)
    {
        if (jumlahStudents > maxStud)
        {
            maxStud = jumlahStudents;
        }
    }

    for (auto [kelas, jumlahStudents] : popularitasKelas)
    {
        if (jumlahStudents == maxStud)
        {
            totalStudTakePopularCourseComb += jumlahStudents;
        }
    }
    cout << totalStudTakePopularCourseComb << endl;
}