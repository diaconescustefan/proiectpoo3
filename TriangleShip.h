#pragma once
#include "Ship.h"

class TriangleShip : public Ship {
private:
    float timer;

public:
    TriangleShip(float x, float y, bool teamLeft);
    void fire(std::vector<Projectile*>& projectiles) override;
    void update(float dt) override;
};
