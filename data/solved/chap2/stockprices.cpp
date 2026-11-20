#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/stockprices?tab=metadata

/*
 */
struct saham
{
    int jumlah;
    int harga;
};

class CompareMin
{
public:
    bool operator()(saham *a, saham *b)
    {
        return a->harga > b->harga;
    }
};

class CompareMax
{
public:
    bool operator()(saham *a, saham *b)
    {
        return a->harga < b->harga;
    }
};

int main()
{

    cin.tie(NULL);
    cout.tie(NULL);

    int cases, n;
    cin >> cases;

    for (int kasus = 0; kasus < cases; kasus++)
    {

        cin >> n;
        priority_queue<saham *, vector<saham *>, CompareMin> hargaJuals;
        priority_queue<saham *, vector<saham *>, CompareMax> hargaBelis;
        int dealPrice = -999;

        for (int i = 0; i < n; i++)
        {
            string cmd;
            cin >> cmd;

            istringstream ss(cmd);
            string apa;

            bool beli = false;
            int jumlahSaham = 0;
            int hargaSaham = 0;
            if (cmd == "buy")
            {
                beli = true;
            }

            cin >> jumlahSaham;
            cin >> cmd;
            cin >> cmd;
            cin >> hargaSaham;

            saham *lembars = new saham{0, 0};
            lembars->harga = hargaSaham;
            lembars->jumlah = jumlahSaham;
            if (beli)
            {
                hargaBelis.push(lembars); 
            }
            else
            {
                hargaJuals.push(lembars);
            }

            bool transaction = false;
            while (!hargaBelis.empty() && !hargaJuals.empty() &&
                   hargaBelis.top()->harga >= hargaJuals.top()->harga)
            { // O(nlogn)
                int minJumlah = min(hargaBelis.top()->jumlah, hargaJuals.top()->jumlah);
                dealPrice = hargaJuals.top()->harga;
                hargaJuals.top()->jumlah -= minJumlah;
                hargaBelis.top()->jumlah -= minJumlah;

                if (hargaBelis.top()->jumlah <= 0)
                {
                    hargaBelis.pop();
                }
                if (hargaJuals.top()->jumlah <= 0)
                {
                    hargaJuals.pop();
                }

                transaction = true;
            }
            if (!hargaJuals.empty())
            {
                cout << hargaJuals.top()->harga << " ";
            }
            else
            {
                cout << "-" << " ";
            }

            if (!hargaBelis.empty())
            {
                cout << hargaBelis.top()->harga << " ";
            }
            else
            {
                cout << "-" << " ";
            }

            if (dealPrice != -999)
            {
                cout << dealPrice << " " << endl;
            }
            else
            {
                cout << "-" << " " << endl;
            }
        }
    }
}