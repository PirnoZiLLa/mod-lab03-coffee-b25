#include <string>
#include <vector>
#include <iostream>

using namespace std;

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
    vector<string> menu;
    vector<int> prices;

    void check(int drinkIndex);
    void cook(string drinkName);
    void finish();
};



