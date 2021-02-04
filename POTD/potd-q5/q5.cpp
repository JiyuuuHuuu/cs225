
#include "q5.h"
// your code here

void increase_quantity(Food * input)
{
  input->set_quantity(input->get_quantity() + 1);
}
