// your code here
#include "Bar.h"
using namespace potd;
using namespace std;


Bar::Bar(string input)
{
  f_ = new Foo(input);
}

Bar::Bar(const Bar & that)
{
  f_ = new Foo(that.f_->get_name());
}

Bar::~Bar()
{
  delete f_;
}

Bar & Bar::operator=(const Bar & that)
{
  this->~Bar();
  f_ = new Foo(*(that.f_));
  //*f_ = *(that.f_);
  return * this;
}

string Bar::get_name()
{
  return f_->get_name();
}
