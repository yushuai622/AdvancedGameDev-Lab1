#pragma once
#include "Window.h"
#include "Vector2.h"
#include "Entity.h"
#include <SFML/System/Clock.hpp>

class Game
{
public:
	sf::Time getElapsedTime() const;

	// Declare a default constructor and a default destructor.
	Game(int entityCount);
	~Game();

	// Declare a function for handling the input of the user. Returns void and receives no parameters.
	void handleInput();

	// Declare a function for updating the game state. Returns void and receives no parameters.
	void update(float deltaTime); // 新的 update 方法

	// Declare a function for rendering the game to the screen. Returns void and receives no parameters.
	void render();

	// Declare a function for returning a pointer to the "window" member of this class. Receives no parameters.
	Window* getWindow();

	void setFPS(int fps);

	void addEntity();
    void removeEntity();

private:
	// Declare a function for the logic of this demo: moving and bouncing the mushroom against the window limits.
	// This fucntions returns void and receives no parameters.
	// void moveMushroom();

	// Declare a member variable of type Window for the window of the application. Note this is NOT a pointer to a Window object.
	Window gameWindow;

	// Declare a member variable of type Vector2f, that will indicate the movement of the mushroom per frame. Again, not a pointer.
	// sf::Vector2f mushroomVelocity;

	// Declare two member variables of types sf::Texture and sf::Sprite. The first one will hold the texture of the mushroom, while the
	// second will be the sprite to draw in the window. These are variables, not pointers.
	// sf::Texture mushroomTexture;
	// sf::Sprite mushroom;

	std::vector<Entity*> entities;  // 存储 Entity 对象指针的向量
	// Entity* mushroomEntity;

	sf::Vector2f getEntityPosition(int index) const;
	bool isPaused;  // 新增表示游戏是否暂停的成员变量

	sf::Clock clock;  // 新增计时器

    Entity* createEntity();//创建新实体
};

