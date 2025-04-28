#include "Automata.h"
#include <thread>
#include <chrono>

using namespace std;

Automata::Automata() : cash(0), state(STATES::OFF) {
    menu = { "Кофе", "Чай", "Молоко", "Сок" };
    prices = { 50, 40, 60, 70 };
}

void Automata::returnChange() {
    if (cash > 0) {
        cout << "  Возвращено сдачи: " << cash << " единиц\n";
        cash = 0;
    }
}

void Automata::on() {
    if (state == STATES::OFF) {
        state = STATES::WAIT;
        cout << "  Автомат включён. Ожидание клиента...\n";
    }
    else {
        cout << "ОШИБКА: Автомат уже включён.\n";
    }
}

void Automata::off() {
    if (state == STATES::WAIT) {
        returnChange();
        state = STATES::OFF;
        cout << "  Автомат выключен.\n";
    }
    else {
        cout << "ОШИБКА: Выключение возможно только из состояния ожидания.\n";
    }
}

void Automata::coin(int amount) {
    if (state == STATES::WAIT || state == STATES::ACCEPT) {
        cash += amount;
        state = STATES::ACCEPT;
        cout << "  Внесено " << amount << " единиц. Текущий баланс: " << cash << "\n";
    }
    else {
        cout << "ОШИБКА: Невозможно внести деньги в текущем состоянии.\n";
    }
}

void Automata::getMenu() {
    cout << "МЕНЮ НАПИТКОВ:\n";
    for (size_t i = 0; i < menu.size(); ++i) {
        cout << (i + 1) << ". " << menu[i] << " — " << prices[i] << " единиц\n";
    }
}

STATES Automata::getState() {
    return state;
}

void Automata::choice(int drinkNumber) {
    if (state == STATES::ACCEPT) {
        if (drinkNumber <= 0 || static_cast<size_t>(drinkNumber) > menu.size()) {
            cout << "ОШИБКА: Неверный выбор напитка.\n";
            cancel();
        }
        else {
            state = STATES::CHECK;
            check(drinkNumber - 1);
        }
    }
    else {
        cout << "ОШИБКА: Нельзя выбрать напиток сейчас.\n";
    }
}

void Automata::check(int drinkIndex) {
    if (state == STATES::CHECK) {
        if (cash >= prices[drinkIndex]) {
            cash -= prices[drinkIndex];
            cook(menu[drinkIndex]);
        }
        else {
            cout << "ОШИБКА: Недостаточно средств. Требуется: " << prices[drinkIndex] << ", доступно: " << cash << "\n";
            cancel();
        }
    }
    else {
        cout << "ОШИБКА: Неверное состояние для проверки.\n";
    }
}

void Automata::cancel() {
    if (state == STATES::ACCEPT || state == STATES::CHECK) {
        cout << "  Операция отменена. Возврат в состояние ожидания.\n";
        returnChange();
        state = STATES::WAIT;
    }
    else {
        cout << "ОШИБКА: Нельзя отменить операцию в текущем состоянии.\n";
    }
}

void Automata::cook(string drinkName) {
    if (state == STATES::CHECK || state == STATES::COOK) {
        state = STATES::COOK;
        cout << "  Приготовление напитка: " << drinkName << "...\n";
        this_thread::sleep_for(chrono::seconds(5));
        cout << "  Напиток " << drinkName << " готов!\n";
        finish();
    }
    else {
        cout << "ОШИБКА: Невозможно начать приготовление в текущем состоянии.\n";
    }
}

void Automata::finish() {
    if (state == STATES::COOK) {
        cout << "  Обслуживание завершено. Ожидание следующего клиента.\n";
        state = STATES::WAIT;
    }
    else {
        cout << "ОШИБКА: Нельзя завершить приготовление, если оно не начато.\n";
    }
}