// Copyright 2022 UNN-IASR

#include "Automata.h"

#include <iostream>
#include <locale>

int main() {
    std::setlocale(LC_ALL, "");

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
