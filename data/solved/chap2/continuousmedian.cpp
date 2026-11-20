#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/continuousmedian?tab=metadata
typedef unsigned long long ull;

struct BSTVertex
{
    BSTVertex *parent;
    BSTVertex *left;
    BSTVertex *right;
    ull key;
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

    BSTVertex *insert(BSTVertex *T, ull v)
    {
        if (T == NULL)
        {
            T = new BSTVertex;
            T->key = v;
            T->parent = T->right = T->left = NULL;
            T->height = 0;
            T->size = 1;
        }
        else if (v < T->key)
        {
            T->left = insert(T->left, v);
            T->left->parent = T;
        }
        else
        {
            T->right = insert(T->right, v);
            T->right->parent = T;
        }

        T = rebalance(T);
        return T;
    }

    ull findMin(BSTVertex *T)
    {
        if (T == NULL)
        {
            return (ull)0;
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

    ull findMax(BSTVertex *T)
    {
        if (T == NULL)
        {
            return (ull)0;
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

    BSTVertex *search(BSTVertex *T, ull v)
    {
        if (T == NULL)
        {
            return T;
        }
        else if (v < T->key)
        {
            return search(T->left, v);
        }
        else if (T->key == v)
        {
            return T;
        }
        else
        {
            return search(T->right, v);
        }
    }

    ull successor(BSTVertex *T)
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
            return parent == NULL ? (ull)0 : parent->key;
        }
    }

    ull predecessor(BSTVertex *T)
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

            return parent == NULL ? (ull)0 : parent->key;
        }
    }

    BSTVertex *remove(BSTVertex *T, ull v)
    {
        if (T == NULL)
        {
            return T;
        }

        if (T->key == v)
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
                ull successorV = successor(T);
                T->key = successorV;
                T->right = remove(T->right, successorV);
            }
        }
        else if (v < T->key)
        {
            T->left = remove(T->left, v);
        }
        else
        {
            T->right = remove(T->right, v);
        }

        if (T != NULL)
        {
            T = rebalance(T);
        }

        return T;
    }

    int getLeftSubtreeSize(BSTVertex *T, ull key)
    {
        if (T == NULL)
            return 0;

        if (key <= T->key)
        {
            return getLeftSubtreeSize(T->left, key);
        }
        else
        {
            return getSize(T->left) + 1 + getLeftSubtreeSize(T->right, key);
        }
    }

    void insertNode(ull v) { root = insert(root, v); };
    void removeNode(ull v) { root = remove(root, v); };
    BSTVertex *searchNode(ull v)
    {
        return search(root, v);
    }

    int getRank(ull v)
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
};

int main()
{
    int t;
    cin >> t;
    while (t--)
    {

        AVL *tree = new AVL();
        int N;
        cin >> N;
        ull cotinuousMedian = 0;
        for (int i = 0; i < N; i++)
        {
            int a;
            cin >> a;
            tree->insertNode(a);
            if ((i + 1) % 2 == 0)
            {
                int midOneId = ((i + 1) / 2) + 1;
                int midTwoId = ((i + 1) / 2);
                ull sum = tree->getNodeOfOrder(midOneId)->key + tree->getNodeOfOrder(midTwoId)->key; // O(logN), N=currentTreeSize
                ull median = floor(sum / 2);
                cotinuousMedian += median;
            }
            else
            {
                int midId = ((i + 1) / 2) + 1;
                ull median = tree->getNodeOfOrder(midId)->key; // O(logN), N=currentTreeSize
                cotinuousMedian += median;
            }
        }

        cout << cotinuousMedian << endl;
    }
}