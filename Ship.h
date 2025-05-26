#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Projectile.h"

class Ship {
protected:
    int health;
    bool alive;
    float deathTimer;
    sf::Vector2f position;
    sf::Color color;
    sf::Vector2f size;
    bool teamLeft; // true = echipa stanga, false = dreapta

public:
    Ship(int hp, float x, float y, sf::Color c, sf::Vector2f sz, bool leftTeam);
    virtual void fire(std::vector<Projectile*>& projectiles) = 0;
    virtual void draw(sf::RenderWindow& window);
    virtual void update(float dt);
    void move(float dx, float dy);
    void hit(int dmg);
    bool isAlive() const;
    int getHealth() const;
    sf::Vector2f getPosition() const;
    sf::FloatRect getBounds() const;
    bool isLeftTeam() const;
};
