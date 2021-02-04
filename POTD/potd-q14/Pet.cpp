// Pet.cpp
#include "Pet.h"

using namespace std;

Pet::Pet():Animal("cat", "fish")
{
  name_ = "Fluffy";
  owner_name_ = "Cinda";
}

Pet::Pet(string type, string food, string name, string owner):Animal(type, food)
{
  name_ = name;
  owner_name_ = owner;
}

string Pet::getName()
{
  return name_;
}

void Pet::setName(string input)
{
  name_ = input;
}

string Pet::getFood()
{
  return food_;
}

void Pet::setFood(string input)
{
  food_ = input;
}

string Pet::getOwnerName()
{
  return owner_name_;
}

void Pet::setOwnerName(string input)
{
  owner_name_ = input;
}

string Pet::print()
{
  string output = "My name is ";
  output += name_;
  return output;
}
