// Copyright 2022 UNN-IASR

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

    void check(int drinkIndex);
    void cook(std::string drinkName);
    void finish();
};
