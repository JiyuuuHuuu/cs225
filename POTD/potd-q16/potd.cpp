#include "potd.h"
#include <iostream>

using namespace std;

void insertSorted(Node **head, Node *insert)
{
  // your code here!
  Node *cur = *head;
  if (cur == NULL || cur->data_ >= insert->data_) // insert at the front
  {
    insert->next_ = *head;
    *head = insert;
    return;
  }

  cur = cur->next_; // loop to insert in the middle
  Node *prev = *head;
  //cout<<"1"<<endl;
  while (cur != NULL)
  {
    if (insert->data_ <= cur->data_)
    {
      insert->next_ = cur;
      prev->next_ = insert;
      return;
    }
    prev = cur;
    cur = cur->next_;
  }

  insert->next_ = NULL; // insert at the back
  prev->next_ = insert;
}
