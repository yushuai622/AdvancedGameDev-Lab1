#include "Entity.h"
#include <cstdlib>
#include <cmath>

Entity::Entity(const std::string& textureFile, float speed, Window* window) {
    texture.loadFromFile(textureFile);
    sprite.setTexture(texture);

    // 随机化位置
    if (window) {
        auto windowSize = window->getWindowSize();
        sprite.setPosition(std::rand() % (windowSize.x - texture.getSize().x),
                           std::rand() % (windowSize.y - texture.getSize().y));
    }

    // 随机化方向
    float angle = static_cast<float>(std::rand()) / RAND_MAX * 2 * M_PI;
    velocity = sf::Vector2f(std::cos(angle), std::sin(angle)) * speed;
}


Entity::~Entity() {
    // 清理代码（如果需要的话）
}

void Entity::update(const sf::Vector2u& windowSize, float deltaTime) {
    // 添加模拟的计算延迟
    // float delay = (((float)rand() / RAND_MAX) > 0.8) ? 0.075f : 0.01f;
    // sf::sleep(sf::seconds(delay));

    sf::Vector2u textureSize = texture.getSize();

    bool bouncesRight = (sprite.getPosition().x > windowSize.x - textureSize.x && velocity.x > 0);
    bool bouncesLeft = (sprite.getPosition().x < 0 && velocity.x < 0);
    if (bouncesRight || bouncesLeft) {
        velocity.x *= -1;
    }

    bool bouncesBottom = (sprite.getPosition().y > windowSize.y - textureSize.y && velocity.y > 0);
    bool bouncesTop = (sprite.getPosition().y < 0 && velocity.y < 0);
    if (bouncesBottom || bouncesTop) {
        velocity.y *= -1;
    }

    // 更新位置时考虑 deltaTime
    sprite.setPosition(sprite.getPosition() + velocity * deltaTime);
}

void Entity::draw(sf::RenderWindow& window) const {
    window.draw(sprite);
}

const sf::Vector2f& Entity::getPosition() const {
    return sprite.getPosition();
}