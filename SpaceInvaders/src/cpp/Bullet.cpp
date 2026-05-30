#include "../header/Bullet.hpp"

Bullet::Bullet(float x, float y) {
    shape.setSize({5.f, 15.f});
    shape.setFillColor(sf::Color::Yellow);
    shape.setPosition({x, y});
}

void Bullet::update(float dt) {
    shape.move({0.f, -speed * dt});
}

bool Bullet::isOffScreen() const {
    return shape.getPosition().y < 0;
}