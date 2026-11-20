#include <bits/stdc++.h>
using namespace std;

bool isValidPIN(int pin)
{
    bool used[10];
    memset(used, false, sizeof used);
    int m = pin;
    vector<int> digits;
    while (m)
    {
        if (used[m % 10])
        {
            return false;
        }
        used[m % 10] = true;
        digits.push_back(m % 10);
        m /= 10;
    }

    if (digits.size() != 6)
    {
        return false;
    }
    for (int i = 0; i < digits.size(); i++)
    {
        if (digits[i] != 0 && pin % digits[i] != 0)
        {
            return false;
        }
        else if (digits[i] == 0)
        {
            return false;
        }
    }
    return true;
}

int main()
{
    int l, h;
    cin >> l >> h;

    int count = 0;
    for (int pin = l; pin <= h; pin++)
    {// O((h-l) * maxdigit)
        if (isValidPIN(pin))
        {
            count++;
        }
    }
    cout << count << endl;
}