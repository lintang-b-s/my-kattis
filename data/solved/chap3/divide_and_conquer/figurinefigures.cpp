#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int MAX_FIGURINE_WEIGHT = 60001;
using cd = complex<long double>;
const long double PI = acos(-1);

// code for fft below adapted from: https://cp-algorithms.com/algebra/fft.html
// my ipad notes for fast fourier transform: https://drive.google.com/file/d/1Pl6qEFNHvDfuBrbxxZSYLx5VqseJ__wi/view?usp=sharing

// fft fast fourier transform
// computes the point-values representation of polynomial from coefficient representation
// utilise complex (2n)th roots of unity to get the  point-values representation of polynomial.
// if invert=true, then it computes inverse fourier transform, which is computes coefficient representation from point-values representation
// O(nlgn) time
void fft(vector<cd> &a, bool invert)
{
    int n = a.size();
    if (n == 1)
    {
        return;
    }

    vector<cd> a0(n / 2), a1(n / 2);
    for (int i = 0; 2 * i < n; i++)
    {
        a0[i] = a[2 * i];
        a1[i] = a[2 * i + 1];
    }
    fft(a0, invert);
    fft(a1, invert);

    long double ang = 2 * PI / n * (invert ? -1 : 1);
    cd w(1), wn(cos(ang), sin(ang));
    for (int i = 0; 2 * i < n; i++)
    {
        a[i] = a0[i] + w * a1[i];
        a[i + n / 2] = a0[i] - w * a1[i];
        if (invert)
        {
            a[i] /= 2;
            a[i + n / 2] /= 2;
        }
        w *= wn;
    }
}

// fft_multiply computes polynomial multiplication with fourier transform method in O(nlgn) time
vector<ll> fft_multiply(vector<ll> const &a, vector<ll> const &b)
{
    vector<cd> fa(a.begin(), a.end()), fb(b.begin(), b.end());
    int n = 1;
    while (n < a.size() + b.size())
    { // extend the coefficient vector into 2n coeficients
        // so that the pointwise polynomial multiplication resulted from fft
        // resulting in polynomial C of degree-bound 2n
        n <<= 1;
    }
    fa.resize(n);
    fb.resize(n);

    fft(fa, false); // O(nlgn) fast fourier transform polynomial A(x)
    fft(fb, false); // O(nlgn) fast fourier transform polynomial B(x)
    for (int i = 0; i < n; i++)
    { // O(n)
        // pointwise multiplication of the point-values representation of polynomial A(x) and B(x)
        fa[i] *= fb[i];
    }
    fft(fa, true); // O(nlgn) inverse fast fourier transform polynomial C(x)=A(x)*B(x)

    vector<ll> result(n);
    for (int i = 0; i < n; i++)
    { // O(n)
        result[i] = round(fa[i].real());
    }
    return result;
}

int main()
{
    cout << fixed << setprecision(15);
    int n;
    cin >> n;
    vector<int> figurines_weight(n);
    for (int i = 0; i < n; i++)
    {
        cin >> figurines_weight[i];
    }

    vector<ll> figurines_weight_freq(MAX_FIGURINE_WEIGHT);
    for (int i = 0; i < n; i++)
    {
        auto f_w = figurines_weight[i];
        figurines_weight_freq[f_w]++;
    }

    // TLE
    // auto figurines_weight_freq_pow_2 = fft_multiply(figurines_weight_freq, figurines_weight_freq);       // O(nlgn)
    // auto figurines_weight_freq_pow_3 = fft_multiply(figurines_weight_freq_pow_2, figurines_weight_freq); // O(nlgn)
    // auto figurines_weight_freq_pow_4 = fft_multiply(figurines_weight_freq_pow_3, figurines_weight_freq); // O(nlgn)
    auto figurines_weight_freq_pow_2 = fft_multiply(figurines_weight_freq, figurines_weight_freq);             // O(nlgn), n=MAX_FIGURINE_WEIGHT
    auto figurines_weight_freq_pow_4 = fft_multiply(figurines_weight_freq_pow_2, figurines_weight_freq_pow_2); // O(nlgn)

    long double expected_weight = 0.0;
    ll number_of_distinct_weights = 0;
    ll max_weight = 0;
    ll min_weight = 1e9;
    ll tot_freq = 0;

    for (ll w = 0; w < MAX_FIGURINE_WEIGHT * 4; w++)
    {
        auto w_freq = figurines_weight_freq_pow_4[w];
        if (w_freq > 0)
        {
            max_weight = max(max_weight, w);
            min_weight = min(min_weight, w);
            number_of_distinct_weights++;
            expected_weight += w_freq * w;
            tot_freq += w_freq;
        }
    }

    expected_weight /= tot_freq;
    cout << max_weight << " " << min_weight << " " << number_of_distinct_weights << " " << expected_weight;
}