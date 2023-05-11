#include "Paradisio-Beings.cpp"

int main(){
    cout << "It is another day in paradise!" << endl;
    Loser_Barista lb("Caffeinated", 44, 55);
    Brilliant_ComputerScience bcs("Spiffy-Diffy", 33, 41 );
    Paychology_Major pm("Droopy", 11, 22);
    lb.talk();
    bcs.walk();
    pm.think();

    Paradisio_Beings *pb1 = &lb;
    Paradisio_Beings *pb2 = &bcs;
    Paradisio_Beings *pb3 = &pm;
    
    pb1->eat();  // Should show Loser-Barista eating
    pb2->eat();  // Should show Brilliant-ComputerScience eating
    pb3->eat();  // Should show Paychology-Major eating
    cout << "COP 4020 is cool!" << endl;

    return 0;
}
