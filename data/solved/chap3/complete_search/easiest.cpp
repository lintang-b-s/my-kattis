#include <bits/stdc++.h>
using namespace std;

int getDigitSum(int m)
{
    int sum = 0;
    while (m)
    {
        sum += m % 10;
        m /= 10;
    }
    return sum;
}

int main()
{
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        int digit_sum = getDigitSum(n);

        for (int p = 11; p <= 100000; p++)
        {
            int mult_digit_sum = getDigitSum(p * n);
            if (mult_digit_sum == digit_sum)
            {
                cout << p << endl;
                break;
            }
        }
    }
}
