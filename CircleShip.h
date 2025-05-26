#pragma once
#include "Ship.h"

class CircleShip : public Ship {
private:
    float timer;

public:
    CircleShip(float x, float y, bool teamLeft);
    void fire(std::vector<Projectile*>& projectiles) override;
    void update(float dt) override;
};
