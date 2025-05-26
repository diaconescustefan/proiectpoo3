#include "MainShip.h"
#include <iostream>

MainShip::MainShip(float x, float y, bool teamLeft)
    : Ship(5, x, y, sf::Color::Blue, { 60.f, 40.f }, teamLeft), fireCooldown(0.f) {
}

void MainShip::update(float dt) {
    Ship::update(dt); // menține logica de bază (viață, moarte)

    if (fireCooldown > 0.f)
        fireCooldown -= dt;
}

void MainShip::fire(std::vector<Projectile*>& projectiles) {
    if (!alive || fireCooldown > 0.f) return;

    // Direcție: orizontal
    sf::Vector2f dir = (teamLeft) ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);

    // Poziție inițială a proiectilului (marginea navei)
    sf::Vector2f start = position;
    start.x += (teamLeft ? size.x : -10.f);
    start.y += size.y / 2 - 5.f; // centrat pe înălțime

    projectiles.push_back(new Projectile(start, dir, sf::Color::Blue, 250.f));
    fireCooldown = 0.25f; // cooldown între focuri
}
