#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "Player.hpp"
#include "Enemy.hpp"
#include "Bullet.hpp"

class Game {
public:
    Game();
    void run();

private:
    void update(float dt);
    void render();
    void checkCollisions();
    void spawnEnemies();

    sf::RenderWindow window;
    sf::Font font;
    sf::Text scoreText;
    sf::Text gameOverText;

    Player player;
    std::vector<Enemy> enemies;
    std::vector<Bullet> bullets;

    float enemySpeed = 60.f;
    float enemyDir = 1.f;
    float enemyDropDistance = 5.f;

    int score = 0;
    bool gameOver = false;
    bool youWin = false;
};