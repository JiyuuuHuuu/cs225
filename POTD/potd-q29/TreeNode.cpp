#include "TreeNode.h"
#include <iostream>

TreeNode * getNode(TreeNode *root, int key, int & index);

TreeNode * deleteNode(TreeNode* root, int key)
{
  // your code here
  int index;
  TreeNode *curr = getNode(root, key, index);
  // std::cout<<curr->val_<<std::endl;
  if (index == 0)
    return root;


  TreeNode *temp = NULL;
  TreeNode *prev = NULL;
  int lr = 0;
  if (index == 1)
    temp = curr;
  if (index == 2)
    temp = curr->left_;
  if (index == 3)
    temp = curr->right_;

  if (temp->left_ != NULL)
  {
    prev = temp;
    temp = temp->left_;
    lr = 10;
    while (temp->right_ != NULL)
    {
      prev = temp;
      temp = temp->right_;
      lr = 21;
    }
  }
  else if (temp->right_ != NULL)
  {
    prev = temp;
    temp = temp->right_;
    lr = 11;
  }
  else
  {
    if (index == 2)
    {
      curr->left_ = NULL;
    }
    else
    {
      curr->right_ = NULL;
    }
    delete temp;
    return root;
  }

  if (index == 1)
  {
    temp->left_ = root->left_;
    temp->right_ = root->right_;
    if (lr == 10)
      prev->left_ = NULL;
    else
      prev->right_ = NULL;
    delete root;
    return temp;
  }
  else
  {
    // std::cout<<temp->val_<<std::endl;
    TreeNode *temp2;
    if (index == 2)
    {
      temp->left_ = curr->left_->left_;
      temp->right_ = curr->left_->right_;
      temp2 = curr->left_;
      curr->left_ = temp;
      // std::cout<<temp->val_<<std::endl;
    }
    else
    {
      temp->left_ = curr->right_->left_;
      temp->right_ = curr->right_->right_;
      temp2 = curr->right_;
      curr->right_ = temp;
      // std::cout<<temp->val_<<std::endl;
    }
    if (lr == 0)
    {
      if (prev == temp2)
        temp->left_ = NULL;
      else
        prev->left_ = NULL;
    }
    else
    {
      if (prev == temp2)
        temp->right_ = NULL;
      else
        prev->right_ = NULL;
    }
    delete temp2;
  }
  return root;
}

TreeNode * getNode(TreeNode *root, int key, int & index)
{
  if (root->left_ == NULL && root->right_ == NULL)
  {
    index = 0;
    return NULL;
  }
  if (root->val_ == key)
  {
    index = 1;
    return root;
  }
  if (root->right_ != NULL)
  {
    if (root->right_->val_ == key)
    {
      index = 3;
      return root;
    }
  }
  if (root->left_ != NULL)
  {
    if (root->left_->val_ == key)
    {
      index = 2;
      return root;
    }
  }

  if (key > root->val_ && root->right_ != NULL)
    return getNode(root->right_, key, index);
  else if (key < root->val_ && root->left_ != NULL)
    return getNode(root->left_, key, index);

  index = 0;
  return NULL;
}

void inorderPrint(TreeNode* node)
{
    if (!node)  return;
    inorderPrint(node->left_);
    std::cout << node->val_ << " ";
    inorderPrint(node->right_);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
