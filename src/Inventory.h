#pragma once

#include <SFML/Graphics.hpp>
#include <Item.h>

class Inventory{
    public:
        Inventory();
        void update();
        void addItem(const Item& item);
        void removeItem(const Item& item);
        void draw(sf::RenderWindow& window);

    private:
        std::array<Item, 5>;
        sf::Sprite inventoryBar;
        sf::Texture inventoryBarTexture;
}