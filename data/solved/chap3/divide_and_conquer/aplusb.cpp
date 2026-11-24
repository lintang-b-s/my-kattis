#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
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

// multiply computes polynomial multiplication with fourier transform method in O(nlgn) time
vector<ll> multiply(vector<ll> const &a, vector<ll> const &b)
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

/*
this is classic textbook example application of fast fourier transform
similiar to generating function for counting problem
which is to do convolution to combine two histograms a and b
in this problem histogram a=b=input array
sample input 1:
4
1 2 3 4


4 = 1+3 = 3+1
3 = 1+2 = 2+1


i != j
(i, j) != (j, i) for all indexes i<j.


i | freq
1 |  1
2 |  1
3 |  1
4 |  1

tapi note that hasil dari convolution fft nya bisa include ak=ai+ai or ak=aj+aj, for ak=1,2,3,4 (untuk sample input 1)
contoh: 2 = 1+1 = 1*2
4 = 2+2 = 2*2

perhatikan bahwa untuk array of N integers arr, dengan maxi=max(arr)
number of ak such that ak=ai+ai=2ai, for all 1<=ai,ak<=maxi
hanyalah semua bilangan genap diantara a1, a2,.., an
kenapa? karena semua bilangan genap adalah ak=2ai=ai+ai, for some integer ai<ak.

sample input 2:
6
1 1 3 3 4 6

a = 1 1 3 3 4 6
b = 1 1 3 3 4 6
i = 1 2 3 4 5 6

ak | indexes (i,j,k)
4 = (1,3,5), (1,4,5), (3,1,5), (4,1,5), (2,3,5), (3,2,5), (2,4,5), (4,2,5)
6 = (3,4,6), (4,3,6)


4 = 1+3
6 = 3+3
disini hasil convolution dari fast fourier transform bisa include:
6 = (3,3,6), (4,4,6)


sample input 3:
3
0 10 10

ak | indexes (i,j,k)
10 = (1,2,2), (2,1,2), (1,3,3) (3,1,3), (1,2,3), (2,1,3), (3,1,2), (1,3,2)
harus nya output 4 aja [(1,2,3), (2,1,3), (3,1,2), (1,3,2)]
tapi karena convolutionnya fft, masih bisa include other 4 frequency dari ak=10=ai+aj diatas
tapi i=k atau j=k... yang [(1,2,2), (2,1,2), (1,3,3) (3,1,3)]
berarti kalau ada ai=0, for some 1<=i<=N
setiap ak=ai+aj yang i=k atau j=k bakal ada 2 untuk setiap count frequency dari 0

sample input 4:
3
0 0 0
ak | indexes (i,j,k)
0 = valid: (1,2,3), (2,1,3), (2,3,1) (3,2,1), (1,3,2), (3,1,2)
    invalid: (1,2,2), (2,1,2), (1,3,3), (3,1,3), (2,3,3), (3,2,3),
             (2,3,2), (3,2,2), (1,2,1), (2,1,1), (2,3,1), (3,2,1)


untuk setiap ak=0 ada 2*(freq[ak]-1) triples yang invalid karena
ak=ai+aj=0 yang invalid ketika 2 case: i=k atau j=k.
i=k, so ak=ak+aj=0, karena ak udah dipake ada (freq[ak]-1) yang bisa jadi aj=0
j=k, so ak=ai+aj=0, karena ak udah dipake ada (freq[ak]-1) yang bisa jadi ai=0
total ada 2*(freq[ak]-1)

*/

const int offset = 50000;
const int N = 100001;

int main()
{
    int n;
    cin >> n;
    vector<int> arr(n);

    for (int i = 0; i < n; i++)
    {
        cin >> arr[i];
        arr[i] + offset;
    }

    vector<ll> a_freq(N, 0);
    vector<ll> b_freq(N, 0);
    for (int i = 0; i < n; i++)
    {
        auto v = arr[i] + offset;
        a_freq[v]++;
        b_freq[v]++;
    }

    ll number_of_ways = 0;
    auto c_freq = multiply(a_freq, b_freq); // O(NlgN)

    for (int i = 0; i < n; i++)
    { // O(n)
        // removes ak=ai+ai=2ai
        auto ai = arr[i] + offset;
        c_freq[ai * 2]--;
    }

    for (int i = 0; i < n; i++) // O(n)
    {
        auto ak = arr[i] + 2 * offset; // (ai+offset)+(bi+offset)=ai+bi+2*offset=ak
        number_of_ways += c_freq[ak];
        if (arr[i] != 0)
        {
            number_of_ways -= 2 * a_freq[offset];
        }
        else
        {
            number_of_ways -= 2 * (a_freq[offset] - 1);
        }
    }
    cout << number_of_ways << endl;
}