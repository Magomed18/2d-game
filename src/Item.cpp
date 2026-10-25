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

const sf::Texture* Item::getTexture() const
{
    return texture.get();
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

// void Item::draw(sf::RenderWindow& window,
//                 sf::Vector2f slotCenter,
//                 sf::Vector2f availableSize, const sf::Font& textFont) const
// {
//     if (!texture || quantity == 0 ||
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
// }