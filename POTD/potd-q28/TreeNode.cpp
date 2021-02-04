#include "TreeNode.h"

#include <cstddef>
#include <iostream>
using namespace std;

int heightHelper(TreeNode* curr);

TreeNode::TreeNode() : left_(NULL), right_(NULL) { }

int TreeNode::getHeight()
{
  return heightHelper(this);
}

int heightHelper(TreeNode *curr)
{
  if (curr->left_ == NULL && curr->right_ == NULL)
    return 0;

  if (curr->left_ == NULL)
    return heightHelper(curr->right_) + 1;

  if (curr->right_ == NULL)
    return heightHelper(curr->left_) + 1;

  int a = heightHelper(curr->right_);
  int b = heightHelper(curr->left_);
  return (a > b? a:b) + 1;
}
