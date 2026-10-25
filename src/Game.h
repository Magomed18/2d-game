#pragma once

#include "InventoryBarUI.h"
#include "Item.h"
#include "Plot.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <filesystem>

class Game
{
public:
    Game();
    void run();

private:
    void processEvents();
    void update(float deltaTime);
    void render();
    void interactWithPlot();

    static constexpr unsigned int windowWidth = 1280;
    static constexpr unsigned int windowHeight = 720;
    static constexpr float movementSpeed = 220.f;

    const std::filesystem::path imageDirectory{GARDEN_IMAGE_DIR};

    sf::RenderWindow window;
    sf::Clock frameClock;


    sf::Texture backgroundTexture;
    sf::Texture characterTexture;
    sf::Texture inventoryTexture;

    sf::Sprite background;
    sf::Sprite character;

    sf::Font textFont;

    std::array<Plot, 2> plots{
        Plot{{100.f, 325.f}, {158.f, 159.f}},
        Plot{{1077.f, 332.f}, {138.f, 148.f}}
    };

    std::array<Item, 5> items{};
    InventoryBarUI inventoryUI;

    float maxX = 0.f;
    float maxY = 0.f;
};