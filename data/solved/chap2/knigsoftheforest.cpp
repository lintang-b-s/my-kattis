#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/knigsoftheforest/statement-pdf

// cuma simulasi pake max heap

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);

    int karlAlgtav = 0;

    int k, n;
    cin >> k >> n;

    int year, strength;
    cin >> year >> strength;
    karlAlgtav = strength;

    vector<vector<int>> rusaRusa(n, vector<int>(0));

    rusaRusa[year - 2011].push_back(strength);

    for (int i = 0; i < n + k - 2; i++)
    {
        cin >> year >> strength;
        rusaRusa[year - 2011].push_back(strength);
    }
    priority_queue<int> pq;

    bool karAlgtavMenang = false;
    int tahunKarlAlgatavMenang = 2011;
    for (int i = 0; i < n; i++)
    { // O(n log(n+k-2))
        for (auto kekuatan : rusaRusa[i])
        {
            pq.push(kekuatan);
        }

        int rusaAlfaTahunIni = pq.top();
        pq.pop();
        if (rusaAlfaTahunIni == karlAlgtav)
        {
            karAlgtavMenang = true;
            tahunKarlAlgatavMenang += i;
            break;
        }
    }

    if (karAlgtavMenang)
    {
        cout << tahunKarlAlgatavMenang << endl;
    }
    else
    {
        cout << "unknown" << endl;
    }
}