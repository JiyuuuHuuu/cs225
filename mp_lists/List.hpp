/**
 * @file list.cpp
 * Doubly Linked List (MP 3).
 */

template <class T>
List<T>::List() {
  // @TODO: graded in MP3.1
    head_ = NULL;
    tail_ = NULL;
    length_ = 0;
}

/**
 * Returns a ListIterator with a position at the beginning of
 * the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::begin() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(head_);
}

/**
 * Returns a ListIterator one past the end of the List.
 */
template <typename T>
typename List<T>::ListIterator List<T>::end() const {
  // @TODO: graded in MP3.1
  return List<T>::ListIterator(NULL);
}


/**
 * Destroys all dynamically allocated memory associated with the current
 * List class.
 */
template <typename T>
void List<T>::_destroy()
{
  /// @todo Graded in MP3.1
  if (head_ == NULL)
    return;

  ListNode *curr = head_;
  ListNode *prev = head_;

  while (curr != NULL)
  {
    prev = curr;
    curr = curr->next;

    delete prev;
  }
}

/**
 * Inserts a new node at the front of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertFront(T const & ndata) {
  /// @todo Graded in MP3.1
  ListNode * newNode = new ListNode(ndata);
  newNode -> next = head_;
  newNode -> prev = NULL;

  if (head_ != NULL) {
    head_ -> prev = newNode;
  }
  if (tail_ == NULL) {
    tail_ = newNode;
  }

  head_ = newNode;
  length_++;

}

/**
 * Inserts a new node at the back of the List.
 * This function **SHOULD** create a new ListNode.
 *
 * @param ndata The data to be inserted.
 */
template <typename T>
void List<T>::insertBack(const T & ndata)
{
  /// @todo Graded in MP3.1
  ListNode *temp = new ListNode(ndata);
  temp->prev = tail_;
  temp->next = NULL;

  if (tail_ != NULL)
  {
    tail_->next = temp;
  }
  if (head_ == NULL)
  {
    head_ = temp;
  }

  tail_ = temp;
  length_++;
}

/**
 * Helper function to split a sequence of linked memory at the node
 * splitPoint steps **after** start. In other words, it should disconnect
 * the sequence of linked memory after the given number of nodes, and
 * return a pointer to the starting node of the new sequence of linked
 * memory.
 *
 * This function **SHOULD NOT** create **ANY** new List or ListNode objects!
 *
 * This function is also called by the public split() function located in
 * List-given.hpp
 *
 * @param start The node to start from.
 * @param splitPoint The number of steps to walk before splitting.
 * @return The starting node of the sequence that was split off.
 */
template <typename T>
typename List<T>::ListNode * List<T>::split(ListNode * start, int splitPoint)
{
  /// @todo Graded in MP3.1
  if (start == NULL)
    return NULL;


  ListNode * curr = start;

  if (splitPoint == 0)
  {
    start = NULL;
    return curr;
  }

  for (int i = 0; i < splitPoint; i++)
  {
    if (curr != NULL)
      curr = curr->next;
    if (curr == NULL)
      break;
  }

  if (curr != NULL)
  {
      curr->prev->next = NULL;
      curr->prev = NULL;
  }

  return curr;
}

/**
 * Modifies the List using the waterfall algorithm.
 * Every other node (starting from the second one) is removed from the
 * List, but appended at the back, becoming the new tail. This continues
 * until the next thing to be removed is either the tail (**not necessarily
 * the original tail!**) or NULL.  You may **NOT** allocate new ListNodes.
 * Note that since the tail should be continuously updated, some nodes will
 * be moved more than once.
 */
template <typename T>
void List<T>::waterfall()
{
  /// @todo Graded in MP3.1
  ListNode *curr = head_;
  ListNode *temp;

  while (curr->next != tail_ && curr->next != NULL)
  {
    curr = curr->next;
    temp = curr;
    curr = curr->next;

    temp->prev->next = curr;
    curr->prev = temp->prev;

    temp->next = NULL;
    tail_->next = temp;
    temp->prev = tail_;
    tail_ = temp;
  }
}

/**
 * Reverses the current List.
 */
template <typename T>
void List<T>::reverse()
{
  reverse(head_, tail_);
}

/**
 * Helper function to reverse a sequence of linked memory inside a List,
 * starting at startPoint and ending at endPoint. You are responsible for
 * updating startPoint and endPoint to point to the new starting and ending
 * points of the rearranged sequence of linked memory in question.
 *
 * @param startPoint A pointer reference to the first node in the sequence
 *  to be reversed.
 * @param endPoint A pointer reference to the last node in the sequence to
 *  be reversed.
 */
template <typename T>
void List<T>::reverse(ListNode *& startPoint, ListNode *& endPoint)
{
  // @todo Graded in MP3.2
  if (startPoint == NULL || endPoint == NULL)
    return;
  reversehelp(startPoint, endPoint);
  //std::cout<<"1"<<std::endl;
  ListNode *temp;
  ListNode *temp1 = NULL;
  ListNode *temp2 = NULL;
  temp = endPoint->prev;
  endPoint->prev = startPoint->next;
  startPoint->next = temp;

  temp = startPoint;
  startPoint = endPoint;
  endPoint = temp;

  if (startPoint->prev != NULL)
    temp1 = startPoint->prev;
  if (endPoint->next != NULL)
    temp2 = endPoint->next;

  if (temp1 != NULL)
    temp1->next = startPoint;
  if (temp2 != NULL)
    temp2->prev = endPoint;
}

template <typename T>
void List<T>::reversehelp(ListNode *startPoint, ListNode *endPoint)
{
    ListNode *temp1;
    ListNode *temp2 = endPoint;
    ListNode *curr = startPoint;
    int i = 0;

    while (curr != endPoint)
    {
      //std::cout<<i<<std::endl;
      temp1 = curr->prev;
      temp2 = curr->next;

      curr->prev = temp2;
      curr->next = temp1;

      curr = temp2;
      i++;
    }
    temp1 = endPoint->next;
    endPoint->next = endPoint->prev;
    endPoint->prev = temp1;
}

/**
 * Reverses blocks of size n in the current List. You should use your
 * reverse( ListNode * &, ListNode * & ) helper function in this method!
 *
 * @param n The size of the blocks in the List to be reversed.
 */
template <typename T>
void List<T>::reverseNth(int n)
{
  /// @todo Graded in MP3.2
  ListNode *curr1 = head_;
  ListNode *curr2 = curr1;

  for (int i = 0; i < n-1; i++)
  {
    if (curr2->next == NULL)
    {
      reverse(curr1, curr2);
      return;
    }
    curr2 = curr2->next;
    //std::cout<<curr2->data<<std::endl;
  }
  reverse(curr1, curr2);
  head_ = curr1;
  curr1 = curr2->next;

  while (curr1 != NULL)
  {
    //std::cout<<" "<<curr1->data<<std::endl;
    curr2 = curr1;
    for (int i = 0; i < n-1; i++)
    {
      if (curr2->next == NULL)
      {
        reverse(curr1, curr2);
        tail_ = curr2;
        return;
      }
      curr2 = curr2->next;
      //std::cout<<curr2->data<<std::endl;
    }
    reverse(curr1, curr2);
    //std::cout<<curr1->data<<std::endl;
    curr1 = curr2->next;

    /*
    std::cout<<head_->data<<" ";
    std::cout<<head_->next->data<<" ";
    std::cout<<head_->next->next->data<<" ";
    std::cout<<head_->next->next->next->data<<" ";
    std::cout<<head_->next->next->next->next->data<<" ";
    std::cout<<head_->next->next->next->next->next->data<<" ";
    std::cout<<head_->next->next->next->next->next->next->data<<" ";
    std::cout<<head_->next->next->next->next->next->next->next->data<<" ";
    std::cout<<head_->next->next->next->next->next->next->next->next->data<<endl;
    */
  }
  tail_ = curr2;
}


/**
 * Merges the given sorted list into the current sorted list.
 *
 * @param otherList List to be merged into the current list.
 */

template <typename T>
void List<T>::mergeWith(List<T> & otherList) {
    // set up the current list
    head_ = merge(head_, otherList.head_);
    tail_ = head_;

    // make sure there is a node in the new list
    if (tail_ != NULL) {
        while (tail_->next != NULL)
            tail_ = tail_->next;
    }
    length_ = length_ + otherList.length_;

    // empty out the parameter list
    otherList.head_ = NULL;
    otherList.tail_ = NULL;
    otherList.length_ = 0;
}


/**
 * Helper function to merge two **sorted** and **independent** sequences of
 * linked memory. The result should be a single sequence that is itself
 * sorted.
 *
 * This function **SHOULD NOT** create **ANY** new List objects.
 *
 * @param first The starting node of the first sequence.
 * @param second The starting node of the second sequence.
 * @return The starting node of the resulting, sorted sequence.
 */

template <typename T>
typename List<T>::ListNode * List<T>::merge(ListNode * first, ListNode* second)
{
  /// @todo Graded in MP3.2
  if (first == NULL)
  {
    first = second;
    second = NULL;
    return first;
  }

  if (second == NULL)
    return first;

  ListNode *curr1 = first;
  ListNode *curr2 = second;
  ListNode *prev1 = first;
  ListNode *prev2 = second;
  ListNode *ret = NULL;
  ListNode *ret_curr;

  if (curr1->data < curr2->data)
  {
    prev1 = curr1;
    curr1 = curr1->next;

    ret = prev1;
    prev1->next = NULL;
    prev1->prev = NULL;
  }
  else
  {
    prev2 = curr2;
    curr2 = curr2->next;

    ret = prev2;
    prev2->next = NULL;
    prev2->prev = NULL;
  }

  ret_curr = ret;

  while (curr1 != NULL && curr2 != NULL)
  {
    if (curr1->data < curr2->data)
    {
      prev1 = curr1;
      curr1 = curr1->next;

      ret_curr->next = prev1;
      prev1->prev = ret_curr;
      prev1->next = NULL;

      ret_curr = ret_curr->next;
    }
    else
    {
      prev2 = curr2;
      curr2 = curr2->next;

      ret_curr->next = prev2;
      prev2->prev = ret_curr;
      prev2->next = NULL;

      ret_curr = ret_curr->next;
    }
  }

  if (curr1 != NULL)
  {
    ret_curr->next = curr1;
  }
  else if (curr2 != NULL)
  {
    ret_curr->next = curr2;
  }

  return ret;
}


/**
 * Sorts a chain of linked memory given a start node and a size.
 * This is the recursive helper for the Mergesort algorithm (i.e., this is
 * the divide-and-conquer step).
 *
 * Called by the public sort function in List-given.hpp
 *
 * @param start Starting point of the chain.
 * @param chainLength Size of the chain to be sorted.
 * @return A pointer to the beginning of the now sorted chain.
 */
template <typename T>
typename List<T>::ListNode* List<T>::mergesort(ListNode * start, int chainLength)
{
  /// @todo Graded in MP3.2
  // base case
  if (chainLength == 1)
    return start;

  // recursive case
  int splitPoint = chainLength/2;
  ListNode *second = split(start, splitPoint);
  ListNode *temp1 = mergesort(start, splitPoint);
  ListNode *temp2 = mergesort(second, chainLength - splitPoint);
  return merge(temp1, temp2);
}
