#include "Automata.h"
#include <thread>
#include <chrono>

using namespace std;

Automata::Automata() : cash(0), state(STATES::OFF) {
    menu = { "����", "���", "������", "���" };
    prices = { 50, 40, 60, 70 };
}

void Automata::returnChange() {
    if (cash > 0) {
        cout << "  ���������� �����: " << cash << " ������\n";
        cash = 0;
    }
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        cout << "  ������� �������. �������� �������...\n";
    }
    else {
        cout << "������: ������� ��� �������.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        returnChange();
        state = STATES::OFF;
        cout << "  ������� ��������.\n";
    }
    else {
        cout << "������: ���������� �������� ������ �� ��������� ��������.\n";
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAIT || state == STATES::ACCEPT) {
        cash += amount;
        state = STATES::ACCEPT;
        cout << "  ������� " << amount << " ������. ������� ������: " << cash << "\n";
    }
    else {
        cout << "������: ���������� ������ ������ � ������� ���������.\n";
    }
}

void Automata::getMenu() {
    cout << "���� ��������:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        cout << (i + 1) << ". " << menu[i] << " � " << prices[i] << " ������\n";
    }
}

STATES Automata::getState() {
    return state;
}

void Automata::choice(int drinkNumber) {
    if (state == STATES::ACCEPT) {
        if (drinkNumber <= 0 || static_cast<size_t>(drinkNumber) > menu.size()) {
            cout << "������: �������� ����� �������.\n";
            cancel();
        }
        else {
            state = STATES::CHECK;
            check(drinkNumber - 1);
        }
    }
    else {
        cout << "������: ������ ������� ������� ������.\n";
    }
}

void Automata::check(int drinkIndex) {
    if (state == STATES::CHECK) {
        if (cash >= prices[drinkIndex]) {
            cash -= prices[drinkIndex];
            cook(menu[drinkIndex]);
        }
        else {
            cout << "������: ������������ �������. ���������: " << prices[drinkIndex] << ", ��������: " << cash << "\n";
            cancel();
        }
    }
    else {
        cout << "������: �������� ��������� ��� ��������.\n";
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        cout << "  �������� ��������. ������� � ��������� ��������.\n";
        returnChange();
        state = STATES::WAIT;
    }
    else {
        cout << "������: ������ �������� �������� � ������� ���������.\n";
    }
}

void Automata::cook(string drinkName) {
    if (state == STATES::CHECK || state == STATES::COOK) {
        state = STATES::COOK;
        cout << "  ������������� �������: " << drinkName << "...\n";
        this_thread::sleep_for(chrono::seconds(5));
        cout << "  ������� " << drinkName << " �����!\n";
        finish();
    }
    else {
        cout << "������: ���������� ������ ������������� � ������� ���������.\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        cout << "  ������������ ���������. �������� ���������� �������.\n";
        state = STATES::WAIT;
    }
    else {
        cout << "������: ������ ��������� �������������, ���� ��� �� ������.\n";
    }
}