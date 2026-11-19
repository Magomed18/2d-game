#include "Game.h"

#include <algorithm>
#include <cmath>
#include <stdexcept>
#include <iostream>
#include <string>

Game::Game()
    : window(
          sf::VideoMode({windowWidth, windowHeight}),
          "Garden - WASD / Arrow Keys",
          sf::Style::Titlebar | sf::Style::Close
      ),
      backgroundTexture(imageDirectory / "background.png"),
      inventoryTexture(imageDirectory / "inventory-bar.png"),
      background(backgroundTexture),
      character(characterTexture),
      sprout(imageDirectory / "crops/carrot/sprout.png"),
      grown(imageDirectory / "crops/carrot/grown.png"),
      textFont(imageDirectory / "fonts/Roboto-Italic-VariableFont_wdth,wght.ttf"),
      goalText(textFont, "Goal: Harvest 5 carrots - 0", 24),
      completionText(textFont, "Congratulations! You have completed the goal.", 50),
      inventoryUI(
          inventoryTexture,
          {windowWidth / 2.f, static_cast<float>(windowHeight)},
          500.f
      )
{
    window.setFramerateLimit(60);
    window.setKeyRepeatEnabled(false);

    // Prepare the goal text.
    goalText.setFillColor(sf::Color::White);
    goalText.setOutlineColor(sf::Color::Black);
    goalText.setOutlineThickness(1.f);

    // Prepare the completion text.
    completionText.setFillColor(sf::Color::White);
    completionText.setOutlineColor(sf::Color::Black);
    completionText.setOutlineThickness(1.f);

    // Prepare the character image.
    sf::Image characterImage(imageDirectory / "character.png");
    characterImage.createMaskFromColor(sf::Color::White);

    if (!characterTexture.loadFromImage(characterImage))
        throw std::runtime_error("Could not create character texture");

    // The sprite was constructed before this texture was loaded.
    // Reset its texture rectangle to the loaded image dimensions.
    character.setTexture(characterTexture, true);

    // Fit the background to the window.
    const auto backgroundSize = backgroundTexture.getSize();

    background.setScale({
        static_cast<float>(windowWidth) / backgroundSize.x,
        static_cast<float>(windowHeight) / backgroundSize.y
    });

    // Size and position the character.
    constexpr float characterHeight = 72.f;

    const float characterScale =
        characterHeight / characterTexture.getSize().y;

    character.setScale({characterScale, characterScale});

    const auto characterSize = character.getGlobalBounds().size;

    maxX = std::max(0.f, windowWidth - characterSize.x);
    maxY = std::max(0.f, windowHeight - characterSize.y);

    character.setPosition({maxX / 2.f, maxY / 2.f});

    // Starting inventory.
    items[0] = Item{
        "Carrot seed",
        5,
        imageDirectory / "items/crop_seeds/carrot_seed.png"
    };

    items[1] = Item{"Carrot", 0, imageDirectory / "crops/carrot/grown.png"};
}
    void Game::run()
{
    while (window.isOpen())
    {
        const float deltaTime =
            std::min(frameClock.restart().asSeconds(), 0.1f);

        processEvents();

        if (!window.isOpen())
            break;

        update(deltaTime);
        render();
    }
}

void Game::processEvents()
{
    while (const auto event = window.pollEvent())
    {
        if (event->is<sf::Event::Closed>())
            window.close();

        if (const auto* key = event->getIf<sf::Event::KeyPressed>())
        {
            if (key->code == sf::Keyboard::Key::E)
                interactWithPlot();

            if (key->code == sf::Keyboard::Key::Q)
                inventoryUI.toggleVisibility();

            if (key->code == sf::Keyboard::Key::Escape)
                window.close();
        }
    }
}

void Game::interactWithPlot()
{
    const auto bounds = character.getGlobalBounds();

    const sf::Vector2f feet{
        bounds.position.x + bounds.size.x / 2.f,
        bounds.position.y + bounds.size.y
    };

    for (auto& plot : plots)
    {
        // if (!plot.rectangle.getGlobalBounds().contains(feet))
        //     continue;


        if (!plot.contains(feet))
        {
            continue;
        }

        else if (plot.prepare())
        {
            // Prepared; planting waits for the next interaction.
        }
    

        else if (items[0].getQuantity() > 0 && plot.plant(imageDirectory / "crops/carrot/seeds.png", imageDirectory / "crops/carrot/sprout.png", imageDirectory / "crops/carrot/grown.png", 10.f, CropType::Carrot))
        {
            items[0].removeQuantity(1);

        
            
        }

        else if (plot.harvest())
            {
    

            items[1].addQuantity(1);
            ++harvestedCarrots;
            
            }

        
        

        // else if (plot.state == PlotState::Ready){
        //     std::cout << "The plot is set to Ready" << std::endl;
        //     plot.harvest();
        //     std::cout << "The plot is set to Harvested" << std::endl;
        //     // items[1].addQuantity(1);
        //     std::cout << "The plot is set back to Untouched" << std::endl;
        //     // plot.growthProgress = 0.0;
        //     // plot.vegetable.setTexture(plot.texture);
        // }    
    

        break;
        }

        
}


void Game::update(float deltaTime)
{
    if (!window.hasFocus())
        return;

    sf::Vector2f direction{0.f, 0.f};
    using Key = sf::Keyboard::Key;

    if (sf::Keyboard::isKeyPressed(Key::A) ||
        sf::Keyboard::isKeyPressed(Key::Left))
        direction.x -= 1.f;

    if (sf::Keyboard::isKeyPressed(Key::D) ||
        sf::Keyboard::isKeyPressed(Key::Right))
        direction.x += 1.f;

    if (sf::Keyboard::isKeyPressed(Key::W) ||
        sf::Keyboard::isKeyPressed(Key::Up))
        direction.y -= 1.f;

    if (sf::Keyboard::isKeyPressed(Key::S) ||
        sf::Keyboard::isKeyPressed(Key::Down))
        direction.y += 1.f;

    const float length = std::sqrt(
        direction.x * direction.x + direction.y * direction.y
    );

    if (length > 0.f)
        character.move(direction / length * movementSpeed * deltaTime);

    auto position = character.getPosition();

    position.x = std::clamp(position.x, 0.f, maxX);
    position.y = std::clamp(position.y, 0.f, maxY);

    character.setPosition(position);

    //Plot time logic
    for (auto& plot : plots)
    {
        plot.update(deltaTime);
    }
}

void Game::render()
{
    window.clear();
    window.draw(background);

    // Plot rendering loop
    for (auto& plot : plots)
    {
        

        plot.draw(window);

            
    }

    window.draw(character);
    inventoryUI.draw(window, items, textFont);

    goalText.setString(
        "Goal: Harvest 5 carrots - " + std::to_string(harvestedCarrots)
    );

    const auto goalBounds = goalText.getLocalBounds();
    goalText.setOrigin({
        goalBounds.position.x + goalBounds.size.x,
        goalBounds.position.y
    });
    goalText.setPosition({
        static_cast<float>(window.getSize().x) - 20.f,
        20.f
    });

    if (harvestedCarrots >= 5)
    {
        const auto completionBounds = completionText.getLocalBounds();
        completionText.setOrigin({
            completionBounds.position.x + completionBounds.size.x / 2.f,
            completionBounds.position.y + completionBounds.size.y / 2.f
        });
        completionText.setPosition({
            static_cast<float>(window.getSize().x) / 2.f,
            static_cast<float>(window.getSize().y) / 2.f
        });

        window.draw(completionText);
    }
    window.draw(goalText);

    window.display();
}

