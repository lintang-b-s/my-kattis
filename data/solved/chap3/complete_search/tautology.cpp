#include <bits/stdc++.h>
using namespace std;

struct ope
{
    bool cur;
    bool enter;
};

bool eval(string exprs, int p, int q, int r, int s, int t, int &i)
{
    char c = exprs[i++];
    bool cur = false;
    switch (c)
    {
    case 'p':
        /* code */
        cur = p;
        return cur;
    case 'q':
        /* code */
        cur = q;
        return cur;
    case 'r':
        /* code */
        cur = r;
        return cur;
    case 's':
        /* code */
        cur = s;
        return cur;
    case 't':
        /* code */
        cur = t;
        return cur;
    case 'N':
        return !eval(exprs, p, q, r, s, t, i);
    default:
        break;
    }

    auto w = eval(exprs, p, q, r, s, t, i);
    auto x = eval(exprs, p, q, r, s, t, i);

    switch (c)
    {

    case 'A':
        /* code */
        cur = w || x;
        break;
    case 'K':

        cur = w && x;
        break;
    case 'C':
        cur = !x || w;
        break;
    case 'E':
        cur = x == w;
        break;
    default:
        break;
    }

    return cur;
};

int main()
{

    string ss;

    while (cin >> ss)
    {
        if (ss == "0")
        {
            break;
        }

        bool res = true;
        // O (2^5 * n), n = len(ss)
        for (int p = 0; p < 2; p++)
        {
            for (int q = 0; q < 2; q++)
            {
                for (int r = 0; r < 2; r++)
                {
                    for (int s = 0; s < 2; s++)
                    {

                        for (int t = 0; t < 2; t++)
                        {
                            int i = 0;
                            res = res && eval(ss, p, q, r, s, t, i);
                        }
                    }
                }
            }
        }

        if (res)
        {
            cout << "tautology" << endl;
        }
        else
        {
            cout << "not" << endl;
        }
    }
}

// WA
// int main()
// {

//     string ss;

//     auto getOperand = [](char operand, int p, int q, int r, int s, int t)
//     {
//         bool cur = false;
//         bool enter = true;
//         switch (operand)
//         {
//         case 'p':
//             /* code */
//             cur = p;
//             break;
//         case 'q':
//             /* code */
//             cur = q;
//             break;

//         case 'r':
//             /* code */
//             cur = r;
//             break;
//         case 's':
//             /* code */
//             cur = s;
//             break;
//         case 't':
//             /* code */
//             cur = t;
//             break;
//         default:
//             enter = false;
//             break;
//         }
//         return ope{cur, enter};
//     };

//     while (cin >> ss)
//     {
//         if (ss == "0")
//         {
//             break;
//         }
//         stack<char> ops;
//         vector<char> operands;

//         for (int i = 0; i < ss.size(); i++)
//         {
//             if (ss[i] == 'A' || ss[i] == 'N' || ss[i] == 'K' ||
//                 ss[i] == 'C' || ss[i] == 'E')
//             {
//                 ops.push(ss[i]);
//             }
//             else
//             {
//                 operands.push_back(ss[i]);
//             }
//         }

//         bool res = true;
//         // O (2^5 * n), n = len(ss)
//         for (int p = 0; p < 2; p++)
//         {
//             for (int q = 0; q < 2; q++)
//             {
//                 for (int r = 0; r < 2; r++)
//                 {
//                     for (int s = 0; s < 2; s++)
//                     {

//                         for (int t = 0; t < 2; t++)
//                         {
//                             int i = operands.size() - 1;
//                             auto operand = operands[i];
//                             i--;
//                             auto [cur, enter] = getOperand(operand, p, q, r, s, t);

//                             stack<char> curOps = ops;

//                             while (curOps.size() > 0)
//                             {
//                                 enter = true;
//                                 auto op = curOps.top();
//                                 curOps.pop();

//                                 char operand = ' ';
//                                 bool prev = false;
//                                 if (op == 'C' || op == 'A' || op == 'K' || op == 'E')
//                                 {
//                                     operand = operands[i];
//                                     auto ope = getOperand(operand, p, q, r, s, t);
//                                     prev = ope.cur;
//                                     enter = ope.enter;
//                                     i--;
//                                 }

//                                 switch (op)
//                                 {
//                                 case 'N':
//                                     /* code */
//                                     cur = !cur;
//                                     break;
//                                 case 'A':
//                                     /* code */

//                                     cur = prev || cur;
//                                     break;
//                                 case 'K':

//                                     cur = prev && cur;
//                                     break;
//                                 case 'C':
//                                     cur = !cur || prev;
//                                     break;
//                                 case 'E':
//                                     cur = cur == prev;
//                                     break;
//                                 default:
//                                     enter = false;
//                                     break;
//                                 }
//                             }

//                             res = cur && res;
//                         }
//                     }
//                 }
//             }
//         }

//         if (res)
//         {
//             cout << "tautology" << endl;
//         }
//         else
//         {
//             cout << "not" << endl;
//         }
//     }
// }