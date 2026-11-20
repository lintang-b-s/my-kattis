#include <bits/stdc++.h>
using namespace std;

// naik_berapa_meter(t) is monotonic increasing
// turun_berapa_meter(t) is monotonic decreasing
// cari t yang f(t) =  naik_berapa_meter(t) - (h-turun_berapa_meter(t)) = 0. let this t yang memenuhi this equality called meet_time.
// dan f(t) >= 0 ketika t >= meet_time
// kita cari t paling kecil selama f(t) >= 0....
// bisa pakai binary search the answer  f(t) karena monotonic increasing

struct elevation_change
{
    double h, t;
};

double hitung_beda_tinggi_by_waktu(vector<elevation_change> &arr, double t, double h)
{
    double beda_tinggi_berapa_meter = 0.0;
    double pref_sum_time = 0.0;
    for (int i = 0; i < arr.size(); i++)
    {
        if (i > 0 && pref_sum_time < t)
        {
            if (t < pref_sum_time + arr[i].t)
            {
                beda_tinggi_berapa_meter += (arr[i].h / arr[i].t) * (t - pref_sum_time);
            }
            else
            {
                beda_tinggi_berapa_meter += (arr[i].h / arr[i].t) * (pref_sum_time + arr[i].t - pref_sum_time);
            }
            pref_sum_time += min(arr[i].t, t);
        }
        else if (pref_sum_time < t)
        {
            beda_tinggi_berapa_meter += (arr[i].h / arr[i].t) * min(arr[i].t, t);
            pref_sum_time += min(arr[i].t, t);
        }
    }

    return beda_tinggi_berapa_meter;
}

double bsta_waktu_biksu_bertemu(vector<elevation_change> &ascends, vector<elevation_change> &descends, int h, int max_time)
{
    double low = 0, high = max_time;
    double best_waktu_bertemu = 0.0;

    double selisih_tinggi_terbaik = numeric_limits<double>::max();

    for (int i = 0; i < 1000; i++)
    { // O(max(na,nd)). just 1k iterations. na= number of ascending segments. nd is the same but for descending..
        double mid_waktu = (low + high) / 2;
        double naik_t = hitung_beda_tinggi_by_waktu(ascends, mid_waktu, h);
        double turun_t = hitung_beda_tinggi_by_waktu(descends, mid_waktu, h);

        double curr_selisih = (naik_t - (h - turun_t));
        bool waktu_lebih_baik = curr_selisih >= 0;
        if (waktu_lebih_baik)
        {
            best_waktu_bertemu = mid_waktu;
            high = mid_waktu;
        }
        else
        {
            low = mid_waktu;
        }
    }

    return best_waktu_bertemu;
}

int main()
{
    int a, d;
    cin >> a >> d;
    int tinggi_bukit_kuil = 0;
    double max_time = 0;
    vector<elevation_change> ascends;
    for (int i = 0; i < a; i++)
    {
        double h, t;
        cin >> h >> t;
        ascends.push_back({h, t});
        tinggi_bukit_kuil += h;
        max_time += t;
    }

    vector<elevation_change> descends;

    double max_time_2 = 0.0;
    for (int i = 0; i < d; i++)
    {
        double h, t;
        cin >> h >> t;
        descends.push_back({h, t});
        max_time_2 += t;
    }
    max_time = max(max_time_2, max_time);

    cout.precision(12);
    cout << bsta_waktu_biksu_bertemu(ascends, descends, tinggi_bukit_kuil, max_time) << endl;
}
