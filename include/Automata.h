// Copyright 2022 UNN-IASR

#ifndef INCLUDE_AUTOMATA_H_
#define INCLUDE_AUTOMATA_H_

#include <string>
#include <vector>
#include <iostream>

enum class STATES {
    OFF,
    WAIT,
    ACCEPT,
    CHECK,
    COOK
};

class Automata {
 public:
    Automata();

    void on();
    void off();
    void coin(int amount);
    void getMenu();
    STATES getState();
    void choice(int drinkNumber);
    void cancel();
    void returnChange();

 private:
    int cash;
    STATES state;
    std::vector<std::string> menu;
    std::vector<int> prices;

#endif // INCLUDE_AUTOMATA_H_

    void check(int drinkIndex);
    void cook(std::string drinkName);
    void finish();
};
