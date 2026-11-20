#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/babynames?tab=metadata
struct BSTVertex
{
    BSTVertex *parent;
    BSTVertex *left;
    BSTVertex *right;
    string key;
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

    BSTVertex *insert(BSTVertex *T, string v)
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

    string findMin(BSTVertex *T)
    {
        if (T == NULL)
        {
            return "";
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

    string findMax(BSTVertex *T)
    {
        if (T == NULL)
        {
            return "";
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

    BSTVertex *search(BSTVertex *T, string v)
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

    string successor(BSTVertex *T)
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
            return parent == NULL ? "" : parent->key;
        }
    }

    string predecessor(BSTVertex *T)
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

            return parent == NULL ? "" : parent->key;
        }
    }

    BSTVertex *remove(BSTVertex *T, string v)
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
                string successorV = successor(T);
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

    int getLeftSubtreeSize(BSTVertex *T, string key)
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

    void insertNode(string v) { root = insert(root, v); };
    void removeNode(string v) { root = remove(root, v); };
    BSTVertex *searchNode(string v)
    {
        return search(root, v);
    }

    int getRank(string v)
    {
        return getLeftSubtreeSize(root, v);
    }
};

#include <bits/extc++.h> // pbds

using namespace __gnu_pbds;
typedef tree<string, null_type, less<string>, rb_tree_tag,
             tree_order_statistics_node_update>
    ost;

int main()
{

    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int cmdType = 0;

    ost treeCowok;
    ost treeCewek;
    unordered_map<string, int> pplGender;

    while (true)
    {
        int cmdType;
        cin >> cmdType;
        if (cmdType == 0)
        {
            break;
        }

        if (cmdType == 1)
        {
            string nama = "";
            int gender = 0;
            cin >> nama >> gender;
            if (gender == 1)
            {
                treeCowok.insert(nama);
                pplGender[nama] = 1;
            }
            else
            {
                treeCewek.insert(nama);
                pplGender[nama] = 2;
            }
        }
        else if (cmdType == 3)
        {
            string start = "", end = "";
            int queryGender = 0;
            cin >> start >> end >> queryGender;

            if (queryGender == 0)
            {
                int countCowok = treeCowok.order_of_key(end) - treeCowok.order_of_key(start);

                int countCewek = treeCewek.order_of_key(end) - treeCewek.order_of_key(start);

                cout << countCowok + countCewek << "\n";
            }
            else if (queryGender == 1)
            {
                int countCowok = treeCowok.order_of_key(end) - treeCowok.order_of_key(start);
                cout << countCowok << "\n";
            }
            else if (queryGender == 2)
            {
                int countCewek = treeCewek.order_of_key(end) - treeCewek.order_of_key(start);
                cout << countCewek << "\n";
            }
        }
        else if (cmdType == 2)
        {
            string nama;
            cin >> nama;
            if (pplGender[nama] == 1)
            {
                treeCowok.erase(nama);
            }
            else
            {
                treeCewek.erase(nama);
            }
            pplGender.erase(nama);
        }
    }

    // Memory Limit Excedeed
    // AVL *treeCowok = new AVL();
    // AVL *treeCewek = new AVL();

    // while (true)
    // {
    //     int cmdType;
    //     cin >> cmdType;
    //     if (cmdType == 0)
    //     {
    //         break;
    //     }

    //     if (cmdType == 1)
    //     {
    //         string nama = "";
    //         int gender = 0;
    //         cin >> nama >> gender;
    //         if (gender == 1)
    //         {
    //             treeCowok->insertNode(nama); // log(N)
    //         }
    //         else
    //         {
    //             treeCewek->insertNode(nama); // log(N)
    //         }
    //     }
    //     else if (cmdType == 3)
    //     {
    //         string start = "", end = "";
    //         int queryGender = 0;
    //         cin >> start >> end >> queryGender;

    //         if (queryGender == 0)
    //         {
    //             int countCowok = treeCowok->getRank(end) - treeCowok->getRank(start); // log(N)
    //             int countCewek = treeCewek->getRank(end) - treeCewek->getRank(start);// log(N)
    //             cout << countCowok + countCewek << endl;
    //         }
    //         else if (queryGender == 1)
    //         {
    //             cout << treeCowok->getRank(end) - treeCowok->getRank(start) << endl; // log(N)
    //         }
    //         else if (queryGender == 2)
    //         {
    //             cout << treeCewek->getRank(end) - treeCewek->getRank(start) << endl; // log(N)
    //         }
    //     }
    //     else if (cmdType == 2)
    //     {
    //         string nama;
    //         cin >> nama;

    //         BSTVertex *nodeCowok = treeCowok->searchNode(nama); // log(N)
    //         BSTVertex *nodeCewek = treeCewek->searchNode(nama); // log(N)
    //         if (nodeCowok != NULL)
    //         {
    //             treeCowok->removeNode(nama); // log(N)
    //         }
    //         else if (nodeCewek != NULL)
    //         {
    //             treeCewek->removeNode(nama); // log(N)
    //         }
    //     }
    // }

    return 0;
}