#include<iostream>
#include<map>

using std::cout; 
using std::endl;
using std::cin;
#include <string>
using std::string;
using std::getline;

class Paradisio_Beings {
protected:
    string name;
    int age;
    int weight;
    
public:
    virtual void eat() = 0;
    virtual void talk() = 0;
    virtual void walk() = 0;
    virtual void think() = 0;
    void set_values(string name, int age, int weight);
};