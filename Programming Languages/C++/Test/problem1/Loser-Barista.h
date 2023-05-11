#include "Paradisio-Beings.h"

class Loser_Barista : public Paradisio_Beings{
public:
    Loser_Barista(string name, int age, int weight){
        set_values(name, age, weight);
    }

    void eat();
    void talk();
    void walk();
    void think();
};


