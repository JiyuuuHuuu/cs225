#include <vector>
#include "BTreeNode.h"


BTreeNode* find(BTreeNode* root, int key)
{
    // Your Code Here
    for (const int a : root->elements_)
    {
      if (a == key)
      {
        return root;
      }
    }

    BTreeNode *retVal = NULL;

    for (BTreeNode *b : root->children_)
    {
      {
        retVal = find(b, key);
        if (retVal != NULL)
          break;
      }
    }

    return retVal;
}
