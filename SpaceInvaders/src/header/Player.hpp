#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Bullet.hpp"

class Player {
public:
    Player();
    void handleInput(float dt);
    void tryShoot(std::vector<Bullet>& bullets);
    sf::RectangleShape shape;

private:
    float speed = 300.f;
    float shootCooldown = 0.f;
};