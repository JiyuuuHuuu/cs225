#include "Queue.h"

Queue::Queue()
{
  front = NULL;
  tail = NULL;
  num = 0;
}

Queue::~Queue()
{
  _destroy();
}

// `int size()` - returns the number of elements in the stack (0 if empty)
int Queue::size() const
{
  return num;
}

// `bool isEmpty()` - returns if the list has no elements, else false
bool Queue::isEmpty() const
{
  if (num == 0)
    return true;

  return false;
}

// `void enqueue(int val)` - enqueue an item to the queue in O(1) time
void Queue::enqueue(int value)
{
  Node *temp = new Node(value);
  if (front == NULL)
  {
    front = temp;
    tail = temp;
    num++;
    return;
  }
  tail->next = temp;
  tail = temp;
  num++;
}

// `int dequeue()` - removes an item off the queue and returns the value in O(1) time
int Queue::dequeue()
{
  if (front == NULL)
    return -1;

  Node *temp = front;
  front = front->next;
  int i = temp->value;
  delete temp;
  num--;
  return i;
}

void Queue::_destroy()
{
  if (front == NULL)
    return;
    
  Node *curr = front;
  Node *prev;
  while (curr != tail)
  {
    prev = curr;
    curr = curr->next;
    delete prev;
  }
  num = 0;
  delete tail;
}
