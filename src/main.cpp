#include <SFML/Graphics.hpp>
#include "Game.h"
#include <cstdlib>
#include <ctime>
#include <iostream>
// Check here APIs for the SFML classes to be used in this LAB (all in here: https://www.sfml-dev.org/documentation/2.5.1/annotated.php):
//   sf::RenderWindow -  https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1RenderWindow.php
//   sf::Vector2u - https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Vector2.php
//   sf::Style - https://www.sfml-dev.org/documentation/1.6/namespacesf_1_1Style.php
//   sf::Drawable - https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Drawable.php
//   sf::Texture - https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Texture.php
//   sf::Sprite - https://www.sfml-dev.org/documentation/2.5.1/classsf_1_1Sprite.php

// int simpleLoop(Game& game) {
//     sf::Time startTime = game.getElapsedTime();
    
//     game.handleInput();
//     if (!game.getWindow()->isWindowDone()) {
//         game.update();
//         game.render();
//     }

//     sf::Time endTime = game.getElapsedTime();
//     sf::Time elapsed = endTime - startTime;
//     int fps = static_cast<int>(1.0f / elapsed.asSeconds());
//     game.setFPS(fps);
//     std::cout << "Elapsed time: " << elapsed.asSeconds() << "s, FPS: " << fps << std::endl;

//     return fps;
// }

// int targetTimedLoop(Game& game, float targetTime) {
//     sf::Time startTime = game.getElapsedTime();

//     game.handleInput();
//     if (!game.getWindow()->isWindowDone()) {
//         game.update();
//         game.render();
//     }

//     sf::Time endTime = game.getElapsedTime();
//     sf::Time elapsed = endTime - startTime;
//     float sleepTime = targetTime - elapsed.asSeconds();

//     if (sleepTime > 0) {
//         sf::sleep(sf::seconds(sleepTime));
//     }

//     sf::Time totalElapsedTime = game.getElapsedTime() - startTime;
//     int fps = static_cast<int>(1.0f / totalElapsedTime.asSeconds());

//     std::cout << "Elapsed time: " << totalElapsedTime.asSeconds() << "s, FPS: " << fps << std::endl;
//     game.setFPS(fps);

//     return fps;
// }

int adaptiveLoop(Game& game, float& lastFrameTime, float targetFPS) {
    float currentFrameTime = game.getElapsedTime().asSeconds();
    float deltaTime = currentFrameTime - lastFrameTime;
    lastFrameTime = currentFrameTime;

    game.handleInput();
    if (!game.getWindow()->isWindowDone()) {
        game.update(deltaTime);
        game.render();
    }

    // 如果有目标 FPS，则睡眠以维持目标 FPS
    float frameLimit = 1.0f / targetFPS;
    float frameTime = game.getElapsedTime().asSeconds() - currentFrameTime;
    if (frameTime < frameLimit) {
        sf::sleep(sf::seconds(frameLimit - frameTime));
    }

    int fps = static_cast<int>(1.0f / (game.getElapsedTime().asSeconds() - currentFrameTime));
    game.setFPS(fps);
    return fps;
}

int main()
{

    std::srand(static_cast<unsigned int>(std::time(nullptr))); // 初始化随机种子
    
    // Declare an object of type "Game"

    // Simple game loop. Iterate _while_ the window of the game is not "done". Note getWindow() returns a pointer!
    // Three steps per iteration:
    //   1. Ask the game instance to handle the input.
    //   2. Ask the game instance to update its state.
    //   3. Ask the game instance to render.

    // Declare an object of type "Game"
    int entityCount = 5; // 假设我们想要创建 5 个实体
    Game game(entityCount);

    int totalFPS = 0;
    int frameCount = 0;
    float targetTime = 1.0f / 60.0f; // 例如，目标 FPS 为 60
    float lastFrameTime = game.getElapsedTime().asSeconds();
    float targetFPS = 60.0f; // 目标 FPS
    

    // Simple game loop. Iterate _while_ the window of the game is not "done".
    while (!game.getWindow()->isWindowDone())
    {

        float currentFrameTime = game.getElapsedTime().asSeconds();
        float deltaTime = currentFrameTime - lastFrameTime;
        lastFrameTime = currentFrameTime;

        // 1. Ask the game instance to handle the input.
        game.handleInput();
        // 2. Ask the game instance to update its state.
        game.update(deltaTime);
        // 3. Ask the game instance to render.
        game.render();

        // int fps = simpleLoop(game);
        // int fps = targetTimedLoop(game, targetTime);
        int fps = adaptiveLoop(game, lastFrameTime, targetFPS);
        totalFPS += fps;
        frameCount++;
    }

    int averageFPS = frameCount > 0 ? totalFPS / frameCount : 0;
    std::cout << "Average FPS: " << averageFPS << std::endl;

    return 0;
}