#include "Node.h"
#include "iostream"

using namespace std;
Node *listIntersection(Node *first, Node *second);

Node *listSymmetricDifference(Node *first, Node *second)
{
  Node *ret = NULL;
  Node *curr_ret;
  Node *temp;
  // copy the first list without repeating
  if (first != NULL)
  {
    ret = new Node(*first);
    ret->next_ = NULL;
    Node *curr1 = first->next_;
    curr_ret = ret;
    while (curr1 != NULL)
    {
      // cout<<"1"<<endl;
      temp = ret;
      int i = 0;
      while (temp != NULL)
      {
        if (temp->data_ == curr1->data_)
        {
          i = 1;
          break;
        }
        temp = temp->next_;
      }
      if (i == 1)
      {
        curr1 = curr1->next_;
        continue;
      }
      curr_ret->next_ = new Node(*curr1);
      curr1 = curr1->next_;
      curr_ret = curr_ret->next_;
      curr_ret->next_ = NULL;
    }
  }

  if (second == NULL)
    return ret;

  if (ret == NULL) // if the first list is NULL, return the second list without repeating
  {
    ret = new Node(*second);
    ret->next_ = NULL;
    Node *curr2 = second->next_;
    curr_ret = ret;
    while (curr2 != NULL)
    {
      // cout<<"1"<<endl;
      temp = ret;
      int i = 0;
      while (temp != NULL)
      {
        if (temp->data_ == curr2->data_)
        {
          i = 1;
          break;
        }
        temp = temp->next_;
      }
      if (i == 1)
      {
        curr2 = curr2->next_;
        continue;
      }
      curr_ret->next_ = new Node(*curr2);
      curr2 = curr2->next_;
      curr_ret = curr_ret->next_;
      curr_ret->next_ = NULL;
    }
    return ret;
  }

  // copy the second list without repeating
  Node *curr2 = second;
  while (curr2 != NULL)
  {
    temp = ret;
    int i = 0;
    while (temp != NULL)
    {
      if (temp->data_ == curr2->data_)
      {
        i = 1;
        break;
      }
      temp = temp->next_;
    }
    if (i == 1)
    {
      curr2 = curr2->next_;
      continue;
    }
    curr_ret->next_ = new Node(*curr2);
    curr2 = curr2->next_;
    curr_ret = curr_ret->next_;
    curr_ret->next_ = NULL;
  }
  // union of two lists get, remove listIntersectionm from union to get what we want

  Node *remove = listIntersection(first, second);
  Node *remove_curr = remove;

  while (remove_curr != NULL)
  {
    curr_ret = ret;

    if (ret->data_ == remove_curr->data_)
    {
      ret = ret->next_;
      delete curr_ret;
      remove_curr = remove_curr->next_;
      continue;
    }

    Node *prev_ret;
    while (curr_ret != NULL)
    {
      prev_ret = curr_ret;
      curr_ret = curr_ret->next_;
      if (curr_ret == NULL) {break;}

      if (curr_ret->data_ == remove_curr->data_)
      {
        prev_ret->next_ = curr_ret->next_;
        delete curr_ret;
        break;
      }
    }
    remove_curr = remove_curr->next_;
  }

  remove_curr = remove;
  Node *remove_prev;
  while (remove_curr != NULL)
  {
    remove_prev = remove_curr;
    remove_curr = remove_curr->next_;
    delete remove_prev;
  }
  return ret;
}

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
