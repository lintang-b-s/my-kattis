#include <bits/stdc++.h>
using namespace std;

// O(2^n) with lots of pruning.
void backtrack(int i, vector<bool> &reserve, vector<bool> &damage, int &maxi, int borrow)
{
    if (i == damage.size())
    {
        maxi = max(maxi, borrow);
        return;
    }

    if (i > 0 && damage[i] && reserve[i - 1])
    {
        reserve[i - 1] = false;
        damage[i] = false;
        backtrack(i + 1, reserve, damage, maxi, borrow + 1);
        reserve[i - 1] = true;
        damage[i] = true;
    }
    else if (i < damage.size() - 1 && damage[i] && reserve[i + 1])
    {
        reserve[i + 1] = false;
        damage[i] = false;
        backtrack(i + 1, reserve, damage, maxi, borrow + 1);
        reserve[i + 1] = true;
        damage[i] = true;
    }

    backtrack(i + 1, reserve, damage, maxi, borrow);
}

int main()
{
    int n, s, r;
    cin >> n >> s >> r;
    vector<bool> reserve(n, false);
    vector<bool> damage(n, false);

    int damagedCount = 0;
    for (int i = 0; i < s; i++)
    {
        int a;
        cin >> a;
        a--;
        damage[a] = true;
        damagedCount++;
    }

    for (int i = 0; i < r; i++)
    {
        int a;
        cin >> a;
        a--;
        reserve[a] = true;
    }

    int maxi = 0;
    int borrow = 0;
    backtrack(0, reserve, damage, maxi, borrow);
    cout << damagedCount - maxi << endl;
}