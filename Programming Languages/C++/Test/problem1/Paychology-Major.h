#include "Paradisio-Beings.h"

class Paychology_Major : public Paradisio_Beings{
public:
    Paychology_Major(string name, int age, int weight){
        set_values(name, age, weight);
    }

    void eat();
    void talk();
    void walk();
    void think();
    
};