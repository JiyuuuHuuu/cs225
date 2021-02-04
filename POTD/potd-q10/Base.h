#pragma once

#include <stdlib.h>
#include <string>

using namespace std;

class Base
{
  public:
    string foo();
    virtual string bar();
    virtual ~Base();
};
