#include "../header/Player.hpp"

Player::Player() {
    shape.setSize({50.f, 30.f});
    shape.setFillColor(sf::Color::White);
    shape.setPosition({375.f, 540.f});
}

void Player::handleInput(float dt) {
    shootCooldown -= dt;

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Left)) {
        shape.move({-speed * dt, 0.f});
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Right)) {
        shape.move({speed * dt, 0.f});
    }

    // 화면 밖으로 못 나가게
    if (shape.getPosition().x < 0)
        shape.setPosition({0.f, shape.getPosition().y});
    if (shape.getPosition().x > 750.f)
        shape.setPosition({750.f, shape.getPosition().y});
}

void Player::tryShoot(std::vector<Bullet>& bullets) {
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Space) && shootCooldown <= 0.f) {
        bullets.emplace_back(
            shape.getPosition().x + 22.f,
            shape.getPosition().y
        );
        shootCooldown = 0.3f;
    }
}