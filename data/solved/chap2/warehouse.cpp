#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/warehouse?tab=metadata
int main()
{
    int t;
    cin >> t;

    struct product
    {
        string nama;
        int jumlah;
    };

    while (t--)
    {

        int n;
        cin >> n;

        unordered_map<string, int> productFreq;
        for (int i = 0; i < n; i++)
        {

            product produk;
            cin >> produk.nama >> produk.jumlah;

            productFreq[produk.nama] += produk.jumlah;
        }

        vector<product> products;
        for (auto [produk, freq] : productFreq)
        {
            product pp;
            pp.nama = produk;
            pp.jumlah = freq;
            products.push_back(pp);
        }

        sort(products.begin(), products.end(), [](product a, product b)
             { if (a.jumlah == b.jumlah) {
                return a.nama < b.nama;
             }
            return a.jumlah > b.jumlah; });

        cout << products.size() << endl;
        for (auto p : products)
        {
            cout << p.nama << " " << p.jumlah << endl;
        }
    }
}