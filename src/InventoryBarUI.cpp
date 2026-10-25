#include "InventoryBarUI.h"

#include <stdexcept>

InventoryBarUI::InventoryBarUI(const sf::Texture& texture,
                               sf::Vector2f bottomCenter, 
                               float displayedWidth =500.f)
    : bar(texture)
    
{
    if (displayedWidth <= 0.f)
        throw std::invalid_argument("Bar width must be positive");

    // These coordinates for a bar PNG
    bar.setTextureRect(
        sf::IntRect({186, 207}, {457, 95})
    );

    const auto size = bar.getLocalBounds().size;
    const float scale = displayedWidth / size.x;

    bar.setScale({scale, scale});
    bar.setOrigin({size.x / 2.f, size.y});
    bar.setPosition(bottomCenter);


   
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

// void InventoryBarUI::draw(sf::RenderWindow& window,
//                           const std::array<Item, 5>& items, const sf::Font& textFont, sf::Vector2f slotCenter, sf::Vector2f availableSize) const

// {
//     if (!visible)
//         return;

//     window.draw(bar);

//     const auto scale = bar.getScale();

//     const sf::Vector2f availableIconSize{
//         64.f * scale.x,
//         64.f * scale.y
//     };

//     if (!texture || Item::getQuantity == 0 ||
//         availableSize.x <= 0.f || availableSize.y <= 0.f)
//         return;

    
//     sf::Sprite icon(*texture);
    
//     const auto imageSize = texture->getSize();

//     // Fit inside the slot while preserving the image's proportions.
//     const float scale = std::min(
//         availableSize.x / imageSize.x,
//         availableSize.y / imageSize.y
//     );

//     icon.setScale({scale, scale});

//     // Position the middle of the icon at the middle of the slot.
//     icon.setOrigin({imageSize.x / 2.f, imageSize.y / 2.f});
//     icon.setPosition(slotCenter);


//     sf::Text quantityText(textFont, std::to_string(quantity), 24);
//     quantityText.setFillColor(sf::Color::White);
    
//     const auto bounds = quantityText.getLocalBounds();
//     quantityText.setOrigin(bounds.position + bounds.size / 2.f);
//     quantityText.setPosition(slotCenter);

//     window.draw(icon);
//     window.draw(quantityText);

//     for (std::size_t i = 0; i < items.size(); ++i)
//     {
//         items[i].draw(window, getSlotCenter(i), availableIconSize,  textFont);
//     }
// }

void InventoryBarUI::draw(sf::RenderWindow& window,
                          const std::array<Item, 5>& items,
                          const sf::Font& textFont) const
{
    if (!visible)
        return;

    window.draw(bar);

    const auto barScale = bar.getScale();
    const sf::Vector2f availableIconSize{
        64.f * barScale.x,
        64.f * barScale.y
    };

    if (availableIconSize.x <= 0.f || availableIconSize.y <= 0.f)
        return;

    for (std::size_t i = 0; i < items.size(); ++i)
    {
        const auto& item = items[i];
        const auto* texture = item.getTexture();

        if (!texture || item.getQuantity() == 0)
            continue;

        const auto imageSize = texture->getSize();

        if (imageSize.x == 0 || imageSize.y == 0)
            continue;

        const auto slotCenter = getSlotCenter(i);

        sf::Sprite icon(*texture);

        const float iconScale = std::min(
            availableIconSize.x / imageSize.x,
            availableIconSize.y / imageSize.y
        );

        icon.setScale({iconScale, iconScale});
        icon.setOrigin({imageSize.x / 2.f, imageSize.y / 2.f});
        icon.setPosition(slotCenter);

        sf::Text quantityText(
            textFont, std::to_string(item.getQuantity()), 24
        );
        quantityText.setFillColor(sf::Color::Green);

        const auto bounds = quantityText.getLocalBounds();
        quantityText.setOrigin(bounds.position + bounds.size / 2.f);
        quantityText.setPosition(slotCenter);

        constexpr float padding = 4.f;

        quantityText.setPosition({
            slotCenter.x + availableIconSize.x / 2.f - padding,
            slotCenter.y + availableIconSize.y / 2.f - padding
        });

        window.draw(icon);
        window.draw(quantityText);
    }
}