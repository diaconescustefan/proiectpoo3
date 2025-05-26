#include "TriangleShip.h"

TriangleShip::TriangleShip(float x, float y, bool teamLeft)
    : Ship(2, x, y, sf::Color::Yellow, { 40.f, 40.f }, teamLeft), timer(0.f) {
}

void TriangleShip::update(float dt) {
    Ship::update(dt);
    timer += dt;
}

void TriangleShip::fire(std::vector<Projectile*>& projectiles) {
    if (!alive || timer < 4.f) return;
    sf::Vector2f dir = (teamLeft) ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);
    projectiles.push_back(new Projectile(position, dir, sf::Color::Green, 300.f));
    timer = 0.f;
}
