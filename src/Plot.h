#pragma once
#include <filesystem>
#include <SFML/Graphics.hpp>

enum class PlotState
{
    Untouched,
    Prepared,
    Planted,
    Ready
};


struct Plot
{
    // Each Plot instance has its own rectangle, state, and vegetable.
    sf::RectangleShape rectangle;
    PlotState state = PlotState::Untouched;
    sf::Texture texture;
    sf::Sprite vegetable;

    Plot(sf::Vector2f position, sf::Vector2f size, const std::filesystem::path& iconPath ) : rectangle(size), texture(iconPath), vegetable(texture)
    {
        rectangle.setPosition(position);
        // rectangle.setFillColor(sf::Color(100, 150, 60));
        // rectangle.setOutlineColor(sf::Color::Yellow);
        rectangle.setOutlineThickness(2.f);

        
        vegetable.setOrigin({32.f, 32.f});
        vegetable.setPosition(position + size / 2.f);
    }
};
