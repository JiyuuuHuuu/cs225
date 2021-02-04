#include "TreeNode.h"

int treeHeight(TreeNode *root);

bool isHeightBalanced(TreeNode* root)
{
  // your code here
  if (root == NULL)
    return true;

  int a = treeHeight(root->left_);
  int b = treeHeight(root->right_);

  return (a-b <= 1 && a-b >= -1) && isHeightBalanced(root->left_) && isHeightBalanced(root->right_);
}

int treeHeight(TreeNode *Subroot)
{
  if (Subroot == NULL)
    return 0;

  int a = treeHeight(Subroot->left_);
  int b = treeHeight(Subroot->right_);

  return 1+(a>b?a:b);
}

void deleteTree(TreeNode* root)
{
  if (root == NULL) return;
  deleteTree(root->left_);
  deleteTree(root->right_);
  delete root;
  root = NULL;
}
