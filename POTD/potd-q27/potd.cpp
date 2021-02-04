// Your code here
#include "potd.h"

using namespace std;

string getFortune(const string &s)
{
  if (s.size()%5 == 0)
    return "Syntax error: Your question cannot be answered";
  else if (s.size()%5 == 1)
    return "Segmentation fault: Your question cannot be answered";
  else if (s.size()%5 == 2)
    return "Linker command error: The answer cannot be generated";
  else if (s.size()%5 == 3)
    return "Question undefined: cannot be answered";
  else
    return "Input out of size";
}
