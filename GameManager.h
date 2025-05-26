#pragma once
#pragma once
#include <iostream>

class GameManager {
private:
    static GameManager* instance;
    int scor;

    // Constructor privat
    GameManager();

public:
    static GameManager* getInstance();

    void adaugaScor(int valoare);
    int getScor() const;
    void afiseazaScor() const;
};
