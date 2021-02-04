#include <vector>
#include <iostream>
#include "BTreeNode.h"

std::vector<int> traverse(BTreeNode* subRoot, std::vector<int> v);

std::vector<int> traverse(BTreeNode* root)
{
    // your code here
    std::vector<int> v;
    v = traverse(root, v);
    return v;
}

std::vector<int> traverse(BTreeNode* subRoot, std::vector<int> v)
{
    if (subRoot == NULL)
        return v;

    for (int a = 0; a < (int)(subRoot->children_).size(); a++)
    {
      v = traverse((subRoot->children_)[a], v);
      if (a < (int)(subRoot->elements_).size())
      {
        v.push_back((subRoot->elements_)[a]);
      }
    }

    if ((subRoot->children_).size() == 0)
    {
      for (int a : subRoot->elements_)
      {
        v.push_back(a);
      }
    }

    return v;
}
