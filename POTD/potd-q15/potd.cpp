#include "potd.h"
#include <iostream>

using namespace std;

string stringList(Node *head)
{
    // your code here!
    if (head == NULL)
    {
      return "Empty list";
    }

    string output = "";
    int index = 0;
    while(head != NULL)
    {
      if(index != 0)
      {
        output += " -> ";
      }
      output += "Node ";
      output += to_string(index);
      index++;
      output += ": ";
      output += to_string(head->data_);
      head = head->next_;
    }

    return output;
}
