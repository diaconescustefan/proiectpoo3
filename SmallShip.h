#pragma once
#ifndef SMALLSHIP_H
#define SMALLSHIP_H

#include "Ship.h"

class SmallShip : public Ship {
public:
    SmallShip(float x, float y, sf::Color c);
    virtual ~SmallShip();

    void draw(sf::RenderWindow& window) const override;
};

#endif
