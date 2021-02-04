#include "TreeNode.h"

TreeNode* findLastUnbalanced(TreeNode* root)
{
  // your code here
  if (root == NULL)
    return NULL;

  int a = treeHeight(root->left_);
  int b = treeHeight(root->right_);

  TreeNode * temp1 = findLastUnbalanced(root->left_);
  TreeNode * temp2 = findLastUnbalanced(root->right_);

  if (a - b <= 1 && a - b >= -1)
    return (temp1 == NULL? temp2:temp1);

  if (a > b)
  {
    return (temp1 == NULL?root:temp1);
  }

  return (temp2 == NULL?root:temp2);
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
