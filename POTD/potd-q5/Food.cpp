#include "Food.h"
#include <stdlib.h>


// Your code here
Food::Food()
{
  name_ = "No name";
  quantity_ = 0;
}

std::string Food::get_name()
{
  return name_;
}

void Food::set_name(std::string input)
{
  name_ = input;
}

int Food::get_quantity()
{
  return quantity_;
}

void Food::set_quantity(int input)
{
  quantity_ = input;
}
