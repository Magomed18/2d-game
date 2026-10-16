#pragma once

#include <SFML/Graphics.hpp>

enum class PlotState
{
    Untouched,
    Prepared,
    Planted
};

enum class VegetableType
{
    None,
    Carrot,
    Potato,
    Tomato
};

struct Plot
{
    // Each Plot instance has its own rectangle, state, and vegetable.
    sf::RectangleShape rectangle;
    PlotState state = PlotState::Untouched;
    VegetableType vegetableType = VegetableType::None;
    sf::CircleShape vegetable{32.f};

    Plot(sf::Vector2f position, sf::Vector2f size) : rectangle(size)
    {
        rectangle.setPosition(position);
        rectangle.setFillColor(sf::Color(100, 150, 60));
        rectangle.setOutlineColor(sf::Color::Yellow);
        rectangle.setOutlineThickness(2.f);

        vegetable.setFillColor(sf::Color::Green);
        vegetable.setOrigin({32.f, 32.f});
        vegetable.setPosition(position + size / 2.f);
    }
};
