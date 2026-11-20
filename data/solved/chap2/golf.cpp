#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

struct BSTVertex
{
    BSTVertex *parent;
    BSTVertex *left;
    BSTVertex *right;
    ll key;
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

    BSTVertex *insert(BSTVertex *T, ll v)
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

    ll findMin(BSTVertex *T)
    {
        if (T == NULL)
        {
            return (ll)0;
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

    ll findMax(BSTVertex *T)
    {
        if (T == NULL)
        {
            return (ll)0;
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

    BSTVertex *search(BSTVertex *T, ll v)
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

    ll successor(BSTVertex *T)
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
            return parent == NULL ? (ll)0 : parent->key;
        }
    }

    ll predecessor(BSTVertex *T)
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

            return parent == NULL ? (ll)0 : parent->key;
        }
    }

    BSTVertex *remove(BSTVertex *T, ll v)
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
                ll successorV = successor(T);
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

    void insertNode(ll v) { root = insert(root, v); };
    void removeNode(ll v) { root = remove(root, v); };
    BSTVertex *searchNode(ll v)
    {
        return search(root, v);
    }

    // explanation of this order statistic (AVL) tree can be found in the CLRS book (Introduction to algorithms) 3rd edition chapter 14.1
    // the book describes augmenting red-black tree for order statistics operations, but it actually similiar for augmenting AVL tree, as both are BST
    // ---  ranking problem ---
    int getLeftSubtreeSize(BSTVertex *T, ll key)
    {
        if (T == NULL)
            return 0;

        if (key <= T->key)
        {
            // key <= T.key, then we recurse on the left subtree, bcs this is a BST
            return getLeftSubtreeSize(T->left, key);
        }
        else
        {
            // key > T.key, then we recurse on the right subtree, bcs this is a BST
            // also we return rank of node key within the subtree rooted at T
            auto r = getSize(T->left) + 1;
            auto c_rank = getLeftSubtreeSize(T->right, key);
            return r + c_rank;
        }
    }

    //
    int getRank(ll v)
    { // O(logn)
        return getLeftSubtreeSize(root, v);
    }

    // another cool explanation (animation) of order statistic on AVL tree: https://visualgo.net/en/bst?mode=AVL  (Select(k))
    // ---- order statistics ----
    BSTVertex *selectOrder(BSTVertex *T, int k)
    {
        if (T == NULL)
        {
            return NULL;
        }

        int q = getSize(T->left);

        if (q + 1 == k) // q+1 is the rank of node T within the subtreee rooted at T
        {               // node T is the k-th smallest element
            return T;
        }
        else if (k < q + 1)
        { // k-th smallest element resides in T's left subtree
            return selectOrder(T->left, k);
        }
        else
        {
            // k-th smallest element resides in T's right subtree
            // Since the subtree rooted at T
            // contains q+1 elements that come before T’s right subtree in an inorder tree walk, the
            // k-th smallest element in the subtree rooted at T is the (k-(q+1))-th smallest element in
            // the subtree rooted at T.right.
            return selectOrder(T->right, k - q - 1);
        }
    }

    BSTVertex *getNodeOfOrder(int k)
    { // O(logn)
        return selectOrder(root, k);
    }
};

struct golfer
{
    string nama;
    ll score;
};

int main()
{
    int n, q;
    cin >> n >> q;
    unordered_map<string, int> golfer_map(n);
    vector<golfer> golfers(n);
    AVL *order_statistics_tree = new AVL();

    for (int i = 0; i < n; i++)
    {
        cin >> golfers[i].nama;
        golfer_map[golfers[i].nama] = i;
        order_statistics_tree->insertNode(0);
    }

    while (q--)
    {
        char query;
        cin >> query;
        if (query == '!')
        {
            int k;
            cin >> k;
            vector<bool> bs(n);
            for (int j = 0; j < k; j++)
            {
                string nama;
                ll from_par;
                cin >> nama >> from_par;
                auto gid = golfer_map[nama];
                order_statistics_tree->removeNode(golfers[gid].score);
                golfers[gid].score += from_par;
                order_statistics_tree->insertNode(golfers[gid].score);
                bs[gid] = true;
            }
        }
        else
        {
            string nama_golfer;
            cin >> nama_golfer;
            auto gid = golfer_map[nama_golfer];
            auto skor_golfer = golfers[gid].score;
            auto rank = order_statistics_tree->getRank(skor_golfer);
            cout << rank + 1 << " " << skor_golfer << endl;
        }
    }
}