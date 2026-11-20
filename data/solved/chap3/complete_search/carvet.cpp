#include <bits/stdc++.h>
using namespace std;
const int dir[4][4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

// O(4^(max(m,n))). backtracking recursion tree, 4 children nodes each node, with height max(m,n). m=number of rows,n=number of columns. kita cuma bisa lompat ke 2 sel sebelah (kiri & kanan) / (atas & bawah) setiap mobil yang digeser..
void backtrack(vector<vector<int>> &grid, int i, int j, vector<int> moved_cars, vector<int> &ans, vector<bool> &used_cars, pair<int, int> desired_loc)
{

    if (i == desired_loc.first - 1 && j == desired_loc.second - 1)
    {
        if (moved_cars.size() < ans.size())
        {
            ans = moved_cars;
        }
        else if (ans.size() == 0)
        {
            ans = moved_cars;
        }
        return;
    }

    int n = grid.size();
    int m = grid[0].size();

    for (auto d : dir)
    {
        int ndr = d[0] + i;
        int ndc = d[1] + j;

        if (ndr >= n || ndr < 0 || ndc >= m || ndc < 0)
        {
            continue;
        }
        int cur_car = grid[ndr][ndc];
        if (cur_car == -2 || used_cars[cur_car])
        {
            continue;
        }
        bool valid = false;

        int ndr2 = 2 * d[0] + i;
        int ndc2 = 2 * d[1] + j;
        if (ndr2 >= n || ndr2 < 0 || ndc2 >= m || ndc2 < 0)
        {
            continue;
        }
        if (grid[ndr2][ndc2] == cur_car)
        {
            valid = true;
        }

        if (!valid)
        {
            continue;
        }

        grid[i][j] = cur_car;
        grid[ndr2][ndc2] = -1;
        used_cars[cur_car] = true;
        moved_cars.push_back(cur_car);
        backtrack(grid, ndr2, ndc2, moved_cars, ans, used_cars, desired_loc);
        grid[i][j] = -1;
        grid[ndr2][ndc2] = cur_car;
        used_cars[cur_car] = false;
        moved_cars.pop_back();
    }
}

int main()
{
    int m, n;
    cin >> m >> n;

    vector<vector<int>> grid(m, vector<int>(n));
    int qr, qc;
    for (int i = 0; i < m; i++)
    {
        for (int j = 0; j < n; j++)
        {
            cin >> grid[i][j];
            if (grid[i][j] == -1)
            {
                qr = i;
                qc = j;
            }
        }
    }

    int r, c;
    cin >> r >> c;

    vector<bool> used_cars(62500);
    vector<int> ans;
    vector<int> moved_cars;
    backtrack(grid, qr, qc, moved_cars, ans, used_cars, {r, c});

    if (ans.size() == 0)
    {
        cout << "impossible" << endl;
        return 0;
    }

    for (int i = 0; i < ans.size(); i++)
    {
        cout << ans[i];
        if (i < ans.size() - 1)
        {
            cout << " ";
        }
    }
}

// tle
// const int dir[4][4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

// void backtrack(vector<vector<int>> &grid, int last_car,
//                vector<int> &cur_moved_cars, vector<vector<int>> &moved_cars, vector<bool> &used_cars, pair<int, int> desired_loc)
// {

//     if (last_car != -1 && used_cars[last_car])
//     {
//         return;
//     }
//     if (last_car != -1)
//     {
//         used_cars[last_car] = true;
//     }

//     if (grid[desired_loc.first - 1][desired_loc.second - 1] == -1)
//     {

//         moved_cars.push_back(cur_moved_cars);
//         return;
//     }

//     int n = grid.size();
//     int m = grid[0].size();
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (grid[i][j] == -1 || grid[i][j] == -2 || grid[i][j] == last_car)
//             {
//                 continue;
//             }

//             int cur_car = grid[i][j];
//             pair<int, int> other_car_cell;

//             bool horizontal = false;
//             for (auto d : dir)
//             {
//                 int ndr = d[0] + i;
//                 int ndc = d[1] + j;
//                 if (ndr >= n || ndr < 0 || ndc >= m || ndc < 0)
//                 {
//                     continue;
//                 }
//                 if (grid[ndr][ndc] == cur_car)
//                 {
//                     if (d[0] == 0)
//                     {
//                         horizontal = true;
//                     }
//                     other_car_cell = {ndr, ndc};
//                 }
//             }

//             for (auto d : dir)
//             {
//                 if (horizontal && d[0] != 0)
//                 {
//                     continue;
//                 }
//                 if (!horizontal && d[1] != 0)
//                 {
//                     continue;
//                 }
//                 int ndr = d[0] + i;
//                 int ndc = d[1] + j;
//                 if (ndr >= n || ndr < 0 || ndc >= m || ndc < 0)
//                 {
//                     continue;
//                 }

//                 if (grid[ndr][ndc] == -1)
//                 {
//                     grid[ndr][ndc] = cur_car;
//                     grid[i][j] = cur_car;
//                     grid[other_car_cell.first][other_car_cell.second] = -1;
//                     cur_moved_cars.push_back(cur_car);
//                     backtrack(grid, cur_car, cur_moved_cars, moved_cars, used_cars, desired_loc);
//                     grid[ndr][ndc] = -1;
//                     grid[i][j] = cur_car;
//                     grid[other_car_cell.first][other_car_cell.second] = cur_car;
//                     cur_moved_cars.pop_back();
//                 }
//             }
//         }
//     }

//     if (last_car != -1)
//     {
//         used_cars[last_car] = false;
//     }
// }

// int main()
// {
//     int m, n;
//     cin >> m >> n;

//     vector<vector<int>> grid(m, vector<int>(n));

//     for (int i = 0; i < m; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> grid[i][j];
//         }
//     }

//     int r, c;
//     cin >> r >> c;
//     vector<int> cur_moved_cars;
//     vector<vector<int>> moved_cars;
//     vector<bool> used_cars(62500);
//     backtrack(grid, -1, cur_moved_cars, moved_cars, used_cars, {r, c});

//     if (moved_cars.size() == 0)
//     {
//         cout << "impossible" << endl;
//         return 0;
//     }
//     sort(moved_cars.begin(), moved_cars.end());
//     auto ans = moved_cars[0];
//     for (int i = 0; i < ans.size(); i++)
//     {
//         cout << ans[i];
//         if (i < ans.size() - 1)
//         {
//             cout << " ";
//         }
//     }
// }

// tle
// const int dir[4][4] = {{0, 1}, {1, 0}, {-1, 0}, {0, -1}};

// void backtrack(vector<vector<int>> grid, int last_car,
//                vector<int> cur_moved_cars, vector<vector<int>> &moved_cars, vector<bool> used_cars, pair<int, int> desired_loc)
// {

//     if (grid[desired_loc.first - 1][desired_loc.second - 1] == -1)
//     {

//         moved_cars.push_back(cur_moved_cars);
//         return;
//     }

//     int n = grid.size();
//     int m = grid[0].size();
//     for (int i = 0; i < n; i++)
//     {
//         for (int j = 0; j < m; j++)
//         {
//             if (grid[i][j] == -1 || grid[i][j] == -2 || used_cars[grid[i][j]])
//             {
//                 continue;
//             }

//             int cur_car = grid[i][j];
//             pair<int, int> other_car_cell;

//             bool horizontal = false;
//             for (auto d : dir)
//             {
//                 int ndr = d[0] + i;
//                 int ndc = d[1] + j;
//                 if (ndr >= n || ndr < 0 || ndc >= m || ndc < 0)
//                 {
//                     continue;
//                 }
//                 if (grid[ndr][ndc] == cur_car)
//                 {
//                     if (d[0] == 0)
//                     {
//                         horizontal = true;
//                     }
//                     other_car_cell = {ndr, ndc};
//                 }
//             }

//             for (auto d : dir)
//             {
//                 if (horizontal && d[0] != 0)
//                 {
//                     continue;
//                 }
//                 if (!horizontal && d[1] !=0) {
//                     continue;
//                 }
//                 int ndr = d[0] + i;
//                 int ndc = d[1] + j;
//                 if (ndr >= n || ndr < 0 || ndc >= m || ndc < 0)
//                 {
//                     continue;
//                 }

//                 if (grid[ndr][ndc] == -1)
//                 {
//                     grid[ndr][ndc] = cur_car;
//                     grid[i][j] = cur_car;
//                     grid[other_car_cell.first][other_car_cell.second] = -1;
//                     cur_moved_cars.push_back(cur_car);
//                     used_cars[cur_car] = true;
//                     backtrack(grid, cur_car, cur_moved_cars, moved_cars, used_cars, desired_loc);
//                     grid[ndr][ndc] = -1;
//                     grid[i][j] = cur_car;
//                     grid[other_car_cell.first][other_car_cell.second] = cur_car;
//                     cur_moved_cars.pop_back();
//                     used_cars[cur_car] = false;
//                 }
//             }
//         }
//     }
// }

// int main()
// {
//     int m, n;
//     cin >> m >> n;

//     vector<vector<int>> grid(m, vector<int>(n));

//     for (int i = 0; i < m; i++)
//     {
//         for (int j = 0; j < n; j++)
//         {
//             cin >> grid[i][j];
//         }
//     }

//     int r, c;
//     cin >> r >> c;
//     vector<int> cur_moved_cars;
//     vector<vector<int>> moved_cars;
//     vector<bool> used_cars(62500);
//     backtrack(grid, -1, cur_moved_cars, moved_cars, used_cars, {r, c});

//     if (moved_cars.size() == 0)
//     {
//         cout << "impossible" << endl;
//         return 0;
//     }

//     sort(moved_cars.begin(), moved_cars.end(), [](vector<int> a, vector<int> b)
//          { return a.size() < b.size(); });
//     auto ans = moved_cars[0];
//     for (int i = 0; i < ans.size(); i++)
//     {
//         cout << ans[i];
//         if (i < ans.size() - 1)
//         {
//             cout << " ";
//         }
//     }
// }