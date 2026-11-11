#pragma once

#include <filesystem>
#include <optional>
#include <SFML/Graphics.hpp>
#include <Crop.h>

enum class PlotState
{
    Untouched,
    Prepared,
    Planted,
    Ready,
    Harvested
};


class Plot
{

    public:

        Plot(){};
        void time_progress(deltaTime);
        void draw(sf::RenderWindow& window, auto vegetable);
        void set_state(PlotState state);
        void check_state();


    private:
        sf::Vector2f position;
        sf::RectangleShape rectangle;
        PlotState state = PlotState::Untouched;
        std::optional<Crop> vegetable;
        double age;
   

    

//     Plot(sf::Vector2f position, sf::Vector2f size, double initialGrowthProgress) 
//     : rectangle(size),
      
//     {
//         rectangle.setPosition(position);
//         // rectangle.setFillColor(sf::Color(100, 150, 60));
//         // rectangle.setOutlineColor(sf::Color::Yellow);
//         rectangle.setOutlineThickness(2.f);

    


//         // vegetable.setScale({1.5f, 1.5f});
//         // vegetable.setOrigin({32.f, 32.f});
//         // vegetable.setPosition(position + size / 2.f);
//     }
};
// Hello!