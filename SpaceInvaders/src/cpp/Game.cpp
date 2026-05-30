#include "../header/Game.hpp"
#include <algorithm>
#include <string>

Game::Game()
    : window(sf::VideoMode({800u, 600u}), "Space Invaders")
    , scoreText(font)
    , gameOverText(font)
{
    window.setFramerateLimit(60);
    font.openFromFile("C:\\Users\\nsa05\\OneDrive\\Desktop\\game\\SpaceInvaders\\assets\\arial.ttf");

    scoreText.setCharacterSize(24);
    scoreText.setFillColor(sf::Color::White);
    scoreText.setPosition({10.f, 10.f});

    gameOverText.setCharacterSize(48);
    gameOverText.setFillColor(sf::Color::Red);
    gameOverText.setPosition({200.f, 250.f});

    spawnEnemies();
}

void Game::spawnEnemies() {
    for (int row = 0; row < 3; row++) {
        for (int col = 0; col < 5; col++) {
            enemies.emplace_back(
                100.f + col * 120.f,
                50.f + row * 70.f
            );
        }
    }
}

void Game::run() {
    sf::Clock clock;
    while (window.isOpen()) {
        float dt = clock.restart().asSeconds();

        while (const auto event = window.pollEvent()) {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        update(dt);
        render();
    }
}

void Game::update(float dt) {
    if (gameOver || youWin) return;

    player.handleInput(dt);
    player.tryShoot(bullets);

    // 총알 업데이트
    for (auto& bullet : bullets) {
        bullet.update(dt);
    }

    // 화면 밖 총알 제거
    bullets.erase(
        std::remove_if(bullets.begin(), bullets.end(),
            [](const Bullet& b) { return b.isOffScreen(); }
        ),
        bullets.end()
    );

    // 적 이동
    bool hitWall = false;
    for (auto& enemy : enemies) {
        enemy.shape.move({enemySpeed * enemyDir * dt, 0.f});
        if (enemy.shape.getPosition().x > 760.f || enemy.shape.getPosition().x < 0.f) {
            hitWall = true;
        }
    }

    if (hitWall) {
        enemyDir *= -1.f;
        for (auto& enemy : enemies) {
            enemy.shape.move({0.f, enemyDropDistance});
        }
    }

    checkCollisions();

    // 게임오버: 적이 바닥에 닿으면
    for (auto& enemy : enemies) {
        if (enemy.shape.getPosition().y > 550.f) {
            gameOver = true;
        }
    }

    // 클리어
    if (enemies.empty()) {
        youWin = true;
    }
}

void Game::checkCollisions() {
    std::vector<int> bulletsToRemove;
    std::vector<int> enemiesToRemove;

    for (int i = 0; i < (int)bullets.size(); i++) {
        for (int j = 0; j < (int)enemies.size(); j++) {
            if (bullets[i].shape.getGlobalBounds().findIntersection(
                enemies[j].shape.getGlobalBounds())) {
                bulletsToRemove.push_back(i);
                enemiesToRemove.push_back(j);
                score += 10;
            }
        }
    }

    std::sort(enemiesToRemove.rbegin(), enemiesToRemove.rend());
    for (int idx : enemiesToRemove) {
        enemies.erase(enemies.begin() + idx);
    }

    std::sort(bulletsToRemove.rbegin(), bulletsToRemove.rend());
    for (int idx : bulletsToRemove) {
        bullets.erase(bullets.begin() + idx);
    }
}

void Game::render() {
    scoreText.setString("Score: " + std::to_string(score));

    if (gameOver)
        gameOverText.setString("GAME OVER");
    else if (youWin)
        gameOverText.setString("YOU WIN!");

    window.clear(sf::Color::Black);
    window.draw(player.shape);

    for (auto& bullet : bullets) {
        window.draw(bullet.shape);
    }
    for (auto& enemy : enemies) {
        window.draw(enemy.shape);
    }

    window.draw(scoreText);
    if (gameOver || youWin) {
        window.draw(gameOverText);
    }

    window.display();
}