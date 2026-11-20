#include <bits/stdc++.h>
using namespace std;
/*
D=n2^2
sqrt(D)=n2=n1+x
          >= 0 + x   [frame starts at  0, n1>=0]
x <= sqrt(D)

(n1+x)^2 - n1^2 = D
*/

int main()
{
    int D;
    cin >> D;
    bool udah_mas = false;
    for (int x = 0; x <= sqrt(D); x++)
    { // O(D sqrt(D))
        for (int n1 = 0; n1 <= D; n1++)
        {
            int n2 = n1 + x;

            if (n2 * n2 - n1 * n1 == D)
            {
                cout << n1 << " " << n2 << endl;
                return 0;
            }
        }
    }
    cout << "impossible" << endl;
}

// WA
// int main()
// {
//     int D;
//     cin >> D;
//     bool udah_mas = false;
//     for (int n1 = 0; n1 <= 24998; n1++)
//     {
//         for (int n2 = 0; n2 <= 25002; n2++)
//         {
//             if (n2 * n2 - n1 * n1 == D)
//             {
//                 cout << n1 << " " << n2 << endl;
//                 return 0;;
//             }
//         }

//     }
//     cout << "impossible" << endl;
// }