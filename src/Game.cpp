#include "Game.h"

// CONSTRUCTOR AND DESTRUCTOR

// 1. The default constructor must initialize the window with a string (window title) and an sf::Vector2u(800,600) for its size
//    Also the movement vector for the mushroom should be initalized to x=4.0f, y=4.0f.
//    Both the vector and the window must be set with a "member initializers list" (https://en.cppreference.com/w/cpp/language/constructor)
//    The body of the constructor must:
//      * Load the texture file (mushroom50-50.png) into the sf::Texture member variable using the loadFromFile function of the sf::Texture class.
//      * Set the sf::Texture variable as the texture of the sf::Sprite member (using the sf::Sprite::setTexture(sf::Texture) function).

// Game::Game() : gameWindow("Mushroom Game", sf::Vector2u(800, 600)), mushroomVelocity(4.0f, 4.0f)
// {
// 	mushroomTexture.loadFromFile("../../src/mushroom50-50.png");
// 	mushroom.setTexture(mushroomTexture);
// }

// Game::Game() : gameWindow("Mushroom Game", sf::Vector2u(800, 600)) {
//     // 创建一个 Entity 实例，参数是蘑菇的纹理路径和速度
//     mushroomEntity = new Entity("../../src/mushroom50-50.png", 4.0f, 4.0f);
// }
Game::Game(int entityCount) : gameWindow("Mushroom Game", sf::Vector2u(800, 600)), isPaused(false)
{
    for (int i = 0; i < entityCount; ++i)
    {
        float speed = 400.0f; // 假设的速度值
        Entity *newEntity = new Entity("../../src/mushroom50-50.png", speed, &gameWindow);
        entities.push_back(newEntity);
    }
}

// 2.  Define an empty default destructor.
Game::~Game()
{
    for (Entity *entity : entities)
    {
        delete entity;
    }
    entities.clear();
    // delete mushroomEntity;
    // mushroomEntity = nullptr;
}

// MEMBER FUNCTIONS:

// 3. For handling the input. This logic will not handle any input yet, so define an empty handling function.
void Game::handleInput()
{
    sf::Event event;
    while (gameWindow.getRenderWindow().pollEvent(event))
    {
        if (event.type == sf::Event::Closed)
        {
            gameWindow.setDone(true); // 假设您有一个设置窗口状态为 "done" 的方法
        }
        else if (event.type == sf::Event::KeyPressed)
        {
            if (event.key.code == sf::Keyboard::Space)
            {
                isPaused = !isPaused; // 切换暂停状态
            }else if (event.key.code == sf::Keyboard::Up)
            {
                 addEntity();
            }else if (event.key.code == sf::Keyboard::Down) {
                removeEntity();
            }
            
        }
    }
}

// 4. For updating tha game state:
//	  a) Call the private function of this class that executes the logic (mushroom movement).
//    b) Call the update function of the window (the window does handle input in the update function. This is not really orthodox,
//       but it will work for now).
void Game::update(float deltaTime)
{
    if (!isPaused)
    {
        for (Entity *entity : entities)
        {
            entity->update(gameWindow.getWindowSize(), deltaTime);
        }
        gameWindow.update();
    }
}

// 5. Function for rendering the game:
//    a) Our window object offers functionality for clearing the screen. Call the method that starts the draw on the window member first.
//    b) Draw the mushroom on screen, by calling the draw function in window that receives a reference to a sf::Drawable& reference.
//    c) Our window also offers functionality for displaying all that has been drawn since the last clear. Call the method that ends the draw on the window now.
void Game::render()
{
    gameWindow.beginDraw();
    for (Entity *entity : entities)
    {
        entity->draw(gameWindow.getRenderWindow());
    }
    gameWindow.draw(gameWindow.getGUIText()); // 绘制 FPS 文本
    gameWindow.endDraw();

    // gameWindow.beginDraw();   // 开始绘制
    // mushroomEntity->draw(gameWindow.getRenderWindow()); // 现在正确地传递 sf::RenderWindow 对象
    // gameWindow.endDraw();     // 结束绘制
}

// 6. Define the function that returns a pointer to the window member variable of this class.
Window *Game::getWindow()
{
    return &gameWindow;
}

// 7. Define the function for updating the movement of the mushroom.
//    The following is pseudocode (as I don't know how you named your member variables):
//
//    # Some initializations:
//    windowSize <- window.getWindowSize
//    textureSize <- mushroomTexture.getSize
//    xRightLimit <- windowSize.width - textureSize.width
//    yBottomLimit <- windowSize.height - textureSize.height
//
//    # Check if we are bouncing off the right or left edges:
//    bouncesRight <- (mushroom.xPosition > xRightLimit AND mushroom.movement.x > 0)
//    bouncesLeft <- (mushroom.xPosition < 0 AND mushroom.movement.x < 0)
//    if bouncesRight OR bouncesLeft
//       { change sign of mushroom.movement.x }
//
//    # Same for top or bottom edges:
//    bouncesBottom <- (mushroom.yPosition > yBottomLimit AND mushroom.movement.y > 0)
//    bouncesTop <- (mushroom.yPosition < 0 AND mushroom.movement.y < 0)
//    if bouncesBottom OR bouncesTop
//       { change sign of mushroom.movement.y }
//
//	  mushroom.setPosition(mushroom.xPosition + mushroom.movement.x, mushroom.yPosition + mushroom.movement.y)

sf::Vector2f Game::getEntityPosition(int index) const
{
    if (index < 0 || index >= entities.size())
    {
        throw std::out_of_range("Index out of range");
    }
    return entities[index]->getPosition();
    // 确保 Entity 类有 getPosition 方法
}

sf::Time Game::getElapsedTime() const
{
    return clock.getElapsedTime();
}

void Game::setFPS(int fps)
{
    std::string fpsString = "FPS: " + std::to_string(fps);
    gameWindow.getGUIText().setString(fpsString);
}

void Game::addEntity()
{
    entities.push_back(createEntity());
}

void Game::removeEntity()
{
    if (!entities.empty())
    {
        delete entities.back();
        entities.pop_back();
    }
}

Entity *Game::createEntity()
{
    // 创建并返回一个新的 Entity 实例
    // 请根据您的 Entity 类的构造函数调整参数
    return new Entity("../../src/mushroom50-50.png", 400.0f, &gameWindow);
}
