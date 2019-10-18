/* Your code here! */
#include <vector>
#include "dsets.h"
#include <iostream>

using namespace std;

/*
  DisjointSets::addelements
    DESCRIPTION: add num elements into the back of the Disjoint Sets
    INPUT: int num: the number of emelents added
    OUTUT: NONE
    SIDEEFFECTS: NONE
*/
void DisjointSets::addelements(int num)
{
  for (int i = 0; i < num; i++)
  {
    elements_.push_back(-1);
  }
}

/*
  DisjointSets::find
    DESCRIPTION: find the root of the uptree elem resides
    INPUT: int elem: the element whose root we want to find
    OUTUT: the root of the input
    SIDEEFFECTS: compress the route for the uptree
*/
int DisjointSets::find(int elem)
{
  // base case
  if (elements_[elem] < 0)
    return elem;

  int retVal = find(elements_[elem]);
  elements_[elem] = retVal;
  return retVal;
}

/*
  DisjointSets::setunion
    DESCRIPTION: set union of two disjoint sets by size (larger one should be
                                                        the new root)
    INPUT: int a: first element whose set we want to set union
           int b: second element whose set we want to set union
    OUTUT: NONE
    SIDEEFFECTS: set union for the two desired sets
*/
void DisjointSets::setunion(int a, int b)
{
  int temp_a = find(a);
  int temp_b = find(b);
  if (temp_a == temp_b) // a  and b already in the same union
  {
    // cout<<"Buu"<<endl;
    return;
  }
  if (elements_[temp_a] <= elements_[temp_b])
  {
    elements_[temp_a] += elements_[temp_b]; // update the size of uptree
    elements_[temp_b] = temp_a;
  }
  else
  {
    elements_[temp_b] += elements_[temp_a]; // update the size of uptree
    elements_[temp_a] = temp_b;
  }
}

/*
  DisjointSets::size
    DESCRIPTION: return the size of the set elem resides
    INPUT: int elem: want to know the size of the set int elem resides
    OUTUT: the size of the disjoint set
    SIDEEFFECTS: NONE
*/
int DisjointSets::size(int elem)
{
  int temp = find(elem);
  return (-1)*elements_[temp];
}
