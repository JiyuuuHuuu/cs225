#include "Node.h"

void mergeList(Node *first, Node *second)
{
  // your code here!
  if (first == NULL && second == NULL)
    return;

  Node *curr_first = first;
  Node *curr_second = second;
  Node *temp1, *temp2;

  while (curr_first != NULL && curr_second != NULL)
  {
    temp1 = curr_first;
    temp2 = curr_second;

    curr_second = curr_second->next_;
    curr_first = curr_first->next_;
    temp2->next_ = curr_first;
    temp1->next_ = temp2;
  }

  if (curr_first != NULL)
  {
    temp2->next_ = curr_first;
  }
  else if (curr_second != NULL)
  {
    temp2->next_ = curr_second;
  }
}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node() {
    numNodes--;
}

int Node::numNodes = 0;
