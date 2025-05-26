#pragma once
#include "Ship.h"
#include "Projectile.h"
#include <vector>

class MainShip : public Ship {
private:
    float fireCooldown; // Timp între două focuri

public:
    MainShip(float x, float y, bool teamLeft);

    void fire(std::vector<Projectile*>& projectiles) override;
    void update(float dt) override;
};
