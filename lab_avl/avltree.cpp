// valgrinded
/**
 * @file avltree.cpp
 * Definitions of the binary tree functions you'll be writing for this lab.
 * You'll need to modify this file.
 */

template <class K, class V>
V AVLTree<K, V>::find(const K& key) const
{
    return find(root, key);
}

template <class K, class V>
V AVLTree<K, V>::find(Node* subtree, const K& key) const
{
    if (subtree == NULL)
        return V();
    else if (key == subtree->key)
        return subtree->value;
    else {
        if (key < subtree->key)
            return find(subtree->left, key);
        else
            return find(subtree->right, key);
    }
}

template <class K, class V>
void AVLTree<K, V>::rotateLeft(Node*& t)
{
    // std::cout<<"2"<<std::endl;
    functionCalls.push_back("rotateLeft"); // Stores the rotation name (don't remove this)
    // your code here
    Node *temp = t->right;
    Node *temp2 = t->right->left;

    t->right = temp2;
    temp->left = t;
    t = temp;
}

template <class K, class V>
void AVLTree<K, V>::rotateLeftRight(Node*& t)
{
    functionCalls.push_back("rotateLeftRight"); // Stores the rotation name (don't remove this)
    // Implemented for you:
    rotateLeft(t->left);
    rotateRight(t);
}

template <class K, class V>
void AVLTree<K, V>::rotateRight(Node*& t)
{
    functionCalls.push_back("rotateRight"); // Stores the rotation name (don't remove this)
    // your code here
    Node *temp = t->left;
    Node *temp2 = t->left->right;

    t->left = temp2;
    temp->right = t;
    t = temp;

    // std::cout<<"rotateright"<<std::endl;
}

template <class K, class V>
void AVLTree<K, V>::rotateRightLeft(Node*& t)
{
    functionCalls.push_back("rotateRightLeft"); // Stores the rotation name (don't remove this)
    // your code here
    rotateRight(t->right);
    rotateLeft(t);
}

template <class K, class V>
void AVLTree<K, V>::rebalance(Node*& subtree)
{
    // your code here
    if (treeHeight(subtree->left) - treeHeight(subtree->right) > 1)
    {
      if (treeHeight(subtree->left->left) > treeHeight(subtree->left->right))
        rotateRight(subtree);
      else
        rotateLeftRight(subtree);
    }
    else if (treeHeight(subtree->left) - treeHeight(subtree->right) < -1)
    {
      // std::cout<<"2"<<std::endl;
      if (treeHeight(subtree->right->left) > treeHeight(subtree->right->right))
        rotateRightLeft(subtree);
      else
        rotateLeft(subtree);
    }
    // std::cout<<"2"<<std::endl;
}

template <class K, class V>
void AVLTree<K, V>::insert(const K & key, const V & value)
{
    // std::cout<<key<<std::endl;
    insert(root, key, value);
    // std::cout<<"3"<<std::endl;
}

template <class K, class V>
void AVLTree<K, V>::insert(Node*& subtree, const K& key, const V& value)
{
    // your code here
    if (subtree == NULL)
    {
      Node *temp = new Node(key, value);
      subtree = temp;
      return;
    }

    if (key == subtree->key)
      return;

    if (key > subtree->key)
    {
      insert(subtree->right, key, value);
      rebalance(subtree);
      return;
    }

    insert(subtree->left, key, value);
    rebalance(subtree);
}

template <class K, class V>
void AVLTree<K, V>::remove(const K& key)
{
    // std::cout<<key<<std::endl;
    remove(root, key);
    // std::cout<<std::endl;
}

template <class K, class V>
void AVLTree<K, V>::remove(Node*& subtree, const K& key)
{
    // std::cout<<subtree->key<<" ";
    if (subtree == NULL)
        return;

    if (key < subtree->key) {
        // your code here
        remove(subtree->left, key);
        rebalance(subtree);
    } else if (key > subtree->key) {
        // your code here
        remove(subtree->right, key);
        rebalance(subtree);
    } else {
        if (subtree->left == NULL && subtree->right == NULL) {
            /* no-child remove */
            // your code here
            Node *temp = subtree;
            subtree = NULL;
            delete temp;
            return;
        } else if (subtree->left != NULL && subtree->right != NULL) {
            /* two-child remove */
            // your code here
            Node* temp = subtree->left;
            while(temp->right != NULL)
            {
              temp = temp->right;
            }
            swap(temp, subtree);
            remove(subtree->left, key);
        } else {
            /* one-child remove */
            // your code here
            if (subtree->left != NULL)
            {
              Node *temp = subtree;
              subtree = subtree->left;
              delete temp;
            }
            else
            {
              Node *temp = subtree;
              subtree = subtree->right;
              delete temp;
            }
        }
        // your code here
        rebalance(subtree);
    }
}

template <class K, class V>
int AVLTree<K, V>::treeHeight(Node *Subroot)
{
  if (Subroot == NULL)
    return -1;

  int a = treeHeight(Subroot->left);
  int b = treeHeight(Subroot->right);

  return 1+(a>b?a:b);
}
