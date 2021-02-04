#include "Node.h"

using namespace std;

Node *listIntersection(Node *first, Node *second)
{
  // your code here
  Node *curr1 = first;
  Node *curr2 = second;
  Node *ret = NULL;
  Node *curr, *temp;

  while (curr1 != NULL)
  {
    int data1 = curr1->data_;
    curr2 = second;
    while (curr2 != NULL)
    {
      if (data1 == curr2->data_)
      {
        int i = 0;
        temp = ret;
        while (temp != NULL)
        {
          if (temp->data_ == curr2->data_)
            i = 1;
          temp = temp->next_;
        }
        if (ret == NULL)
        {
          ret = new Node(*curr1);
          ret->next_ = NULL;
          curr = ret;
        }
        else if (i == 0)
        {
          curr->next_ = new Node(*curr1);
          curr = curr->next_;
          curr->next_ = NULL;
        }
      }
      curr2 = curr2->next_;
    }
    curr1 = curr1->next_;
  }

  return ret;
}

Node::Node() {
    numNodes++;
}

Node::Node(Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
