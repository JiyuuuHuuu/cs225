// Pet.h
#include "Animal.h"

using namespace std;

class Pet: public Animal
{
  private:
    string name_;
    string owner_name_;

  public:
    Pet();
    Pet(string type, string food, string name, string owner);
    string getName();
    void setName(string input);
    string getFood();
    void setFood(string input);
    string getOwnerName();
    void setOwnerName(string input);
    string print();
};
