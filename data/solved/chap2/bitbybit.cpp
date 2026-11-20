#include <bits/stdc++.h>

using namespace std;

// https://open.kattis.com/problems/bitbybit?tab=metadata

int main()
{
    int n;
    int bits[32];
    fill(bits, bits + 32, 2);

    while (true)
    {
        cin >> n;
        cin.ignore();
        if (n == 0)
        {
            break;
        }

        for (int i = 0; i < n; i++) // O(n), all bitwise operation is O(1)
        {
            string line;
            getline(cin, line);
            istringstream ss(line);

            vector<string> ops;
            string op;
            while (getline(ss, op, ' '))
            {
                ops.push_back(op);
            }
            if (ops[0] == "SET")
            {
                int j = stoi(ops[1]);
                bits[j] = 1;
            }
            else if (ops[0] == "CLEAR")
            {
                int j = stoi(ops[1]);
                bits[j] = 0;
            }
            else if (ops[0] == "AND")
            {
                int i = stoi(ops[1]);
                int j = stoi(ops[2]);
                int bitj = bits[j];
                int biti = bits[i];

                if (biti == 2 || bitj == 2)
                {
                    if (biti == 0 || bitj == 0)
                    {
                        bits[i] = 0;
                    }
                    else
                    {
                        bits[i] = 2;
                    }
                }
                else
                {
                    int andres = biti & bitj;
                    // set the res to bit-i
                    if (andres)
                    {
                        bits[i] = 1;
                    }
                    else
                    {
                        bits[i] = 0;
                    }
                }
            }
            else
            {
                int i = stoi(ops[1]);
                int j = stoi(ops[2]);
                int bitj = bits[j];
                int biti = bits[i];

                if (biti == 2 || bitj == 2)
                {
                    if (biti == 1 || bitj == 1)
                    {
                        bits[i] = 1;
                    }
                    else
                    {
                        bits[i] = 2;
                    }
                }
                else
                {
                    int andres = biti | bitj;
                    // set the res to bit-i
                    if (andres)
                    {
                        bits[i] = 1;
                    }
                    else
                    {
                        bits[i] = 0;
                    }
                }
            }
        }

        string bitstring = "";

        for (int i = 31; i >= 0; i--) // 32 ops
        {
            int biti = bits[i];
            if (biti == 1)
            {
                bitstring += '1';
            }
            else
            {
                if (biti != 2)
                {
                    bitstring += '0';
                }
                else
                {
                    bitstring += '?';
                }
            }
        }
        cout << bitstring << endl;
        fill(bits, bits + 32, 2);
    }

    return 0;
}

// // wrong answer on test case 2
// int main()
// {
//     int bit = 0;
//     int n;
//     bool known[32];
//     memset(known, false, sizeof(known));
//     while (true)
//     {
//         cin >> n;
//         cin.ignore();
//         if (n == 0)
//         {
//             break;
//         }

//         for (int i = 0; i < n; i++)
//         {
//             string line;
//             getline(cin, line);
//             istringstream ss(line);

//             vector<string> ops;
//             string op;
//             while (getline(ss, op, ' '))
//             {
//                 ops.push_back(op);
//             }
//             if (ops[0] == "SET")
//             {
//                 int j = stoi(ops[1]);
//                 bit |= (1 << j);
//             }
//             else if (ops[0] == "CLEAR")
//             {
//                 int j = stoi(ops[1]);
//                 bit &= ~(1 << j);
//                 known[j] = true;
//             }
//             else if (ops[0] == "AND")
//             {
//                 int i = stoi(ops[1]);
//                 int j = stoi(ops[2]);
//                 int bitj = bit & (1 << j) ? 1 : 0;
//                 int biti = bit & (1 << i) ? 1 : 0;
//                 int andres = biti & bitj;
//                 // set the res to bit-i
//                 if (andres)
//                 {
//                     bit |= (1 << i);
//                 }
//                 else
//                 {
//                     bit &= ~(1 << i);
//                 }
//             }
//             else
//             {
//                 int i = stoi(ops[1]);
//                 int j = stoi(ops[2]);
//                 int bitj = bit & (1 << j) ? 1 : 0;
//                 int biti = bit & (1 << i) ? 1 : 0;
//                 int andres = biti | bitj;
//                 // set the res to bit-i
//                 if (andres)
//                 {
//                     bit |= (1 << i);
//                 }
//                 else
//                 {
//                     bit &= ~(1 << i);
//                 }
//             }
//         }

//         string bitstring = "";

//         for (int i = 31; i >= 0; i--)
//         {
//             int biti = bit >> i;
//             if (biti & (1 << 0))
//             {
//                 bitstring += '1';
//             }
//             else
//             {
//                 if (known[i])
//                 {
//                     bitstring += '0';
//                 }
//                 else
//                 {
//                     bitstring += '?';
//                 }
//             }
//         }
//         cout << bitstring << endl;
//         bit = 0;
//         memset(known, false, sizeof(known));
//     }

//     return 0;
// }
