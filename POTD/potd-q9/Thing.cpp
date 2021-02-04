// Your code here!
#include "Thing.h"
using namespace potd;
using namespace std;


Thing::Thing(int input)
{
  properties_ = new string[input];
  values_ = new string[input];
  props_ct_ = 0;
  props_max_ = input;
}

Thing::Thing(const Thing & input)
{
  properties_ = new string[input.props_max_];
  values_ = new string[input.props_max_];
  for (int i = 0; i < input.props_ct_; i++)
  {
    properties_[i] = input.properties_[i];
    values_[i] = input.values_[i];
  }
  props_ct_ = input.props_ct_;
  props_max_ = input.props_max_;
}

Thing & Thing::operator=(const Thing & input)
{
  if(this != &input)
  {
    _destroy();
    properties_ = new string[input.props_max_];
    values_ = new string[input.props_max_];
    for (int i = 0; i < input.props_ct_; i++)
    {
      properties_[i] = input.properties_[i];
      values_[i] = input.values_[i];
    }
    props_ct_ = input.props_ct_;
    props_max_ = input.props_max_;
  }
  return * this;
}

Thing::~Thing()
{
  _destroy();
}

int Thing::set_property(string name, string value)
{
  for (int i = 0; i < props_ct_; i++)
  {
    if(properties_[i] == name)
    {
      values_[i] = value;
      return i;
    }
  }
  if (props_ct_ >= props_max_)
  {
    return -1;
  }
  properties_[props_ct_] = name;
  values_[props_ct_] = value;
  props_ct_++;
  return props_ct_ - 1;
}

string Thing::get_property(string input)
{
  for (int i = 0; i < props_ct_; i++)
  {
    if(properties_[i] == input)
    {
      return values_[i];
    }
  }
  return "";
}

void Thing::_copy(const Thing & input)
{
  properties_ = input.properties_;
  values_ = input.values_;
  props_ct_ = input.props_ct_;
  props_max_ = input.props_max_;
}

void Thing::_destroy()
{
  delete[] properties_;
  delete[] values_;
  props_ct_ = 0;
  props_max_ = 0;
}
