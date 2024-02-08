#pragma once
#include <SFML/Graphics.hpp>
#include "Window.h"

class Entity {
public:
    Entity(const std::string& textureFile, float speed, Window* window);
    // Entity(const std::string& textureFile, float xVelocity, float yVelocity);
    ~Entity();

    // void move(const sf::Vector2u& windowSize);
    void update(const sf::Vector2u& windowSize, float deltaTime);  // 添加新的参数 deltaTime 来表示自上一帧以来经过的时间
    void draw(sf::RenderWindow& window) const;
    const sf::Vector2f& getPosition() const;

private:
    sf::Texture texture;
    sf::Sprite sprite;
    sf::Vector2f velocity;
};
