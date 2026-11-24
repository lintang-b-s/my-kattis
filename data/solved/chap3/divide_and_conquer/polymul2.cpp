#include <bits/stdc++.h>
using namespace std;

using cd = complex<double>;
const double PI = acos(-1);

// code for fft below adapted from: https://cp-algorithms.com/algebra/fft.html
// my ipad notes for fast fourier transform: https://drive.google.com/file/d/1Pl6qEFNHvDfuBrbxxZSYLx5VqseJ__wi/view?usp=sharing

// fft fast fourier transform
// computes the point-values representation of polynomial from coefficient representation
// utilise complex (2n)th roots of unity to get the  point-values representation of polynomial.
// if invert=true, then it computes inverse fast fourier transform, which is computes coefficient representation from point-values representation
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
vector<int> fft_multiply(vector<int> const &a, vector<int> const &b)
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

    vector<int> result(n);
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

int main()
{

    int t;
    cin >> t;
    while (t--)
    {
        int na, nb;
        cin >> na;
        vector<int> a(na + 1);
        for (int i = 0; i <= na; i++)
        {
            cin >> a[i];
        }

        cin >> nb;
        vector<int> b(nb + 1);
        for (int i = 0; i <= nb; i++)
        {
            cin >> b[i];
        }

        // auto c = naive_polynomials_multiplication(a, b); // O(n^2) TLE
        auto c = fft_multiply(a, b); // O(nlgn)
        int c_degree_bound = (na + 1) + (nb + 1) - 1;
        cout << c_degree_bound - 1 << endl;
        for (int i = 0; i < c_degree_bound; i++)
        {
            cout << c[i];
            if (i < c_degree_bound - 1)
            {
                cout << " ";
            }
        }
        cout << endl;
    }
}