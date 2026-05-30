#pragma once
#include <SFML/Graphics.hpp>

class Bullet {
public:
    Bullet(float x, float y);
    void update(float dt);
    bool isOffScreen() const;
    sf::RectangleShape shape;

private:
    float speed = 500.f;
};