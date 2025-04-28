#include <iostream>
#include "Automata.h"

using namespace std;

int main() {
    setlocale(LC_ALL, "");
    Automata machine;

    machine.on();
    machine.getMenu();
    machine.coin(30); 
    machine.choice(1); 
    machine.coin(60); 
    machine.choice(1); 
    machine.off(); 

    return 0;
}