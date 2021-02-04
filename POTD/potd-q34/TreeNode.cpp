#include "TreeNode.h"

TreeNode::RotationType balanceTree(TreeNode*& subroot) {
	// Your code here
  if (leftHeavy(subroot))
  {
    if (getHeight(subroot->left_->left_) > getHeight(subroot->left_->right_))
    {
      return TreeNode::right;
    }
    else
    {
      return TreeNode::leftRight;
    }
  }
  else if (rightHeavy(subroot))
  {
    if (getHeight(subroot->right_->left_) > getHeight(subroot->right_->right_))
    {
      return TreeNode::rightLeft;
    }
    else
    {
      return TreeNode::left;
    }
  }
  return TreeNode::right;
}
