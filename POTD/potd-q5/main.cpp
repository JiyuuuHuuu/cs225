// your code here

#include "q5.h"
#include <stdlib.h>
#include <string>
#include <iostream>

int main()
{
  Food apple;
  apple.set_name("apple");
  apple.set_quantity(5);

  std::cout<<"You have "<<apple.get_quantity()<<" "<<apple.get_name()<<"s."<<std::endl;

  increase_quantity(&apple);
  std::cout<<"You have "<<apple.get_quantity()<<" "<<apple.get_name()<<"s."<<std::endl;

  return 0;
}
