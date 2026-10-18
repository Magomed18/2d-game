#include <<SFML/Graphics.hpp>>
#include <SFML/Graphics.hpp>
#include "Plot.h"
#include "InventoryBarUI.h"
#include "Item.h"

#include <algorithm>
#include <array>
#include <cmath>
#include <filesystem>
#include <iostream>

int main()
{

    const std::filesystem::path imageDirectory(GARDEN_IMAGE_DIR);
    // Keep both textures alive for as long as their sprites are used.
    sf::Texture inventoryTexture;
    sf::Texture backgroundTexture;
    sf::Texture characterTexture;
    sf::Image characterImage;

    std::array<Plot, 2> plots{
        Plot{{100.f, 325.f}, {158.f, 159.f}},
        Plot{{1077.f, 332.f}, {138.f, 148.f}}
    };

    if (!backgroundTexture.loadFromFile(imageDirectory / "background.png") ||
        !characterImage.loadFromFile(imageDirectory / "character.png") ||
        !inventoryTexture.loadFromFile(imageDirectory / "inventory-bar.png"))
    {
        std::cerr << "Could not load background.png or character.png from "
                  << imageDirectory << '\n';
        return 1;
    }

    // Temporary workaround for this character's white background.
    // Remove the mask when you export artwork with a transparent background.
    characterImage.createMaskFromColor(sf::Color::White);
    if (!characterTexture.loadFromImage(characterImage))
    {
        std::cerr << "Could not create the character texture\n";
        return 1;
    }

    constexpr unsigned int windowWidth = 1280;
    constexpr unsigned int windowHeight = 720;
    sf::RenderWindow window(sf::VideoMode({windowWidth, windowHeight}),
                            "Garden - WASD / Arrow Keys",
                            sf::Style::Titlebar | sf::Style::Close);
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    sf::Sprite background(backgroundTexture);
    const auto backgroundSize = backgroundTexture.getSize();
    background.setScale({static_cast<float>(windowWidth) / backgroundSize.x,
                         static_cast<float>(windowHeight) / backgroundSize.y});

    sf::Sprite character(characterTexture);
    // Scale the character image to 72 pixels tall, preserving its shape.
    constexpr float characterHeight = 72.f;
    const float characterScale = characterHeight / characterTexture.getSize().y;
    character.setScale({characterScale, characterScale});
    const auto characterSize = character.getGlobalBounds().size;
    const float maxX = std::max(0.f, windowWidth - characterSize.x);
    const float maxY = std::max(0.f, windowHeight - characterSize.y);
    character.setPosition({maxX / 2.f, maxY / 2.f});

    std::array<Item, 5> items{};

    items[0] = Item{
        "Carrot seed",
        5,
        imageDirectory / "items/crop_seeds/carrot_seed.png"
    };

    InventoryBarUI inventoryUI(
    inventoryTexture,
    {windowWidth / 2.f, static_cast<float>(windowHeight)},
    500.f
);


    constexpr float movementSpeed = 220.f; // Pixels per second.
    sf::Clock frameClock;

    while (window.isOpen())
    {
        // Limit large jumps if a frame takes unusually long.
        const float deltaTime = std::min(frameClock.restart().asSeconds(), 0.1f);
        while (const auto event = window.pollEvent())
        {
            if (const auto* key = event->getIf<sf::Event::KeyPressed>())
            {
                if (key->code == sf::Keyboard::Key::E)
                {
                    const auto bounds = character.getGlobalBounds();

                    const sf::Vector2f feet{
                        bounds.position.x + bounds.size.x / 2.f,
                        bounds.position.y + bounds.size.y
                    };

                    for (auto& plot : plots)
                    {
                        if (!plot.rectangle.getGlobalBounds().contains(feet))
                            continue;

                        if (plot.state == PlotState::Untouched)
                        {
                            plot.state = PlotState::Prepared;
                        }
                        else if (plot.state == PlotState::Prepared)
                        {
                            plot.state = PlotState::Planted;
                        }
                        // One key press interacts with only one plot.
                        break;
                    }
                }
                if (key->code == sf::Keyboard::Key::Q)
                {
                    inventoryUI.toggleVisibility();
                }
                if (key->code == sf::Keyboard::Key::Escape)
                {
                    window.close();
                }
            }
            if (event->is<sf::Event::Closed>())
                window.close();

            // if (sf::Keyboard::isKeyPressed(sf::Keyboard::Key::Escape))
			// 	window.close();

        }


        // if (!window.isOpen())
        //     break;

        sf::Vector2f direction{0.f, 0.f};
        if (window.hasFocus())
        {
            using Key = sf::Keyboard::Key;
            if (sf::Keyboard::isKeyPressed(Key::A) || sf::Keyboard::isKeyPressed(Key::Left))
                direction.x -= 1.f;
            if (sf::Keyboard::isKeyPressed(Key::D) || sf::Keyboard::isKeyPressed(Key::Right))
                direction.x += 1.f;
            if (sf::Keyboard::isKeyPressed(Key::W) || sf::Keyboard::isKeyPressed(Key::Up))
                direction.y -= 1.f;
            if (sf::Keyboard::isKeyPressed(Key::S) || sf::Keyboard::isKeyPressed(Key::Down))
                direction.y += 1.f;
        }

        // Keep diagonal movement at the same speed as horizontal movement.
        const float length = std::sqrt(direction.x * direction.x + direction.y * direction.y);
        if (length > 0.f)
            character.move(direction / length * movementSpeed * deltaTime);

        auto position = character.getPosition();
        position.x = std::clamp(position.x, 0.f, maxX);
        position.y = std::clamp(position.y, 0.f, maxY);
        character.setPosition(position);

        
    }
}
Game::Game()
: mWindow(sf::VideoMode(640, 480), "SFML Application")
, mPlayer()
{
mPlayer.setRadius(40.f);
mPlayer.setPosition(100.f, 100.f);
mPlayer.setFillColor(sf::Color::Cyan);
}
void Game::run()
{
    while (mWindow.isOpen())
    {
        void Game::processEvents();
        void Game::update();
        void Game::render();
        {
            window.clear();
                window.draw(background); // Draw the ground first.
                for (auto& plot : plots)
                {
                    if (plot.state == PlotState::Untouched)
                        plot.rectangle.setFillColor(sf::Color(100, 150, 60));
                    else
                        plot.rectangle.setFillColor(sf::Color(110, 75, 45));
        
                    window.draw(plot.rectangle);
                    if (plot.state == PlotState::Planted)
                        window.draw(plot.vegetable);
                }
                window.draw(character);  // Draw the character on top.
                inventoryUI.draw(window, items);
                window.display();
        }
    
    }
}