#include "Projectile.h"

Projectile::Projectile(sf::Vector2f pos, sf::Vector2f dir, sf::Color color, float spd)
    : direction(dir), speed(spd) {
    shape.setRadius(5.f);
    shape.setFillColor(color);
    shape.setPosition(pos);
    fromLeft = dir.x > 0;
}

void Projectile::update(float dt) {
    sf::Vector2f velocity = direction * speed * dt;

    // 🔒 Asigurare că se mișcă doar pe X
    velocity.y = 0;

    shape.move(velocity);
}


void Projectile::draw(sf::RenderWindow& window) const {
    window.draw(shape);
}

sf::FloatRect Projectile::getBounds() const {
    return shape.getGlobalBounds();
}

void Projectile::markForRemoval() {
    removeFlag = true;
}

bool Projectile::shouldRemove() const {
    return removeFlag;
}

bool Projectile::isFromLeft() const {
    return fromLeft;
}
