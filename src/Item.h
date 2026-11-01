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
    const sf::Texture* getTexture() const;

    int addQuantity(int amount);
    int removeQuantity(int amount);


private:
    
    std::string name;
    int quantity = 0;
    std::shared_ptr<sf::Texture> texture;
};