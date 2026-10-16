#pragma once

#include <SFML/Graphics.hpp>
#include <string>

class Item
{
public:
    Item();
    int getQuantity() const;
    std::string getName() const;
    void update();
    void draw(sf::RenderWindow& window);

private:
    std::string name;
    int quantity;

    sf::Sprite sprite;
    sf::Texture texture;
};