#pragma once

#include <stdlib.h>
#include <string>
#include "Base.h"

using namespace std;

class Derived: public Base
{
  public:
    string foo();
    string bar();
    virtual ~Derived();
};
