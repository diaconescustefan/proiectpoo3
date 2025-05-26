#include "Ship.h"

Ship::Ship(int hp, float x, float y, sf::Color c, sf::Vector2f sz, bool leftTeam) {
    // Salvăm viața
    health = hp;

    // Nava e vie la început
    alive = true;

    // Timpul după care nava dispare când moare
    deathTimer = 0.f;

    // Coordonatele unde apare nava pe ecran
    position.x = x;
    position.y = y;

    // Culoarea navei (ex: albastru, roșu)
    color = c;

    // Dimensiunile navei (lățime și înălțime)
    size = sz;

    // Ce echipă e (true = stânga, false = dreapta)
    teamLeft = leftTeam;
}


void Ship::draw(sf::RenderWindow& window) {
    // Dacă nava este moartă și timerul ei a ajuns la 0, nu o mai desenăm
    if (alive == false && deathTimer <= 0.f) {
        return;
    }

    // Cream o formă de dreptunghi care reprezintă nava
    sf::RectangleShape formaNava;

    // Setăm dimensiunea formei egala cu dimensiunea navei
    formaNava.setSize(size);  // sau: sf::Vector2f(width, height)

    // Setăm poziția formei egala cu poziția navei
    formaNava.setPosition(position);

    // Dacă nava este vie, are culoarea normală
    if (alive == true) {
        formaNava.setFillColor(color);
    }
    // Dacă nava este moartă, o facem gri
    else {
        formaNava.setFillColor(sf::Color(100, 100, 100));  // gri
    }

    // Desenăm forma în fereastra jocului
    window.draw(formaNava);
}

void Ship::update(float dt) {
    if (!alive) deathTimer -= dt;
}

void Ship::hit(int dmg) {
    if (!alive) return;
    health -= dmg;
    if (health <= 0) {
        health = 0;
        alive = false;
        deathTimer = 5.f;
    }
}

bool Ship::isAlive() const { return alive; }
int Ship::getHealth() const { return health; }
sf::Vector2f Ship::getPosition() const { return position; }

sf::FloatRect Ship::getBounds() const {
    return sf::FloatRect(position, size);
}

void Ship::move(float dx, float dy) {
    position += sf::Vector2f(dx, dy);

    // Limitare ecran
    if (position.x < 0) position.x = 0;
    if (position.y < 0) position.y = 0;
    if (position.x + size.x > 800) position.x = 800 - size.x;
    if (position.y + size.y > 600) position.y = 600 - size.y;

    // 🚫 LIMITARE pe jumătate de ecran
    if (teamLeft && position.x + size.x > 400)
        position.x = 400 - size.x;
    if (!teamLeft && position.x < 400)
        position.x = 400;
}


bool Ship::isLeftTeam() const {
    return teamLeft;
}
