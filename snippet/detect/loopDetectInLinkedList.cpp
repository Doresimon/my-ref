/**
 * Detect loop in a linked list
 * Given a linked list, check if the the linked list has loop or not.  
 */

#include <iostream>
#include <set>

using namespace std;

class Node
{
  public:
    int v;
    Node *next;

  public:
    Node(int v);
    Node *jump(int step);
    Node *push(Node *n);
    void print();
};

Node::Node(int v)
{
    this->v = v;
    this->next = NULL;
}

Node *Node::jump(int step)
{
    Node *p = this;
    while (step > 0 && p->next != NULL)
    {
        p = p->next;
    }
    return p;
}

Node *Node::push(Node *n)
{
    Node *p = this;
    while (p->next)
    {
        p = p->next;
    }
    p->next = n;
    return n;
}

// if there is a cycle, this function will be a dead loop
void Node::print()
{
    Node *p = this;
    while (p->next)
    {
        p = p->next;
        cout << p->v << " -> ";
    }
    cout << "NULL" << endl;
    return;
}

int DetectLoopBySlowFastPointer(Node *head)
{
    Node *slow = head;
    Node *fast = head;

    while (fast != NULL)
    {
        slow = slow->next; // jump 1 step

        fast = fast->next; // jump 2 step
        if (fast == NULL)
            return 0;
        fast = fast->next;
        if (fast == NULL)
            return 0;

        if (fast->v == slow->v)
            return 1;
    }

    return 0;
}

int main()
{

    Node *head = new Node(0);
    int count = 20;
    for (int i = 1; i < count; i++)
    {
        head->push(new Node(i));
    }

    Node tail = Node(count);
    head->push(&tail);
    tail.next = head->jump(5);

    if (DetectLoopBySlowFastPointer(head))
    {
        cout << "LOOP DETECTED." << endl;
    }
    else
    {
        cout << "LOOP NOT DETECTED." << endl;
    }

    return 0;
}