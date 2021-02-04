#include "potd.h"
#include "stdlib.h"

using namespace std;

// Your code here!
double sum(vector<double>::iterator start, vector<double>::iterator end)
{
  vector<double>::iterator curr1 = start;
  vector<double>::iterator curr2 = end - 1;

  //cout<<*curr1<<"  "<<*curr2<<endl;

  if (curr1 == curr2)
  {
    return *curr1;
  }

  if (next(curr1, 1) == curr2)
  {
    return (*curr1 + *curr2);
  }

  double temp_sum = (*curr1 + *curr2);
  return sum(curr1 + 1, curr2) + temp_sum;
}

vector<double>::iterator max_iter(vector<double>::iterator start, vector<double>::iterator end)
{
  vector<double>::iterator curr = start;
  vector<double>::iterator ret = start;

  while (curr != end)
  {
    if (*ret < *curr)
      ret = curr;

    curr++;
  }

  return ret;
}

void sort_vector(vector<double>::iterator start, vector<double>::iterator end)
{
  if (start == end)
    return;

  swap(*start, *max_iter(start, end));

  sort_vector(start + 1, end);
}
