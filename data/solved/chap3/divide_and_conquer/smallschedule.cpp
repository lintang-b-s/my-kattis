#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

bool serve(ll q, ll l, ll s, ll m, ll c)
{
    int q_used_count = 0;
    int one_used_count = 0;
    for (int i = 0; i < m; i++)
    {
        int cur_q_count = min(c / q, l - q_used_count);
        q_used_count += cur_q_count;
        one_used_count += min(c - q * cur_q_count, s - one_used_count);
    }
    return q_used_count == l && one_used_count == s;
}

ll bsta(ll q, ll l, ll s, ll m)
{
    ll low = 0, high = q * l + s;
    ll best_tot_process_time = high;
    while ((high - low) > 1)
    {// O(log(q*l+s)*m)
        ll mid = (low + high) / 2;
        if (serve(q, l, s, m, mid))
        {
            best_tot_process_time = mid;
            high = mid;
        }
        else
        {
            low = mid;
        }
    }

    return best_tot_process_time;
}

int main()
{

    ll q, m, s, l;
    cin >> q >> m >> s >> l;

    cout << bsta(q, l, s, m) << endl;
}

// wa
// bool serve(ll q, ll l, ll s, ll m, ll c)
// {

//     ll q_request_used_count = 0;
//     ll one_request_used_count = 0;
//     ll tot_purchasing_time = q * l + s;
//     ll tot_processing_time = 0;
//     bool ok = true;
//     while (tot_purchasing_time > 0)
//     {
//         bool good = false;
//         ll curr_process_time = 0;
//         for (int i = 0; i < m; i++)
//         {
//             if (q_request_used_count < l && q < tot_purchasing_time)
//             {
//                 tot_purchasing_time -= q;
//                 q_request_used_count++;
//                 curr_process_time = max(curr_process_time, q);
//                 good = true;
//             }
//             else if (one_request_used_count < s)
//             {
//                 ll proc = min(q, tot_purchasing_time);
//                 curr_process_time = max(curr_process_time, proc);
//                 tot_purchasing_time -= proc;
//                 one_request_used_count += proc;
//                 good = true;
//             }
//         }

//         if (!good)
//         {
//             ok = false;
//             break;
//         }
//         tot_processing_time += curr_process_time;
//     }

//     return ok && tot_processing_time <= c;
// }

// ll bsta(ll q, ll l, ll s, ll m)
// {
//     ll low = 0, high = q * l + s;
//     ll best_tot_process_time = high;
//     while ((high - low) > 1)
//     {
//         ll mid = (low + high) / 2;
//         if (serve(q, l, s, m, mid))
//         {
//             best_tot_process_time = mid;
//             high = mid;
//         }
//         else
//         {
//             low = mid;
//         }
//     }

//     return best_tot_process_time;
// }

// int main()
// {

//     ll q, m, s, l;
//     cin >> q >> m >> s >> l;

//     cout << bsta(q, l, s, m) << endl;
// }
