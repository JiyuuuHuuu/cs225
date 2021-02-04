// Animal.h
#include <iostream>
#include <string>

using namespace std;

class Animal
{
  private:
    string type_;

  protected:
    string food_;

  public:
    Animal();
    Animal(string type, string food);
    string getType();
    void setType(string input);
    string getFood();
    void setFood(string input);
    virtual string print();
};
