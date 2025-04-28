// Copyright 2022 GHA Test Team

#include <gtest/gtest.h>
#include "Automata.h"


TEST(AutomataTest, InitialStateIsOff) {
    Automata machine;
    EXPECT_EQ(machine.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnOn) {
    Automata machine;
    machine.on();
    EXPECT_EQ(machine.getState(), STATES::WAIT);
}


TEST(AutomataTest, TurnOnWhenAlreadyOn) {
    Automata machine;
    machine.on();
    machine.on(); 
    EXPECT_EQ(machine.getState(), STATES::WAIT);
}


TEST(AutomataTest, TurnOffFromWait) {
    Automata machine;
    machine.on();
    machine.off();
    EXPECT_EQ(machine.getState(), STATES::OFF);
}

TEST(AutomataTest, TurnOffInvalidState) {
    Automata machine;
    machine.on();
    machine.coin(50);
    machine.off();
    EXPECT_NE(machine.getState(), STATES::OFF);
}


TEST(AutomataTest, InsertCoinInWait) {
    Automata machine;
    machine.on();
    machine.coin(30);
    EXPECT_EQ(machine.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, InsertCoinInAccept) {
    Automata machine;
    machine.on();
    machine.coin(30);
    machine.coin(20);
    EXPECT_EQ(machine.getState(), STATES::ACCEPT);
}

TEST(AutomataTest, ChooseWithoutMoney) {
    Automata machine;
    machine.on();
    machine.choice(1); 
    EXPECT_EQ(machine.getState(), STATES::WAIT);
}

TEST(AutomataTest, SuccessfulChoice) {
    Automata machine;
    machine.on();
    machine.coin(100);
    machine.choice(1);
    EXPECT_EQ(machine.getState(), STATES::WAIT);
}

TEST(AutomataTest, InvalidDrinkChoice) {
    Automata machine;
    machine.on();
    machine.coin(100);
    machine.choice(10);
    EXPECT_EQ(machine.getState(), STATES::WAIT);
}