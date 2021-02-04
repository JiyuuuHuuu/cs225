// Your code here
#pragma once
#include <string>


class Food
{
  private:
    std::string name_;
    int quantity_;

  public:
    Food();
    std::string get_name();
    void set_name(std::string input);
    int get_quantity();
    void set_quantity(int input);
};
