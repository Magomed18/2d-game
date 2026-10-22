#include "InventoryBarUI.h"

#include <stdexcept>

InventoryBarUI::InventoryBarUI(const sf::Texture& texture,
                               sf::Vector2f bottomCenter,
                               float displayedWidth)
    : bar(texture)
{
    if (displayedWidth <= 0.f)
        throw std::invalid_argument("Bar width must be positive");

    // These coordinates match your current PNG.
    bar.setTextureRect(
        sf::IntRect({186, 207}, {457, 95})
    );

    const auto size = bar.getLocalBounds().size;
    const float scale = displayedWidth / size.x;

    bar.setScale({scale, scale});
    bar.setOrigin({size.x / 2.f, size.y});
    bar.setPosition(bottomCenter);

    textFont.openFromFile("assets/fonts/arial.ttf");
}

void InventoryBarUI::toggleVisibility()
{
    visible = !visible;
}

void InventoryBarUI::setPosition(sf::Vector2f bottomCenter)
{
    bar.setPosition(bottomCenter);
}

sf::Vector2f InventoryBarUI::getSlotCenter(std::size_t index) const
{
    return bar.getTransform().transformPoint(slotCenters.at(index));
}

void InventoryBarUI::draw(sf::RenderWindow& window,
                          const std::array<Item, 5>& items) const
{
    if (!visible)
        return;

    window.draw(bar);

    const auto scale = bar.getScale();

    const sf::Vector2f availableIconSize{
        64.f * scale.x,
        64.f * scale.y
    };

    for (std::size_t i = 0; i < items.size(); ++i)
    {
        items[i].draw(window, getSlotCenter(i), availableIconSize, textFont);
    }
}