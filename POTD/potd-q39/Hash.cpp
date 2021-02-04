#include <vector>
#include <string>
#include "Hash.h"

using namespace std;

int hashFunction(string s, int M)
{
   // Your Code Here
   //hash function to sum up the ASCII characters of the letters of the string
   int sum = 0;
   for (int i = 0; i < (int)s.length(); i++)
   {
     sum += (int)s[i];
   }

   while(sum >= M)
   {
     sum -= M;
   }

   return sum;
}

int countCollisions (int M, vector<string> inputs)
{
	int collisions = 0;
	// Your Code Here
  int check[M];
  for (int i = 0; i < M; i++)
  {
    check[i] = 0;
  }

  for (string i : inputs)
  {
    int temp = hashFunction(i, M);
    if (check[temp])
    {
      collisions++;
    }
    check[temp] = 1;
  }
	return collisions;
}
