// your code here
#include "Foo.h"
using namespace potd;
using namespace std;


namespace potd
{
  class Bar
  {
    private:
      potd::Foo * f_;

    public:
      Bar(string input);
      Bar(const Bar &);
      ~Bar();
      Bar & operator=(const Bar &);
      string get_name();
  };
}
