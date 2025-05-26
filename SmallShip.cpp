#include "SmallShip.h"

SmallShip::SmallShip(float x, float y, sf::Color c)
    : Ship(2, x, y, c, sf::Vector2f(50.0f, 30.0f)) {
}

SmallShip::~SmallShip() {}

void SmallShip::draw(sf::RenderWindow& window) const {
    sf::RectangleShape shape(size);
    shape.setFillColor(alive ? color : sf::Color(100, 100, 100));
    shape.setPosition(position.x, position.y);
    window.draw(shape);
}