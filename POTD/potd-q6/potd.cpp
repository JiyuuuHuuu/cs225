// your code here!
#include <stdlib.h>
#include <iterator>
#include "potd.h"
#include <cmath>

int getSize(int *arr);

int * potd::raise(int *arr)
{
  int * output = new int(getSize(arr));
  int i = 0;
  for (i = 0; i < getSize(arr) - 2; i++)
  {
    output[i] = pow(arr[i], arr[i + 1]);
  }
  output[i] = arr[i];
  output[i + 1] = arr[i + 1];
  return output;
}


int getSize(int *arr)
{
    int i = 0;
    while(arr[i]>0){
        i++;
    }
    return i + 1;
}
