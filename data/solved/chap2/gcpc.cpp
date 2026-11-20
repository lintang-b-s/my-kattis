#include <bits/stdc++.h>
using namespace std;

struct teamScore
{
    int solved;
    int penalty;
    int team;
};

// https://open.kattis.com/problems/gcpc?tab=metadata

// avl tree code reference: https://github.com/stevenhalim/cpbook-code/blob/master/ch2/nonlineards/AVL.cpp
struct BSTVertex
{
    BSTVertex *parent;
    BSTVertex *left;
    BSTVertex *right;
    teamScore key;
    int height;
    int size;
};

class AVL
{
protected:
    BSTVertex *root;

public:
    AVL() { root = NULL; }
    int height(BSTVertex *T)
    {
        return T == NULL ? -1 : T->height;
    }

    int getSize(BSTVertex *T)
    {
        return T == NULL ? 0 : T->size;
    }

    BSTVertex *rotateLeft(BSTVertex *T)
    {
        BSTVertex *y = T->right;
        y->parent = T->parent;
        T->parent = y;
        T->right = y->left;
        if (y->left != NULL)
        {
            y->left->parent = T;
        }
        y->left = T;

        T->height = max(height(T->left), height(T->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        T->size = getSize(T->left) + getSize(T->right) + 1;
        y->size = getSize(y->left) + getSize(y->right) + 1;

        return y;
    }

    BSTVertex *rotateRight(BSTVertex *T)
    {
        BSTVertex *y = T->left;
        y->parent = T->parent;
        T->parent = y;
        T->left = y->right;
        if (y->right != NULL)
        {
            y->right->parent = T;
        }
        y->right = T;

        T->height = max(height(T->left), height(T->right)) + 1;
        y->height = max(height(y->left), height(y->right)) + 1;

        T->size = getSize(T->left) + getSize(T->right) + 1;
        y->size = getSize(y->left) + getSize(y->right) + 1;

        return y;
    }

    BSTVertex *rebalance(BSTVertex *T)
    {
        int balanceFactorT = height(T->left) - height(T->right);
        if (balanceFactorT == 2)
        {
            int balanceFactorBelow = height(T->left->left) - height(T->left->right);
            if (balanceFactorBelow >= 1)
            {
                T = rotateRight(T);
            }
            else
            {
                T->left = rotateLeft(T->left);
                T = rotateRight(T);
            }
        }
        else if (balanceFactorT == -2)
        {
            int balanceFactorBelow = height(T->right->left) - height(T->right->right);
            if (balanceFactorBelow <= 0)
            {
                T = rotateLeft(T);
            }
            else
            {
                T->right = rotateRight(T->right);
                T = rotateLeft(T);
            }
        }

        T->height = max(height(T->left), height(T->right)) + 1;
        T->size = getSize(T->left) + getSize(T->right) + 1;

        return T;
    }

    BSTVertex *insert(BSTVertex *T, teamScore v)
    {
        if (T == NULL)
        {
            T = new BSTVertex;
            T->key = v;
            T->parent = T->right = T->left = NULL;
            T->height = 0;
            T->size = 1;
        }
        else if (v.solved < T->key.solved)
        {
            T->left = insert(T->left, v);
            T->left->parent = T;
        }
        else if (v.solved > T->key.solved)
        {
            T->right = insert(T->right, v);
            T->right->parent = T;
        }
        else
        {
            if (v.penalty < T->key.penalty)
            {
                T->left = insert(T->left, v);
                T->left->parent = T;
            }
            else if (v.penalty > T->key.penalty)
            {
                T->right = insert(T->right, v);
                T->right->parent = T;
            }
            else
            {
                if (v.team < T->key.team)
                {
                    T->left = insert(T->left, v);
                    T->left->parent = T;
                }
                else
                {
                    T->right = insert(T->right, v);
                    T->right->parent = T;
                }
            }
        }

        T = rebalance(T);
        return T;
    }

    teamScore findMin(BSTVertex *T)
    {
        if (T == NULL)
        {
            return teamScore{0, 0};
        }
        else if (T->left == NULL)
        {
            return T->key;
        }
        else
        {
            return findMin(T->left);
        }
    }

    teamScore findMax(BSTVertex *T)
    {
        if (T == NULL)
        {
            return teamScore{0, 0};
        }
        else if (T->right == NULL)
        {
            return T->key;
        }
        else
        {
            return findMax(T->right);
        }
    }

    BSTVertex *search(BSTVertex *T, teamScore v)
    {
        if (T == NULL)
        {
            return T;
        }
        else if (v.solved < T->key.solved)
        {
            return search(T->left, v);
        }
        else if (T->key.solved == v.solved && T->key.penalty == v.penalty &&
                 T->key.team == v.team)
        {
            return T;
        }
        else if (v.solved > T->key.solved)
        {
            return search(T->right, v);
        }
        else
        {
            if (v.penalty < T->key.penalty)
            {
                return search(T->left, v);
            }
            else if (v.penalty > T->key.penalty)
            {
                return search(T->right, v);
            }
            else
            {
                if (v.team < T->key.team)
                {
                    return search(T->left, v);
                }
                else
                {
                    return search(T->right, v);
                }
            }
        }
    }

    teamScore successor(BSTVertex *T)
    {
        if (T->right != NULL)
        {
            return findMin(T->right);
        }
        else
        {
            BSTVertex *parent = T->parent;
            BSTVertex *cur = T;
            while (parent != NULL && (cur == parent->right))
            {
                cur = parent;
                parent = cur->parent;
            }
            return parent == NULL ? teamScore{0, 0} : parent->key;
        }
    }

    teamScore predecessor(BSTVertex *T)
    {
        if (T->left != NULL)
        {
            return findMax(T->left);
        }
        else
        {
            BSTVertex *parent = T->parent;
            BSTVertex *cur = T;
            while (parent != NULL && (cur == parent->left))
            {
                cur = parent;
                parent = cur->parent;
            }

            return parent == NULL ? teamScore{0, 0} : parent->key;
        }
    }

    BSTVertex *remove(BSTVertex *T, teamScore v)
    {
        if (T == NULL)
        {
            return T;
        }

        if (T->key.solved == v.solved && T->key.penalty == v.penalty &&
            T->key.team == v.team)
        {
            if (T->right == NULL && T->left == NULL)
            {
                T = NULL;
            }
            else if (T->right != NULL && T->left == NULL)
            {
                T->right->parent = T;
                T = T->right;
            }
            else if (T->right == NULL && T->left != NULL)
            {
                T->left->parent = T;
                T = T->left;
            }
            else
            {
                teamScore successorV = successor(T);
                T->key = successorV;
                T->right = remove(T->right, successorV);
            }
        }
        else if (v.solved < T->key.solved)
        {
            T->left = remove(T->left, v);
        }
        else if (v.solved > T->key.solved)
        {
            T->right = remove(T->right, v);
        }
        else
        {
            if (v.penalty < T->key.penalty)
            {
                T->left = remove(T->left, v);
            }
            else if (v.penalty > T->key.penalty)
            {
                T->right = remove(T->right, v);
            }
            else
            {
                if (v.team < T->key.team)
                {
                    T->left = remove(T->left, v);
                }
                else
                {
                    T->right = remove(T->right, v);
                }
            }
        }

        if (T != NULL)
        {
            T = rebalance(T);
        }

        return T;
    }

    int getLeftSubtreeSize(BSTVertex *T, teamScore key)
    {
        if (T == NULL)
        {
            return 0;
        }

        if (key.solved < T->key.solved)
        {
            return getLeftSubtreeSize(T->left, key);
        }
        else if (key.solved > T->key.solved)
        {
            return getSize(T->left) + 1 + getLeftSubtreeSize(T->right, key);
        }
        else
        {
            if (key.penalty < T->key.penalty)
            {
                return getLeftSubtreeSize(T->left, key);
            }
            else if (key.penalty > T->key.penalty)
            {
                return getSize(T->left) + 1 + getLeftSubtreeSize(T->right, key);
            }
            else
            {
                if (key.team <= T->key.team)
                {
                    return getLeftSubtreeSize(T->left, key);
                }
                else
                {
                    return getSize(T->left) + 1 + getLeftSubtreeSize(T->right, key);
                }
            }
        }
    }

    void insertNode(teamScore v) { root = insert(root, v); };
    void removeNode(teamScore v) { root = remove(root, v); };
    BSTVertex *searchNode(teamScore v)
    {
        return search(root, v);
    }

    int getRank(teamScore v)
    {
        return getLeftSubtreeSize(root, v);
    }

    BSTVertex *selectOrder(BSTVertex *T, int k)
    {
        if (T == NULL)
        {
            return NULL;
        }

        int q = getSize(T->left);

        if (q + 1 == k)
        {
            return T;
        }
        else if (k < q + 1)
        {
            return selectOrder(T->left, k);
        }
        else
        {
            return selectOrder(T->right, k - q - 1);
        }
    }

    BSTVertex *getNodeOfOrder(int k)
    {
        return selectOrder(root, k);
    }

    int getTreeSize()
    {
        return root->size;
    }
};

int main()
{
    int n, m;
    cin >> n >> m;

    AVL *tree = new AVL();
    map<int, teamScore> teamScoreMap;

    for (int i = 1; i <= n; i++)
    {
        teamScoreMap[i] = {0, 0, i};
    }
    while (m--)
    {
        int t = 0, p = 0;
        cin >> t >> p;

        auto fvTS = teamScoreMap[t];
        fvTS.solved = -fvTS.solved;
        tree->removeNode(fvTS); // log(N)

        teamScoreMap[t].solved++;
        teamScoreMap[t].penalty += p;
        teamScoreMap[t].team = t;

        teamScore ts;
        ts.solved = -teamScoreMap[t].solved;
        ts.penalty = teamScoreMap[t].penalty;
        ts.team = t;

        tree->insertNode(ts); // log(N)

        teamScore favoriteTeamScore = {0, 0, 1};
        int favoriteTeamRank = -1;
        if (teamScoreMap[1].solved != 0)
        {
            favoriteTeamScore.solved = -teamScoreMap[1].solved;
            favoriteTeamScore.penalty = teamScoreMap[1].penalty;
        }

        favoriteTeamRank = tree->getRank(favoriteTeamScore); // log(N)
        if (teamScoreMap[1].solved == 0)
        {
            favoriteTeamRank = tree->getTreeSize();
        }

        cout << favoriteTeamRank + 1 << endl;
    }
}