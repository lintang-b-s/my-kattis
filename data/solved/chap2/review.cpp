#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/review?tab=metadata

// typedef long long valType;
// struct emStType
// {
//     valType skill;
//     int employeeId;
// };
// class SegmentTree
// {
// private:
//     int n;
//     vector<emStType> A, st, lazy;
//     bool minimum;

//     int leftChild(int parent)
//     {
//         // go to left child
//         return parent << 1;
//     }

//     int rightChild(int parent)
//     {
//         return (parent << 1) + 1;
//     }

//     emStType conquer(emStType a, emStType b)
//     {
//         if (a.skill == -1)
//         {
//             return b;
//         }
//         if (b.skill == -1)
//         {
//             return a;
//         }
//         if (minimum)
//         {
//             if (a.skill < b.skill)
//             {
//                 return a;
//             }
//             else
//             {
//                 return b;
//             }
//         }

//         if (a.skill > b.skill)
//         {
//             return a;
//         }
//         else
//         {
//             return b;
//         }
//     }

//     void build(int parent, int L, int R)
//     { // O(n)
//         if (L == R)
//         {
//             st[parent] = A[L];
//         }
//         else
//         {
//             int mid = (L + R) / 2;
//             build(leftChild(parent), L, mid);
//             build(rightChild(parent), mid + 1, R);
//             st[parent] = conquer(st[leftChild(parent)], st[rightChild(parent)]);
//         }
//     }

//     void propagate(int parent, int L, int R)
//     {
//         if (lazy[parent].skill != -1)
//         { // parent has a lazy flag
//             st[parent] = lazy[parent];

//             if (L != R)
//             {
//                 lazy[leftChild(parent)] = lazy[rightChild(parent)] = lazy[parent];
//             }
//             else
//             {
//                 A[L] = lazy[parent];
//             }
//             lazy[parent].skill = -1;
//         }
//     }

//     emStType RMQ(int parent, int L, int R, int i, int j)
//     { // O(log N)
//         propagate(parent, L, R);
//         if (i > j)
//         {
//             return emStType{-1, -1};
//         }
//         if ((i <= L) && (j >= R))
//         {
//             return st[parent];
//         }

//         int mid = (L + R) / 2;
//         return conquer(RMQ(leftChild(parent), L, mid, i, min(mid, j)),
//                        RMQ(rightChild(parent), mid + 1, R, max(i, mid + 1), j));
//     }

//     void update(int parent, int L, int R, int i, int j, emStType val)
//     {
//         propagate(parent, L, R);

//         if (i > j)
//         {
//             return;
//         }
//         if ((i <= L) && (j >= R))
//         {
//             lazy[parent] = val;
//             propagate(parent, L, R);
//         }
//         else
//         {
//             int mid = (L + R) / 2;
//             update(leftChild(parent), L, mid, i, min(mid, j), val);
//             update(rightChild(parent), mid + 1, R, max(i, mid + 1), j, val);
//             emStType leftSubTree = (lazy[leftChild(parent)].skill != -1) ? lazy[leftChild(parent)] : st[leftChild(parent)];
//             emStType rightSubTree = (lazy[rightChild(parent)].skill != -1) ? lazy[rightChild(parent)] : st[rightChild(parent)];
//             st[parent] = conquer(leftSubTree, rightSubTree);
//         }
//     }

// public:
//     SegmentTree(int size, bool isMinimum) : n(size), A(n), st(4 * n), lazy(4 * n, emStType{-1, -1}), minimum(isMinimum) {}

//     SegmentTree(vector<emStType> &initialA, bool isMinimum) : SegmentTree(initialA.size(), isMinimum)
//     {
//         A = initialA;
//         build(1, 0, n - 1);
//     }

//     void update(int i, int j, emStType val)
//     {
//         update(1, 0, n - 1, i, j, val);
//     }

//     emStType RMQ(int i, int j)
//     { // get index of max/min value over arr[i], arr[i+1], ... ,arr[j]
//         return RMQ(1, 0, n - 1, i, j);
//     }
// };

typedef long long valType;
class SegmentTree
{
private:
    int n;
    vector<valType> A, st, lazy;
    bool minimum;

    int leftChild(int parent)
    {
        // go to left child
        return parent << 1;
    }

    int rightChild(int parent)
    {
        return (parent << 1) + 1;
    }

    valType conquer(valType a, valType b)
    {
        if (a == -1)
        {
            return b;
        }
        if (b == -1)
        {
            return a;
        }
        return a + b;
    }

    void build(int parent, int L, int R)
    { // O(n)
        if (L == R)
        {
            st[parent] = A[L];
        }
        else
        {
            int mid = (L + R) / 2;
            build(leftChild(parent), L, mid);
            build(rightChild(parent), mid + 1, R);
            st[parent] = conquer(st[leftChild(parent)], st[rightChild(parent)]);
        }
    }

    void propagate(int parent, int L, int R)
    {
        if (lazy[parent] != -1)
        { // parent has a lazy flag
            st[parent] = lazy[parent];

            if (L != R)
            {
                lazy[leftChild(parent)] = lazy[rightChild(parent)] = lazy[parent];
            }
            else
            {
                A[L] = lazy[parent];
            }
            lazy[parent] = -1;
        }
    }

    valType RSQ(int parent, int L, int R, int i, int j)
    { // O(log N)
        propagate(parent, L, R);
        if (i > j)
        {
            return 0;
        }
        if ((i <= L) && (j >= R))
        {
            return st[parent];
        }

        int mid = (L + R) / 2;
        valType leftChildVal = RSQ(leftChild(parent), L, mid, i, min(mid, j));
        valType rightChildVal = RSQ(rightChild(parent), mid + 1, R, max(i, mid + 1), j);

        valType sumval = leftChildVal + rightChildVal;
        return sumval;
    }

    void update(int parent, int L, int R, int i, int j, valType val)
    {
        propagate(parent, L, R);

        if (i > j)
        {
            return;
        }
        if ((i <= L) && (j >= R))
        {
            lazy[parent] = val;
            propagate(parent, L, R);
        }
        else
        {
            int mid = (L + R) / 2;
            update(leftChild(parent), L, mid, i, min(mid, j), val);
            update(rightChild(parent), mid + 1, R, max(i, mid + 1), j, val);
            valType leftSubTree = (lazy[leftChild(parent)] != -1) ? lazy[leftChild(parent)] : st[leftChild(parent)];
            valType rightSubTree = (lazy[rightChild(parent)] != -1) ? lazy[rightChild(parent)] : st[rightChild(parent)];
            st[parent] = conquer(leftSubTree, rightSubTree);
        }
    }

public:
    SegmentTree(int size, bool isMinimum) : n(size), A(n), st(4 * n), lazy(4 * n, -1), minimum(isMinimum) {}

    SegmentTree(vector<valType> &initialA, bool isMinimum) : SegmentTree(initialA.size(), isMinimum)
    {
        A = initialA;
        build(1, 0, n - 1);
    }

    void update(int i, int j, valType val)
    {
        update(1, 0, n - 1, i, j, val);
    }

    valType RSQ(int i, int j)
    {
        return RSQ(1, 0, n - 1, i, j);
    }
};

typedef long long ll;

struct Employee
{
    int id;
    int manager;
    int technicalSkill;
    ll writingTime;
    ll reviewTime;
    vector<Employee *> childrens;
};

void dfs(Employee *em, int techinicalSkill, ll &sum)
{
    if (em->childrens.size() == 0)
    {
        return;
    }
    for (auto &child : em->childrens)
    {
        if (child->technicalSkill < techinicalSkill)
        {
            sum += child->reviewTime;
        }
        dfs(child, techinicalSkill, sum);
    }
};

// vector<Employee *> employeSkillSorted;

vector<int> timeIn, timeOut;
int timer = 0;

// WA, karena suatu bawahan bisa direview oleh beberapa atasan (gak cuma satu) dengan skill higher than skill bawahanini
// int preorderSegmentTree(Employee *em, vector<Employee *> &ems, SegmentTree &st)
// {
//     auto getId = [&](valType val)
//     {
//         return lower_bound(employeSkillSorted.begin(), employeSkillSorted.end(), val) - employeSkillSorted.begin(); // O(log E)
//     };
//     // get least/minimum technical skill val ancestor that greater than current em techincal skill
//     int newId = getId(em->technicalSkill);

//     auto leftLeastTsGreaterThan = st.RMQ(newId, ems.size() - 1); // O(log E)
//     if (leftLeastTsGreaterThan.skill != INT_MAX)
//     {
//         auto &higherEm = ems[leftLeastTsGreaterThan.employeeId];
//         if (higherEm->id + 1 != em->manager)
//         {
//             higherEm->writingTime += em->reviewTime;
//         }
//     }
//     st.update(newId, newId, emStType{(valType)em->technicalSkill, em->id}); // O(log E)

//     if (em->childrens.size() == 0)
//     {
//         em->writingTime = 0;
//         return 0;
//     }
//     ll childrensWritingTime = 0;
//     for (auto &child : em->childrens)
//     {

//         if (child->technicalSkill < em->technicalSkill)
//         {
//             childrensWritingTime += child->reviewTime;
//         }
//         childrensWritingTime += preorderSegmentTree(child, ems, st);
//     }

//     em->writingTime += childrensWritingTime;
//     return em->writingTime;
// }

void dfs2(int emId, vector<Employee *> &ems)
{
    timeIn[emId] = timer++;
    for (auto child : ems[emId]->childrens)
    {
        dfs2(child->id, ems);
    }
    timeOut[emId] = timer - 1;
}

int main()
{
    int E;
    cin >> E;

    timeIn.resize(E);
    timeOut.resize(E);
    Employee *root;

    vector<Employee *> employees;
    map<int, vector<int>> employeeSameSkillGroups; // bisa aja ada beberapa employees dengan same skill

    for (int i = 0; i < E; i++)
    {
        int m, ts;
        ll rt;
        cin >> m >> ts >> rt;

        Employee *em = new Employee();
        em->id = i;
        em->manager = m;
        em->technicalSkill = ts;
        em->reviewTime = rt;

        employees.push_back(em);
        // employeSkillSorted.push_back(em);
        employeeSameSkillGroups[ts].push_back(i);
    }

    for (int i = 0; i < E; i++)
    {

        auto &em = employees[i];
        if (em->manager != -1)
        {
            employees[em->manager - 1]->childrens.push_back(em);
        }
        else
        {
            root = em;
        }
    }

    dfs2(root->id, employees);

    vector<valType>
        lefts(E, 0);
    SegmentTree st(lefts, false);

    vector<ll> emWritingTime(E, 0);
    for (auto [skill, emIds] : employeeSameSkillGroups)
    { // O(E log E)
        for (auto emId : emIds)
        {                                                              // employess dengan same skill, dapet writing time yang sama dari bawahan-bawahannya
            emWritingTime[emId] = st.RSQ(timeIn[emId], timeOut[emId]); // O(log E)
        }

        for (auto emId : emIds)
        {
            st.update(timeIn[emId], timeIn[emId], employees[emId]->reviewTime); // O(log E)
        }
    }
    for (auto wt : emWritingTime)
    {
        cout << wt << endl;
    }

    // sort(employeSkillSorted.begin(), employeSkillSorted.end(), [&](Employee *a, Employee *b)
    //      { return a->technicalSkill < b->technicalSkill; });

    // vector<valType>
    //     lefts(E, 0);
    // SegmentTree st(lefts, false);

    // int left = 0;

    // vector<ll> empWritingTime(E, 0);

    // WA hidden test case 9
    // for (int i = 0; i < E; i++)
    // {
    //     auto emp = employeSkillSorted[i];

    //     while (left < i)
    //     {
    //         auto empPrev = employeSkillSorted[left];
    //         int empPrevTimeIn = timeIn[empPrev->id];
    //         st.update(empPrevTimeIn, empPrevTimeIn, empPrev->reviewTime);
    //         left++;
    //     }

    //     int empTimeIn = timeIn[emp->id];
    //     int empTimeOut = timeOut[emp->id];
    //     empWritingTime[emp->id] = st.RSQ(empTimeIn, empTimeOut);
    // }

    // for (auto wt : empWritingTime)
    // {
    //     cout << wt << endl;
    // }
    // WA
    // optimasi: pake trik segment tree buat cari least value greather than current value & to the left of current value
    // + pre order traversal tree nya

    // vector<emStType> lefts(E, emStType{(valType)INT_MAX, -1});
    // SegmentTree st(lefts, true);

    // WA
    // sort(employeSkillSorted.begin(), employeSkillSorted.end());

    // preorderSegmentTree(root, employees, st);

    // for (auto em : employees)
    // {
    //     cout << em->writingTime << "\n";
    // }

    // naive approach got TLE
    // for (int i = 0; i < E; i++)
    // { // O(E^2)
    //     auto em = employees[i];
    //     ll totalWritingReviewTime = 0;
    //     dfs(em, em->technicalSkill, totalWritingReviewTime);
    //     cout << totalWritingReviewTime << "\n";
    // }
}
