/* Your code here! */

#include <string>



std::string hello()
{
  std::string name, age, output;
  name = "Jiyu";
  age = "19";
  output = "Hello world! My name is ";
  output += name;
  output += " and I am "; //.push_back(" and I am ");
  output += age;//.push_back(age);
  output += " years old.";//.push_back(" years old.")

  return output;
}
