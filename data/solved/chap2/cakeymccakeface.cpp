#include <bits/stdc++.h>

using namespace std;

typedef long long ll;

// https://open.kattis.com/problems/cakeymccakeface?editresubmit=18932376&tab=metadata

int main()
{
    vector<int> entryTimes, exitTimes;
    int N, M;
    cin >> N;
    cin >> M;

    for (int i = 0; i < N; i++)
    {
        ll waktuDeteksiEntry = 0;
        cin >> waktuDeteksiEntry;
        entryTimes.push_back(waktuDeteksiEntry);
    }

    for (int i = 0; i < M; i++)
    {
        ll waktuDeteksiExit = 0;
        cin >> waktuDeteksiExit;
        exitTimes.push_back(waktuDeteksiExit);
    }

    unordered_map<ll, int> waktuMemasakFreq;

    for (int i = 0; i < N; i++)
    { // O(NM)
        for (int j = 0; j < M; j++)
        {
            ll waktuEntry = entryTimes[i];
            ll waktuExit = exitTimes[j];
            if (waktuEntry <= waktuExit)
            {
                waktuMemasakFreq[waktuExit - waktuEntry]++;
            }
        }
    }

    int waktuMemasakMax = -1;

    int maxFreq = -1;

    for (auto [waktuMemasak, freq] : waktuMemasakFreq)
    { // O(max{N,M})
        if (freq > maxFreq)
        {
            maxFreq = freq;
        }
    }

    vector<ll> waktuMemasaksHighestFreq;

    for (auto [waktuMemasak, freq] : waktuMemasakFreq)
    { // O(max{N,M})

        if (maxFreq == freq)
        {
            waktuMemasaksHighestFreq.push_back(waktuMemasak);
        }
    }

    ll bestWaktuMemasak = 1 << 30;
    for (auto waktuMemasak : waktuMemasaksHighestFreq)
    { // O(max{N,M})
        if (waktuMemasak < bestWaktuMemasak)
        {
            bestWaktuMemasak = waktuMemasak;
        }
    }

    if (bestWaktuMemasak == (ll)(1 << 30))
    {
        bestWaktuMemasak = 0;
    }
    cout << bestWaktuMemasak;

    // map<int, vector<ll>> freqWaktuMemasak;
    // for (auto [waktuMemasak, freq] : waktuMemasakFreq)
    // {

    //     freqWaktuMemasak[freq].push_back(waktuMemasak);
    // }

    // vector<ll> waktuMemasaksHighestFreq;
    // if (freqWaktuMemasak.size() > 0)
    // {
    //     auto maxNumberWaktuMemasak = freqWaktuMemasak.rbegin();
    //     waktuMemasaksHighestFreq = maxNumberWaktuMemasak->second;
    // }

    // ll bestWaktuMemasak = 1 << 30;
    // for (auto waktuMemasak : waktuMemasaksHighestFreq)
    // {
    //     if (waktuMemasak < bestWaktuMemasak)
    //     {
    //         bestWaktuMemasak = waktuMemasak;
    //     }
    // }

    // if (bestWaktuMemasak == (ll)(1 << 30))
    // {
    //     bestWaktuMemasak = 0;
    // }
    // cout << bestWaktuMemasak;
}