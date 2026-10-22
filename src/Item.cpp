#include "Item.h"

#include <algorithm>
#include <limits>
#include <utility>

Item::Item(std::string itemName, int initialQuantity,
           const std::filesystem::path& iconPath)
    : name(std::move(itemName)),
      quantity(std::max(0, initialQuantity)),
      texture(std::make_shared<sf::Texture>(iconPath))
{
}

int Item::getQuantity() const
{
    return quantity;
}

const std::string& Item::getName() const
{
    return name;
}

// void Item::addQuantity(int amount)
// {
//     if (amount <= 0)
//         return;

//     if (amount > std::numeric_limits<int>::max() - quantity)
//         return;

//     quantity += amount;
// }

// bool Item::removeQuantity(int amount)
// {
//     if (amount <= 0 || amount > quantity)
//         return false;

//     quantity -= amount;
//     return true;
// }

void Item::draw(sf::RenderWindow& window,
                sf::Vector2f slotCenter,
                sf::Vector2f availableSize, sf::Font& textFont) const
{
    if (!texture || quantity == 0 ||
        availableSize.x <= 0.f || availableSize.y <= 0.f)
        return;

    
    sf::Sprite icon(*texture);
    
    const auto imageSize = texture->getSize();

    // Fit inside the slot while preserving the image's proportions.
    const float scale = std::min(
        availableSize.x / imageSize.x,
        availableSize.y / imageSize.y
    );

    icon.setScale({scale, scale});

    // Position the middle of the icon at the middle of the slot.
    icon.setOrigin({imageSize.x / 2.f, imageSize.y / 2.f});
    icon.setPosition(slotCenter);

    
   sf::Text quantityText;
    quantityText.setFont(textFont);
    quantityText.setString(std::to_string(quantity));
    quantityText.setCharacterSize(24);
    quantityText.setFillColor(sf::Color::White);
    quantityText.setPosition(slotCenter.x - quantityText.getLocalBounds().size.x / 2.f,
                            slotCenter.y - quantityText.getLocalBounds().size.y / 2.f);

    window.draw(icon);
    window.draw(quantityText);
}