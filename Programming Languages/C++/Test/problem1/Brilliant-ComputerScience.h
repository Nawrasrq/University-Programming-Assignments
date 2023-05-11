#include "Paradisio-Beings.h"

class Brilliant_ComputerScience : public Paradisio_Beings{
public:
    Brilliant_ComputerScience(string name, int age, int weight){
        set_values(name, age, weight);
    }

    void eat();
    void talk();
    void walk();
    void think();

};
