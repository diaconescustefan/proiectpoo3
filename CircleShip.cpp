#include "CircleShip.h"

CircleShip::CircleShip(float x, float y, bool teamLeft)
    : Ship(2, x, y, sf::Color::Red, { 40.f, 40.f }, teamLeft), timer(0.f) {
}

void CircleShip::update(float dt) {
    Ship::update(dt);
    timer += dt;
}

void CircleShip::fire(std::vector<Projectile*>& projectiles) {
    if (!alive || timer < 3.f) return;
    sf::Vector2f dir = (teamLeft) ? sf::Vector2f(1.f, 0.f) : sf::Vector2f(-1.f, 0.f);
    projectiles.push_back(new Projectile(position, dir, sf::Color::Red, 300.f));
    timer = 0.f;
}
