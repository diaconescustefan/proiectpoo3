#include "GameManager.h"

// Inițializare pointer static
GameManager* GameManager::instance = nullptr;

// Constructorul privat
GameManager::GameManager() : scor(0) {}

// Returnează instanța singleton
GameManager* GameManager::getInstance() {
    if (!instance)
        instance = new GameManager();
    return instance;
}

// Adaugă la scor
void GameManager::adaugaScor(int valoare) {
    scor += valoare;
}

// Returnează scorul
int GameManager::getScor() const {
    return scor;
}

// Afișează scorul
void GameManager::afiseazaScor() const {
    std::cout << "Scorul actual: " << scor << "\n";
}
