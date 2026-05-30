#include "../header/Enemy.hpp"

Enemy::Enemy(float x, float y) {
    shape.setSize({40.f, 30.f});
    shape.setFillColor(sf::Color::Green);
    shape.setPosition({x, y});
}