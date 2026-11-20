#include <bits/stdc++.h>
using namespace std;

// https://open.kattis.com/problems/sim?tab=metadata

/*

original list: +->l->o->v->->e->s->+


list depan: +->s->t->e->v->e->n->" "->+

merge(listDepan, listOri):

+->s->t->e->v->e->n->" "->l->o->v->->e->s->+

*/

struct Node
{
    char c;
    Node *next;
    Node *prev;

    Node(char ch)
    {
        c = ch;
        next = nullptr;
        prev = nullptr;
    }
};

void insert(Node *tail, char c)
{
    Node *newNode = new Node(c);

    newNode->prev = tail->prev;
    newNode->next = tail;
    tail->prev->next = newNode;
    tail->prev = newNode;
}

void mergeList(Node *headDepan, Node *tailDepan, Node *head)
{
    if (headDepan->next != tailDepan)
    {

        tailDepan->prev->next = head->next;

        head->next->prev = tailDepan->prev;

        head->next = headDepan->next;

        headDepan->next->prev = head;
    }
}

void remove_back(Node *head, Node *tail)
{
    if (head->next == tail)
    {
        return;
    }

    Node *deletedNode = tail->prev;
    deletedNode->prev->next = tail;
    tail->prev = deletedNode->prev;
    delete deletedNode;
}

int main()
{

    int T;
    cin >> T;
    cin.ignore();
    for (int t = 0; t < T; t++)
    {
        Node *head = new Node('+');
        Node *tail = new Node('+');
        head->next = tail;
        tail->prev = head;

        Node *headDepan = new Node('+');
        Node *tailDepan = new Node('+');
        headDepan->next = tailDepan;
        tailDepan->prev = headDepan;

        string line;
        getline(cin, line);
        bool bikinListBaru = false;
        for (int i = 0; i < line.size(); i++)
        { // O(line.size()), all list operations (merge,remove,insert) are O(1)
            char c = line[i];
            if (c == '[')
            {
                bikinListBaru = true;
            }
            else if (c == ']')
            {
                bikinListBaru = false;

                mergeList(headDepan, tailDepan, head);
                // reset list depan
                headDepan = new Node('+');
                tailDepan = new Node('+');
                headDepan->next = tailDepan;
                tailDepan->prev = headDepan;
            }
            else if (c == '<')
            {

                // delete
                if (!bikinListBaru)
                {
                    remove_back(head, tail);
                }
                else
                {
                    remove_back(headDepan, tailDepan);
                }
            }
            else
            {
                if (!bikinListBaru)
                {
                    insert(tail, c);
                }
                else
                {
                    insert(tailDepan, c);
                }
            }
        }

        mergeList(headDepan, tailDepan, head);

        Node *nextNode = head->next;
        while (nextNode != tail)
        {

            cout << nextNode->c;

            nextNode = nextNode->next;
        }
        cout << endl;
    }
    return 0;
}
