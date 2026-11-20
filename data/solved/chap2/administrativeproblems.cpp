#include <bits/stdc++.h>
using namespace std;

typedef unsigned long long ll;

// https://open.kattis.com/problems/administrativeproblems?tab=metadata

int main()
{
    int t;
    cin >> t;

    while (t--)
    {
        map<string, vector<int>> katalogMobil;
        map<string, string> spyCurrentCar;
        unordered_set<string> mataMataInkonsisten;

        map<string, ll> billingMataMata;
        // 0=pickup, 1=return, 2=accident
        int n, m;
        cin >> n >> m;

        for (int i = 0; i < n; i++)
        { // O(NlogN)
            string car = "";
            cin >> car;
            int catalogPrice = 0;
            int pickupPrice = 0;
            int drivingCost = 0;

            cin >> catalogPrice >> pickupPrice >> drivingCost;
            vector<int> mobilepricy;
            mobilepricy.push_back(catalogPrice);
            mobilepricy.push_back(pickupPrice);
            mobilepricy.push_back(drivingCost);

            katalogMobil[car] = mobilepricy; // log(N), N=jumlah mobil
        }

        for (int i = 0; i < m; i++)
        { // O(M (logN + log S)), M=jumlah events, S = jumlah spies
            int time = 0, keparahanAccident = 0, kilometer = 0;
            string namaSpy = "", tipeEvent = "";

            cin >> time >> namaSpy >> tipeEvent;

            if (billingMataMata.find(namaSpy) == billingMataMata.end())
            {
                billingMataMata[namaSpy] = 0;
            }

            if (tipeEvent == "p")
            {
                string tipeMobil = "";
                cin >> tipeMobil;

                if (mataMataInkonsisten.find(namaSpy) != mataMataInkonsisten.end())
                {
                    continue;
                }

                if (spyCurrentCar[namaSpy] != "")
                {

                    mataMataInkonsisten.insert(namaSpy);
                    continue;
                }

                spyCurrentCar[namaSpy] = tipeMobil;

                auto mobilHarga = katalogMobil[tipeMobil];
                billingMataMata[namaSpy] += mobilHarga[1];
            }
            else if (tipeEvent == "r")
            {
                cin >> kilometer;

                if (mataMataInkonsisten.find(namaSpy) != mataMataInkonsisten.end())
                {
                    continue;
                }

                if (spyCurrentCar[namaSpy] == "")
                {

                    mataMataInkonsisten.insert(namaSpy);
                    continue;
                }

                string mobilMataMata = spyCurrentCar[namaSpy];

                billingMataMata[namaSpy] += kilometer * katalogMobil[mobilMataMata][2];

                spyCurrentCar[namaSpy] = "";
            }
            else if (tipeEvent == "a")
            {
                cin >> keparahanAccident;

                if (mataMataInkonsisten.find(namaSpy) != mataMataInkonsisten.end())
                {
                    continue;
                }

                if (spyCurrentCar[namaSpy] == "")
                {
                    mataMataInkonsisten.insert(namaSpy);
                    continue;
                }

                string mobilMataMata = spyCurrentCar[namaSpy];

                ll biayaAccident = keparahanAccident * katalogMobil[mobilMataMata][0];
                billingMataMata[namaSpy] += ceil((double)biayaAccident / 100);
            }
        }

        for (auto [namaSpy, carRent] : spyCurrentCar)
        {
            if (carRent != "")
            {
                mataMataInkonsisten.insert(namaSpy);
            }
        }

        for (auto [namaSpy, billing] : billingMataMata)
        {
            if (mataMataInkonsisten.find(namaSpy) == mataMataInkonsisten.end())
            {
                cout << namaSpy << " " << billing << endl;
            }
            else
            {
                cout << namaSpy << " " << "INCONSISTENT" << endl;
            }
        }
    }
}