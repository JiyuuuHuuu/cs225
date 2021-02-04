#include <iostream>
#include <string>
#include <stack>

using namespace std;

bool isValid(string input)
{
    stack<char> st;
    while (input.length() != 0)
    {
      //cout<<input.length()<<endl;
      if (input.front() == '(' || input.front() == '{' || input.front() == '[')
      {
        st.push(input.front());
        input.erase(input.begin());
      }
      else if (input.front() == ')')
      {
        if (st.size() == 0)
          return false;
        if (st.top() != '(')
          return false;
        st.pop();
        input.erase(input.begin());
      }
      else if (input.front() == '}')
      {
        if (st.size() == 0)
          return false;
        if (st.top() != '{')
          return false;
        st.pop();
        input.erase(input.begin());
      }
      else if (input.front() == ']')
      {
        if (st.size() == 0)
          return false;
        if (st.top() != '[')
          return false;
        st.pop();
        input.erase(input.begin());
      }
      else
      {
        input.erase(input.begin());
      }
    }
    if (st.size() != 0)
      return false;
    return true;    // modify this!
}
