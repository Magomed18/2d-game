#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <string>

class Item
{
public:
    Item() = default;

    Item(std::string name, int quantity,
         const std::filesystem::path& iconPath);

    int getQuantity() const;
    const std::string& getName() const;

    // void addQuantity(int amount);
    // bool removeQuantity(int amount);

    void draw(sf::RenderWindow& window,
              sf::Vector2f slotCenter,
              sf::Vector2f availableSize,
              sf::Font& textFont) const;

private:
    
    std::string name;
    int quantity = 0;
    std::shared_ptr<sf::Texture> texture;
};