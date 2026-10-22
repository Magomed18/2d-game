#pragma once

#include "Item.h"

#include <SFML/Graphics.hpp>
#include <array>
#include <cstddef>

class InventoryBarUI
{
public:
    InventoryBarUI(const sf::Texture& texture,
                   sf::Vector2f bottomCenter,
                   float displayedWidth = 500.f);

    void toggleVisibility();
    void setPosition(sf::Vector2f bottomCenter);

    sf::Vector2f getSlotCenter(std::size_t index) const;

    void draw(sf::RenderWindow& window,
              const std::array<Item, 5>& items) const;

private:
    sf::Font textFont;
    sf::Sprite bar;
    bool visible = false;

    // Coordinates relative to your cropped bar image.
    const std::array<sf::Vector2f, 5> slotCenters{
        sf::Vector2f{52.5f, 46.5f},
        sf::Vector2f{139.5f, 46.5f},
        sf::Vector2f{227.5f, 46.5f},
        sf::Vector2f{316.5f, 46.5f},
        sf::Vector2f{405.5f, 46.5f}
    };
};