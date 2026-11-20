#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
const char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789-";

// 37^length, length=5
void generateRandomString(string current, vector<string> &results, int length)
{
    if (current.length() == length)
    {
        results.push_back(current);
        return;
    }

    for (int i = 0; i < 37; i++)
    {
        generateRandomString(current + chars[i], results, length);
    }
}

ll genRandNumber(int max)
{
    std::random_device rd;

    std::mt19937 gen(rd());

    std::uniform_int_distribution<ll> dist(11, max);

    ll random_number = dist(gen);
    return random_number;
}

ll precomputeV(ll previousHash, string &transaction)
{
    ll v = previousHash;
    for (int i = 0; i < transaction.length(); i++)
    {
        v = (v * 31 + transaction[i]) % 1000000007;
    }
    return v;
}

ll H(ll v,
     ll token)
{
    return (v * 7 + token) % 1000000007;
}

bool isHashValid(ll hash)
{

    int trailingZerosCount = 0;
    while (hash)
    {
        bool isTrail = hash % 10 == 0;
        if (!isTrail)
        {
            break;
        }
        trailingZerosCount = isTrail ? trailingZerosCount + 1 : trailingZerosCount;
        hash /= 10;
    }

    return trailingZerosCount == 7;
}

int main()
{
    ll lastHashVal;
    cin >> lastHashVal;

    vector<string> transactions;
    generateRandomString("", transactions, 3);

    vector<string> blocksTs(2);
    vector<ll> blocksTokens(2);

    bool valid = false;
    for (int i = 0; i < transactions.size(); i++)
    {
        if ((i + 1) % 10000 == 0)
        {
            cout << i + 1 << endl;
        }
        string ts = transactions[i];
        ll v = precomputeV(lastHashVal, ts);

        for (int j = 0; j < 100; j++)
        {
            ll tt = j * 10000000;
            ll token = (tt - (v * 7) % 1000000007 + 1000000007) % 1000000007;
            auto hash = H(v, token);
            if (token >= 0 && isHashValid(hash))
            {
                blocksTs[0] = ts;
                blocksTokens[0] = token;
                valid = true;
                lastHashVal = hash;

                break;
            }
        }
        if (valid)
        {
            break;
        }
    }

    for (int i = 0; i < transactions.size(); i++)
    {
        if ((i + 1) % 10000 == 0)
        {
            cout << i + 1 << endl;
        }
        string ts = transactions[i];
        ll v = precomputeV(lastHashVal, ts);

        for (int j = 0; j < 100; j++)
        {
            ll tt = j * 10000000;
            ll token = (tt - (v * 7) % 1000000007 + 1000000007) % 1000000007;
            auto hash = H(v, token);
            if (token >= 0 && isHashValid(hash) && hash != lastHashVal)
            {
                blocksTs[1] = ts;
                blocksTokens[1] = token;
                valid = true;
                break;
            }
        }
        if (valid)
        {
            break;
        }
    }

    cout << blocksTs[0] << " " << blocksTokens[0] << endl;
    cout << blocksTs[1] << " " << blocksTokens[1] << endl;
}

// WA
// const char chars[] = "abcdefghijklmnopqrstuvwxyz0123456789-";

// // O(37^length), length=3
// void generateRandomString(string current, vector<string> &results, int length)
// {
//     if (current.length() == length)
//     {
//         results.push_back(current);
//         return;
//     }

//     for (int i = 0; i < 37; i++)
//     {
//         generateRandomString(current + chars[i], results, length);
//     }
// }

// ll genRandNumber()
// {
//     std::random_device rd;

//     std::mt19937 gen(rd());

//     std::uniform_int_distribution<ll> dist(0, 1000000000 - 1);

//     ll random_number = dist(gen);
//     return random_number;
// }

// ll H(ll previousHash, string &transaction,
//      ll token)
// {
//     ll v = previousHash;
//     for (int i = 0; i < transaction.length(); i++)
//     {
//         v = (v * 31 + transaction[i]) % 1000000007;
//     }
//     return (v * 7 + token) % 1000000007;
// }

// bool isHashValid(ll hash)
// {

//     int trailingZerosCount = 0;
//     while (hash)
//     {
//         bool isTrail = hash % 10 == 0;
//         if (!isTrail)
//         {
//             break;
//         }
//         trailingZerosCount = isTrail ? trailingZerosCount + 1 : trailingZerosCount;
//         hash /= 10;
//     }

//     return trailingZerosCount == 7;
// }

// int main()
// {
//     ll lastHashVal;
//     cin >> lastHashVal;

//     vector<string> transactions;
//     generateRandomString("", transactions, 3);

//     vector<string> blocksTs(2);
//     vector<ll> blocksTokens(2);

//     bool valid = false;
//     for (int i = 0; i < transactions.size(); i++)
//     {
//         if ((i + 1) % 10000 == 0)
//         {
//             cout << i + 1 << endl;
//         }
//         string ts = transactions[i];
//         for (int j = 0; j < 5; j++)
//         {
//             ll token = genRandNumber();
//             auto hash = H(lastHashVal, ts, token);
//             if (isHashValid(hash))
//             {
//                 blocksTs[0] = ts;
//                 blocksTokens[0] = token;
//                 valid = true;
//                 break;
//             }
//         }
//         if (valid)
//         {
//             break;
//         }
//     }

//     for (int i = 0; i < transactions.size(); i++)
//     {
//         if ((i + 1) % 10000 == 0)
//         {
//             cout << i + 1 << endl;
//         }
//         string ts = transactions[i];
//         for (int j = 0; j < 5; j++)
//         {
//             ll token = genRandNumber();
//             auto hash = H(lastHashVal, ts, token);
//             if (isHashValid(hash))
//             {
//                 blocksTs[1] = ts;
//                 blocksTokens[1] = token;
//                 valid = true;
//                 break;
//             }
//         }
//         if (valid)
//         {
//             break;
//         }
//     }

//     cout << blocksTs[0] << " " << blocksTokens[0] << endl;
//     cout << blocksTs[1] << " " << blocksTokens[1] << endl;
// }