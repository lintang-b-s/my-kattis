#include <bits/stdc++.h>
using namespace std;

struct point
{
    int id;
    double x, y;
};

bitset<100005> q_points;

double euclidean(point p1, point p2)
{
    return (p1.x - p2.x) * (p1.x - p2.x) +
           (p1.y - p2.y) * (p1.y - p2.y);
}

int round_coord(double c)
{
    // from the problem statement: "Coordinates are floating point values with at most decimals"
    return llround(c * 100);
}

// divide and conquer finding the closest pair of points
// detailed explanation can be found in chapter 5.4 in Algorithm Design book 1st edition by Kleinberg and tardos
// T(n)<=2T(n/2)+cn = O(nlgn)
pair<point, point> pecah_belah_dan_kuasai(vector<point> &px, vector<point> &py)
{
    int n = px.size();
    if (n <= 3)
    { // base case, find closest pair by measuring all pairwise distances
        pair<point, point> best_pair;
        double min_dist = 1e15;
        for (int i = 0; i < n; i++)
        {
            for (int j = i + 1; j < n; j++)
            {
                auto a = px[i];
                auto b = px[j];
                auto dist = euclidean(a, b);
                if (dist < min_dist)
                {
                    min_dist = dist;
                    best_pair = {a, b};
                }
            }
        }

        return best_pair;
    }

    // qx and qy are first n/2 points of px (sorted by x-coordinate and y-coordinate respectively)
    int mid = n / 2;
    vector<point> qx(px.begin(), px.begin() + mid);
    // rx and ry are last n/2 points of px (sorted by x-coordinate and y-coordinate respectively)
    vector<point> rx(px.begin() + mid, px.begin() + n);

    for (auto p : qx)
    {
        q_points.set(p.id);
    }

    vector<point> qy;
    vector<point> ry;

    for (auto p : py)
    {
        if (q_points.test(p.id))
        {
            qy.push_back(p);
        }
        else
        {
            ry.push_back(p);
        }
    }

    q_points.reset();

    // divide and conquer on this q points and r points
    auto [q_one, q_two] = pecah_belah_dan_kuasai(qx, qy); // best pair of point on q points
    auto [r_one, r_two] = pecah_belah_dan_kuasai(rx, ry); // best pair of point on r points

    auto dist_q = euclidean(q_one, q_two); // distance of best pair (q_one, q_two)
    auto dist_r = euclidean(r_one, r_two); // distance of best pair (r_one, r_two)
    auto delta = min(dist_q, dist_r);

    vector<point> s; // all points within distance delta of line x=x_star, this s points is sorted by its y-coordinate

    for (auto p : py) // O(n)
    {
        s.push_back(p);
    }

    double x_star = qx.back().x;

    int s_size = 0;
    for (int i = 0; i < s.size(); i++) // O(n)
    {                                  // only retains all s points within distance delta from line x=x_star 
        auto p = s[i];
        point x_star_line = point{p.id, x_star, p.y};
        auto p_xstar_dist = euclidean(p, x_star_line);
        if (p_xstar_dist < delta)
        {
            s[s_size] = p;
            s_size++;
        }
    }

    pair<point, point> best_s_pair;
    double min_s_dist = 1e15;
    // for each points in s, compute distance from this point to each of next 15 points in s
    // s already sorted by y-coordinate
    for (int i = 0; i < s_size; i++) // O(n)
    {
        for (int j = i + 1; j < min(s_size, i + 15); j++)
        {
            auto s_one = s[i];
            auto s_two = s[j];
            auto s_dist = euclidean(s_one, s_two);

            if (s_dist < min_s_dist)
            {
                min_s_dist = s_dist;
                best_s_pair = {s_one, s_two};
            }
        }
    }

    if (min_s_dist < delta)
    { // best_s_pair is the closest pair in current p points
        return best_s_pair;
    }
    else if (dist_q < dist_r)
    { // (q_one, q_two) is the closest pair in current p points
        return {q_one, q_two};
    }
    return {r_one, r_two};
}

// // // TLE gara gara counting sort
// // O(n+k) counting sort, k = (max_y_coord - min_y_coord)*100
// vector<point> counting_sort(vector<point> &s)
// {

//     if (s.empty())
//     {
//         return {};
//     }
//     int l = 1e5;
//     int r = -1e5;
//     for (auto p : s)
//     {
//         auto py = round_coord(p.y);
//         if (py < l)
//         {
//             l = round_coord(p.y);
//         }
//         if (py > r)
//         {
//             r = round_coord(p.y);
//         }
//     }

//     int k = r - l + 1;

//     vector<double> freq(k, 0);

//     int n = s.size();
//     // count ferquency of y-coordinates
//     for (int i = 0; i < n; i++)
//     {
//         auto siy = round_coord(s[i].y);
//         ++freq[siy - l];
//     }

//     // prefix sums
//     for (int i = 1; i < k; i++)
//     {
//         freq[i] = freq[i - 1] + freq[i];
//     }

//     // place s[i] in the correct sorted position
//     vector<point> sorted(n);
//     for (int i = n - 1; i >= 0; i--)
//     {
//         auto siy = round_coord(s[i].y);
//         sorted[freq[siy - l] - 1] = s[i];
//         freq[siy - l]--;
//     }
//     return sorted;
// }

// // divide and conquer finding the closest pair of points
// // detailed explanation can be found in chapter 5.4 in Algorithm Design book 1st edition by Kleinberg and tardos
// // T(n)<=2T(n/2)+cn = O(nlgn)
// pair<point, point> pecah_belah_dan_kuasai(vector<point> &px, vector<point> &py)
// {
//     int n = px.size();
//     if (n <= 3)
//     { // base case, find closest pair by measuring all pairwise distances
//         pair<point, point> best_pair;
//         double min_dist = 1e15;
//         for (int i = 0; i < n; i++)
//         {
//             for (int j = i + 1; j < n; j++)
//             {
//                 auto a = px[i];
//                 auto b = px[j];
//                 auto dist = euclidean(a, b);
//                 if (dist < min_dist)
//                 {
//                     min_dist = dist;
//                     best_pair = {a, b};
//                 }
//             }
//         }

//         return best_pair;
//     }

//     // qx and qy are first n/2 points of px and py
//     vector<point> qx(px.begin(), px.begin() + n / 2);
//     vector<point> qy(py.begin(), py.begin() + n / 2);

//     // rx and ry are last n/2 points of px and py
//     vector<point> rx(px.begin() + n / 2, px.begin() + n);
//     vector<point> ry(py.begin() + n / 2, py.begin() + n);

//     // divide and conquer on this q points and r points
//     auto [q_one, q_two] = pecah_belah_dan_kuasai(qx, qy); // best pair of point on q points
//     auto [r_one, r_two] = pecah_belah_dan_kuasai(rx, ry); // best pair of point on r points

//     auto dist_q = euclidean(q_one, q_two); // distance of best pair (q_one, q_two)
//     auto dist_r = euclidean(r_one, r_two); // distance of best pair (r_one, r_two)
//     auto delta = min(dist_q, dist_r);

//     double x_star = qx.back().x;

//     vector<point> s; // all points within distance delta of line x=x_star
//     for (auto p : px)
//     { // insert all points within distance delta of line x=x_star into vector s
//         point x_star_line = point{x_star, p.y};
//         auto p_xstar_dist = euclidean(p, x_star_line);
//         if (p_xstar_dist < delta)
//         {
//             s.push_back(p);
//         }
//     }

//     // sort s by y-coordinate
//     s = counting_sort(s);

//     pair<point, point> best_s_pair;
//     int s_size = s.size();
//     double min_s_dist = 1e15;
//     // for each points in s, compute distance from sy to each of next 15 points in sy
//     for (int i = 0; i < s_size; i++)
//     {
//         for (int j = i + 1; j < min(s_size, i + 15); j++)
//         {
//             auto s_one = s[i];
//             auto s_two = s[j];
//             auto s_dist = euclidean(s_one, s_two);

//             if (s_dist < min_s_dist)
//             {
//                 min_s_dist = s_dist;
//                 best_s_pair = {s_one, s_two};
//             }
//         }
//     }

//     if (min_s_dist < delta)
//     { // best_s_pair is the closest pair in current p points
//         return best_s_pair;
//     }
//     else if (dist_q < dist_r)
//     { // (q_one, q_two) is the closest pair in current p points
//         return {q_one, q_two};
//     }
//     return {r_one, r_two};
// }

pair<point, point> closest_pair(vector<point> &points)
{
    vector<point> px = points;
    vector<point> py = points;
    sort(px.begin(), px.end(), [](point a, point b)
         { return a.x < b.x; }); // O(nlgn)
    sort(py.begin(), py.end(), [](point a, point b)
         { return a.y < b.y; });
    return pecah_belah_dan_kuasai(px, py);
}

int main()
{
    cout << fixed << setprecision(2);
    int n;
    while (cin >> n)
    {
        if (n == 0)
        {
            break;
        }
        vector<point> points;
        for (int i = 0; i < n; i++)
        {
            double x, y;
            cin >> x >> y;
            points.push_back({i, x, y});
        }
        auto [p_one, p_two] = closest_pair(points);
        cout << p_one.x << " " << p_one.y << " " << p_two.x << " " << p_two.y << endl;
    }
}