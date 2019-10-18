//valgrinded [part=1]
/**
 * @file kdtree.cpp
 * Implementation of KDTree class.
 */

#include <utility>
#include <algorithm>

using namespace std;

template <int Dim>
bool KDTree<Dim>::smallerDimVal(const Point<Dim>& first,
                                const Point<Dim>& second, int curDim) const
{
    /**
     * @todo Implement this function!
     */

    if (!(first[curDim] > second[curDim]))
      return true;

    return false;
}

template <int Dim>
double KDTree<Dim>::getDistance(const Point<Dim>& first,
                                const Point<Dim>& second) const
{
    double dis1 = 0;
    for (int i = 0; i < Dim; i++)
    {
      dis1 += (first[i] - second[i])*(first[i] - second[i]);
    }

    return dis1;
}

template <int Dim>
bool KDTree<Dim>::shouldReplace(const Point<Dim>& target,
                                const Point<Dim>& currentBest,
                                const Point<Dim>& potential) const
{
    /**
     * @todo Implement this function!
     */
     double dis1 = getDistance(target, currentBest);
     double dis2 = getDistance(target, potential);

     if (dis1 > dis2)
       return true;
     else if (dis1 == dis2)
       return (potential < currentBest);

     return false;
}

// helper funtion that finds the kth element of an array (k starts from 0)
template <int Dim>
Point<Dim> KDTree<Dim>::findKth(const vector<Point<Dim>>& newPoints, int k, int dim)
{
    // cout<<k<<endl;
    if (newPoints.size() == 1)
      return newPoints[0];

    Point<Dim> tar = newPoints[0];
    vector<Point<Dim>> subL, subR;

    for (Point<Dim> temp : newPoints)
    {
      if (temp[dim] > tar[dim])
        subR.push_back(temp);
      else if (temp[dim] < tar[dim])
        subL.push_back(temp);
      else if (temp != tar)
      {
        if (temp < tar)
          subL.push_back(temp);
        else
          subR.push_back(temp);
      }
    }

    if ((int)subL.size() == k)
      return tar;
    else if ((int)subL.size() < k)
      return findKth(subR, k - (int)subL.size() - 1, dim);
    else
      return findKth(subL, k, dim);
}

template <int Dim>
void KDTree<Dim>::constHelper(const vector<Point<Dim>>& newPoints, KDTreeNode *& subroot, int dim)
{
    if (newPoints.size() == 0)
      return;

    int k = (newPoints.size() - 1)/2;
    Point<Dim> med = findKth(newPoints, k , dim);

    // cout<<"med:"<<med<<endl;

    subroot = new KDTreeNode(med);

    vector<Point<Dim>> subL, subR;
    for (Point<Dim> temp : newPoints)
    {
      if (temp[dim] > med[dim])
        subR.push_back(temp);
      else if (temp[dim] < med[dim])
        subL.push_back(temp);
      else if (temp != med)
      {
        if (temp < med)
          subL.push_back(temp);
        else
          subR.push_back(temp);
      }
    }

    // cout<<"right:";
    // for (Point<Dim> temp : subL)
    // {
    //   cout<<"left:"<<temp<<" | ";
    // }
    // cout<<endl<<"right:";
    // for (Point<Dim> temp : subR)
    // {
    //   cout<<temp<<" | ";
    // }
    // cout<<endl;

    constHelper(subL, subroot->left, (dim + 1)%Dim);
    constHelper(subR, subroot->right, (dim + 1)%Dim);
}

template <int Dim>
KDTree<Dim>::KDTree(const vector<Point<Dim>>& newPoints)
{
    /**
     * @todo Implement this function!
     */
    root = NULL;
    size = 0;
    constHelper(newPoints, root, 0);
}

template <int Dim>
void KDTree<Dim>::copyHelper(KDTreeNode *& subroot, const KDTreeNode * other)
{
    if (other == NULL)
      return;

    subroot = new KDTreeNode(*other);

    copyHelper(subroot->left, other->left);
    copyHelper(subroot->tight, other->right);
}

template <int Dim>
KDTree<Dim>::KDTree(const KDTree<Dim>& other)
{
  /**
   * @todo Implement this function!
   */
   root = NULL;
   size = 0;
   copyHelper(root, other->root);
}

template <int Dim>
void KDTree<Dim>::destroy(KDTreeNode * subroot)
{
    if (subroot == NULL)
      return;

    destroy(subroot->left);
    destroy(subroot->right);

    delete subroot;
    subroot = NULL;
}

template <int Dim>
const KDTree<Dim>& KDTree<Dim>::operator=(const KDTree<Dim>& rhs)
{
  /**
   * @todo Implement this function!
   */
  destroy(root);
  copyHelper(root, rhs.root);
  size = rhs.size;
  return *this;
}

template <int Dim>
KDTree<Dim>::~KDTree()
{
  /**
   * @todo Implement this function!
   */
   destroy(root);
}

template <int Dim>
Point<Dim> KDTree<Dim>::findHelper(const Point<Dim>& query, const KDTreeNode* subroot, int dim) const
{
    bool isSmall;
    Point<Dim> ret, temp;

    // base case
    if (subroot->left == NULL && subroot->right == NULL)
      return subroot->point;

    // check current dimention
    if (query[dim] < subroot->point[dim])
      isSmall = true;
    else if (query[dim] > subroot->point[dim])
      isSmall = false;
    else
    {
      if (query < subroot->point)
        isSmall = true;
      else if (query > subroot->point)
        isSmall = false;
      else
        return subroot->point;
    }

    // recursively search the hyperrectangle
    if (isSmall)
      ret = subroot->left!=NULL ? findHelper(query, subroot->left, (dim + 1)%Dim):subroot->point;
    else
      ret = subroot->right!=NULL ? findHelper(query, subroot->right, (dim + 1)%Dim):subroot->point;

    // check subroot point
    if (shouldReplace(query, ret, subroot->point))
      ret = subroot->point;

    // calculate the distance from query point to the current splitting plane
    double disP = query[dim]-subroot->point[dim];
    disP = disP*disP;
    double dis = getDistance(query, ret);

    // recursively check the other path
    if (dis >= disP)
    {
      if (isSmall)
        temp = subroot->right!=NULL ? findHelper(query, subroot->right, (dim + 1)%Dim):subroot->point;
      else
        temp = subroot->left!=NULL ? findHelper(query, subroot->left, (dim + 1)%Dim):subroot->point;

      if (shouldReplace(query, ret, temp))
        ret = temp;
    }

    return ret;
}

template <int Dim>
Point<Dim> KDTree<Dim>::findNearestNeighbor(const Point<Dim>& query) const
{
    /**
     * @todo Implement this function!
     */
    return findHelper(query, root, 0);
}
