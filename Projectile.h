#pragma once
#include <SFML/Graphics.hpp>

class Projectile {
    sf::CircleShape shape;
    sf::Vector2f direction;
    float speed;
    bool removeFlag = false;
    bool fromLeft;

public:
    Projectile(sf::Vector2f pos, sf::Vector2f dir, sf::Color color, float speed);
    void update(float dt);
    void draw(sf::RenderWindow& window) const;
    sf::FloatRect getBounds() const;
    void markForRemoval();
    bool shouldRemove() const;
    bool isFromLeft() const;
};
