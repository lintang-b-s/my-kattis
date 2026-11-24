#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

const int N = 200000;

using cd = complex<double>;
const double PI = acos(-1);

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

    double ang = 2 * PI / n * (invert ? -1 : 1);
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

// naive_polynomials_multiplication computes naive O(n^2) polynomial multiplication (or convolution).
vector<int> naive_polynomials_multiplication(vector<int> &a, vector<int> &b)
{
    vector<int> fa(a.begin(), a.end()), fb(b.begin(), b.end());

    int n = 1;
    while (n < a.size() + b.size())
    { // extend the coefficient vector into 2n coeficients
        // so that the pointwise polynomial multiplication resulted from fft
        // resulting in polynomial C of degree-bound 2n
        n <<= 1;
    }

    fa.resize(n);
    fb.resize(n);

    vector<int> fc(n, 0);
    for (int j = 0; j < n; j++)
    { // O(n^2)
        for (int k = 0; k <= j; k++)
        {
            fc[j] += fa[k] * fb[j - k];
        }
    }
    return fc;
}

/*
this is classic textbook example application of fast fourier transform
similiar to generating function for counting problem
which is to do convolution to combine two histograms a and b
in this problem histogram a=b=input array
*/
int main()
{
    int n;
    cin >> n;
    vector<int> golfbot_distances(n);
    for (int i = 0; i < n; i++)
    {
        cin >> golfbot_distances[i];
    }

    int m;
    cin >> m;
    vector<int> holes_distances(m);
    for (int i = 0; i < m; i++)
    {
        cin >> holes_distances[i];
    }

    vector<ll> golfbot_distances_freq(N);
    for (int i = 0; i < n; i++)
    {
        auto d = golfbot_distances[i];
        golfbot_distances_freq[d]++;
    }
    golfbot_distances_freq[0] = 1; // buat one-shot golf//

    auto distances_reached = fft_multiply(golfbot_distances_freq, golfbot_distances_freq); // O(NlgN)
    int holes_completed = 0;
    for (auto d : holes_distances)
    { // O(m)
        auto d_freq = distances_reached[d];
        if (d_freq > 0)
        {
            holes_completed++;
        }
    }
    cout << holes_completed << endl;
}