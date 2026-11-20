#include <bits/stdc++.h>
using namespace std;

/*
https://open.kattis.com/problems/hypercube?tab=metadata


1-bit gray code = 0,1
2-bit gray code = 00, 01, 11, 10 -> reversed = 10, 11, 01, 00
3-bit gray code = 000, 001, 011, 010, 110, 111, 101, 100

3-bit gray code:
      gray   i       (i>>1)
i=0-> 000
i=1-> 001 = 001 XOR (1>>1)
i=2-> 011 = 010 XOR (2>>1)
i=3-> 010 = 011 XOR (3>>1)
.
.
.
i=7-> 100 = 111 XOR (7>>1)
rumus = untuk indeks-i = i ^ (i>>1)

there are 2^n-1 number of elements in n-bit gray code...

misal input: 3 001 111
antara i=1 to i=5

tinggal (5-1+1)-2=3 // -2 karena exclude 2 element itu
tapi solusi ini O(2^n), dapet TLE dari kattis..

how to optimize?
kita harus bisa: given gray code, what is i?

graycode(i) = i ^ (i>>1)

perhatikan msb(gray(i)) == msb(i)

tapi buat bit n-2 to 0 dari msb beda:
gray[k] = i[k] XOR i[k+1], for 0<=k<=n-2 dan i[n-1] = 0
misal k = 0 (3-bit gray code buat i=2):
1 = 0 XOR 1

i=3, k=0
0 = 1 XOR 1

so buat convert gray code-i ke i:
misal graycode=011, berapakah i?

gray[k] = i[k] XOR i[k+1]
bisa diubah ke:  i[k] = gray[k] XOR i[k+1], for k=n-2 downto 0 dan i[n-1]=0


*/

int main()
{
    int n;
    string a, b;
    cin >> n >> a >> b;
    unsigned long long aGray = 0, bGray = 0;

    for (int i = 0; i < n; i++)
    {
        if (a[i] == '1')
        {
            aGray |= 1ULL << (n - i - 1);
        }
        if (b[i] == '1')
        {
            bGray |= 1ULL << (n - i - 1);
        }
    }

    unsigned long long aGrayLast = aGray & (1ULL << (n - 1)) ? 1 : 0;
    unsigned long long bGrayLast = bGray & (1ULL << (n - 1)) ? 1 : 0;

    unsigned long long ai = aGrayLast << (n - 1), bi = bGrayLast << (n - 1);
    for (int i = n - 2; i >= 0; i--) // O(n-2)
    {
        int aGrayk = (aGray & (1ULL << i)) ? 1 : 0;
        int bGrayk = (bGray & (1ULL << i) )? 1 : 0;

        int aikplusone = (ai & (1ULL << (i + 1))) ? 1 : 0;
        int bikplusone = (bi & (1ULL << (i + 1)) )? 1 : 0;

        ai |= (unsigned long long)(aikplusone ^ aGrayk) << i;
        bi |= (unsigned long long)(bikplusone ^ bGrayk) << i;
    }
    cout << bi - ai - 1;

    // unsigned long long aid = 0, bid = 0;

    // for (unsigned long long i = 0; i < (1ULL << n); i++)
    // { // O(2^n)
    //     long long grayCode = i ^ (i >> 1);
    //     if (grayCode == aint)
    //     {
    //         aid = i;
    //     }
    //     if (grayCode == bint)
    //     {
    //         bid = i;
    //     }
    // }
    // cout << bid - aid - 1;
}