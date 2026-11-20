#include <bits/stdc++.h>
using namespace std;


// WA
// int main()
// {
//     int N;
//     cin >> N;

//     long long front = 0;
//     long long currentMax = 0;
//     long long currentMin = 10e9;
//     stack<int> pegunungan;
//     long long highestBridge = 0;
//     for (int i = 0; i < N; i++)
//     {
//         long long tinggiGunung;
//         cin >> tinggiGunung;
//         if (!pegunungan.empty() && tinggiGunung > front)
//         {
//             long long gunungTerakhir = pegunungan.top();
//             while (gunungTerakhir != front)
//             {
//                 pegunungan.pop();
//                 gunungTerakhir = pegunungan.top();
//             }
//             pegunungan.pop();

//             long long gunungPembentukBridgeTerendah = min(front, tinggiGunung);
//             highestBridge = max(highestBridge, gunungPembentukBridgeTerendah - currentMin);
//             front = tinggiGunung;
//             currentMin = 10e9;
//             currentMax = 0;
//         }
//         else
//         {
//             if (tinggiGunung > currentMax)
//             {
//                 highestBridge = max(highestBridge, tinggiGunung - currentMin);
//             }
//             currentMax = max(currentMax, tinggiGunung);
//             currentMin = min(currentMin, tinggiGunung);
//         }

//         if (i == 0)
//         {
//             front = tinggiGunung;
//         }

//         pegunungan.push(tinggiGunung);
//     }

//     cout << highestBridge;
// }
