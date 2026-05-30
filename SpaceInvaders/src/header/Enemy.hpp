#pragma once
#include <SFML/Graphics.hpp>

class Enemy {
public:
    Enemy(float x, float y);
    sf::RectangleShape shape;
};