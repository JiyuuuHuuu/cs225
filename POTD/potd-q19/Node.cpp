#include "Node.h"

/** Create a new node and add it to the list, while keeping the list sorted.
*/
Node *insertSorted(Node *first, int data)
{
    // your code here
    Node *insert = new Node();
    insert->data_ = data;

    if (first == NULL) //check empty list
    {
        first = insert;
        insert->next_ = NULL;
        return first;
    }

    Node *curr = first;
    Node *prev = first;

    while (curr != NULL)
    {
      if (insert->data_ < curr->data_)
      {
        if (insert->data_ == prev->data_) //skip already existing values
          break;

        if (curr == first) // add to the front
        {
          insert->next_ = curr;
          return insert;
        }

        insert->next_ = curr; //add to the middle
        prev->next_ = insert;
        return first;
      }
      prev = curr; //traverse
      curr = curr->next_;
    }

    if (insert->data_ != prev->data_) //add to the tail
    {
      prev->next_ = insert;
      insert->next_ = NULL;
      return first;
    }

    delete insert;
    return first;
}

/** Creates a new list (containing new nodes, allocated on the heap)
	that contains the set union of the values in both lists.
*/
Node *listUnion(Node *first, Node *second) {
    Node *out = NULL;

    while (first != NULL)
    {
        // your code here
        // hint: call insertSorted and update l1
        out = insertSorted(out, first->data_);
        first = first->next_;
    }

    while (second != NULL)
    {
        // your code here
        out = insertSorted(out, second->data_);
        second = second->next_;
    }

    return out;
}

Node::Node() {
    numNodes++;
}

Node::Node(const Node &other) {
    this->data_ = other.data_;
    this->next_ = other.next_;
    numNodes++;
}

Node::~Node()
{
    numNodes--;
}

int Node::numNodes = 0;
