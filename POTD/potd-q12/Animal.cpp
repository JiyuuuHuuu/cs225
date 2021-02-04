// Animal.cpp
#include "Animal.h"

using namespace std;

Animal::Animal()
{
  type_ = "cat";
  food_ = "fish";
}

Animal::Animal(string type, string food)
{
  type_ = type;
  food_ = food;
}

string Animal::getType()
{
  return type_;
}

void Animal::setType(string input)
{
  type_ = input;
}

string Animal::getFood()
{
  return food_;
}

void Animal::setFood(string input)
{
  food_ = input;
}

string Animal::print()
{
  string output = "I am a ";
  output += type_;
  output += ".";
  return output;
}
