#include <SFML/Graphics.hpp>
#include <vector>
#include <algorithm>
#include <iostream>
#include "MainShip.h"
#include "CircleShip.h"
#include "TriangleShip.h"
#include "Projectile.h"
#include "GameManager.h"

// 🔷 TEMPLATE 1: verifică coliziune între două entități care au getBounds()
template <typename T1, typename T2>
bool verificaColiziune(T1* a, T2* b) {
    return a->getBounds().intersects(b->getBounds());
}

// 🔷 TEMPLATE 2: update generic pentru vectori de obiecte
template <typename T>
void updateAll(std::vector<T*>& obiecte, float dt) {
    for (auto* o : obiecte)
        o->update(dt);
}

// 🔧 Desenează bara de viață
void drawHealthBar(sf::RenderWindow& window, Ship* ship) {
    if (!ship->isAlive()) return;

    float maxHealth = 5.f;
    if (ship->getHealth() <= 2) maxHealth = 2.f;

    float ratio = ship->getHealth() / maxHealth;
    float width = 40.f;

    sf::Vector2f pos = ship->getPosition();
    pos.y -= 10;

    sf::RectangleShape back(sf::Vector2f(width, 6));
    back.setFillColor(sf::Color(60, 60, 60));
    back.setPosition(pos);

    sf::RectangleShape front(sf::Vector2f(width * ratio, 6));
    front.setFillColor(sf::Color::Green);
    front.setPosition(pos);

    window.draw(back);
    window.draw(front);
}

// 🔫 Coliziuni
void handleCollisions(std::vector<Projectile*>& projectiles, std::vector<Ship*>& ships) {
    for (auto* proj : projectiles) {
        for (auto* ship : ships) {
            if (ship->isAlive() &&
                verificaColiziune(ship, proj) &&
                ship->isLeftTeam() != proj->isFromLeft()) {

                ship->hit(1);
                proj->markForRemoval();
                GameManager::getInstance()->adaugaScor(10); // scor pe lovitură
            }
        }
    }

    projectiles.erase(std::remove_if(projectiles.begin(), projectiles.end(),
        [](Projectile* p) {
            if (p->shouldRemove()) { delete p; return true; }
            return false;
        }), projectiles.end());
}

// ⚔️ Verifică dacă o echipă a pierdut
bool toateNaveleMoarte(const std::vector<Ship*>& ships, bool echipaStanga) {
    for (auto* ship : ships) {
        if (ship->isLeftTeam() == echipaStanga && ship->isAlive())
            return false;
    }
    return true;
}

int main() {
    sf::RenderWindow window(sf::VideoMode(800, 600), "Space Battle");
    window.setFramerateLimit(60);

    // Nave echipa stânga
    MainShip leftMain(100.f, 250.f, true);
    CircleShip leftCircle(130.f, 100.f, true);
    TriangleShip leftTriangle(130.f, 300.f, true);

    // Nave echipa dreapta
    MainShip rightMain(700.f, 250.f, false);
    CircleShip rightCircle(630.f, 400.f, false);
    TriangleShip rightTriangle(630.f, 150.f, false);

    std::vector<Ship*> allShips = {
        &leftMain, &leftCircle, &leftTriangle,
        &rightMain, &rightCircle, &rightTriangle
    };

    std::vector<Projectile*> projectiles;
    sf::Clock clock;

    while (window.isOpen()) {
        sf::Event event;
        while (window.pollEvent(event)) {
            if (event.type == sf::Event::Closed)
                window.close();
        }

        float dt = clock.restart().asSeconds();
        float speed = 200.f * dt;

        // === CONTROALE STÂNGA ===
        sf::FloatRect futureL = leftMain.getBounds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) futureL.top -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) futureL.top += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) futureL.left -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) futureL.left += speed;

        bool blocatL = false;
        if (leftCircle.isAlive() && futureL.intersects(leftCircle.getBounds())) blocatL = true;
        if (leftTriangle.isAlive() && futureL.intersects(leftTriangle.getBounds())) blocatL = true;

        if (!blocatL) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) leftMain.move(0, -speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) leftMain.move(0, speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) leftMain.move(-speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) leftMain.move(speed, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
            leftMain.fire(projectiles);

        // === CONTROALE DREAPTA ===
        sf::FloatRect futureR = rightMain.getBounds();
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) futureR.top -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) futureR.top += speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) futureR.left -= speed;
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) futureR.left += speed;

        bool blocatR = false;
        if (rightCircle.isAlive() && futureR.intersects(rightCircle.getBounds())) blocatR = true;
        if (rightTriangle.isAlive() && futureR.intersects(rightTriangle.getBounds())) blocatR = true;

        if (!blocatR) {
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) rightMain.move(0, -speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) rightMain.move(0, speed);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) rightMain.move(-speed, 0);
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) rightMain.move(speed, 0);
        }

        if (sf::Keyboard::isKeyPressed(sf::Keyboard::Enter))
            rightMain.fire(projectiles);

        // === UPDATE ===
        updateAll(allShips, dt);
        updateAll(projectiles, dt);

        // === FIRE AUTOMAT ===
        leftCircle.fire(projectiles);
        leftTriangle.fire(projectiles);
        rightCircle.fire(projectiles);
        rightTriangle.fire(projectiles);

        // === COLIZIUNI ===
        handleCollisions(projectiles, allShips);

        // === DESENARE ===
        window.clear();
        for (auto* s : allShips) {
            s->draw(window);
            drawHealthBar(window, s);
        }
        for (auto* p : projectiles)
            p->draw(window);
        window.display();

        // === VICTORIE ===
        if (toateNaveleMoarte(allShips, true)) {
            std::cout << "!!!!Echipa DREAPTA a castigat!\n";
            GameManager::getInstance()->afiseazaScor();
            window.close();
        }

        if (toateNaveleMoarte(allShips, false)) {
            std::cout << "!!!!Echipa STANGA a castigat!\n";
            GameManager::getInstance()->afiseazaScor();
            window.close();
        }
    }

    for (auto* p : projectiles)
        delete p;

    return 0;
}
