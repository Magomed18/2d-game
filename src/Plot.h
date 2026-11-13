#pragma once

#include <filesystem>
#include <optional>
#include <SFML/Graphics.hpp>
#include "Crop.h"

enum class PlotState
{
    Untouched,
    Prepared,
    Planted
};


class Plot
{

    private:
   
        sf::RectangleShape rectangle;
        PlotState state = PlotState::Untouched;
        std::optional<Crop> crop;


    public:

        Plot(sf::Vector2f position, sf::Vector2f size)
            : rectangle(size)
        {
            rectangle.setPosition(position);
            
            rectangle.setFillColor(sf::Color(100, 150, 60));
            rectangle.setOutlineColor(sf::Color::Yellow);
            rectangle.setOutlineThickness(2.f);
        }


        bool contains(sf::Vector2f feet) const
        {
            return rectangle.getGlobalBounds().contains(feet);
        }

        bool prepared()
        {
            if (state != PlotState::Untouched)
                return false;

            state = PlotState::Prepared;
            return true;
        }


        bool plant(const std::filesystem::path& imagePath)
        {
            if (state != PlotState::Prepared || crop.has_value())
                return false;

            crop.emplace(imagePath, 10.f, CropType::Carrot);

            const auto center =
                rectangle.getPosition() + rectangle.getSize() / 2.f;

            crop->crop_image.setPosition(center);

            state = PlotState::Planted;
            return true;
        }

        void update(float deltaTime)
        {
            if (state != PlotState::Planted || !crop)
                return;

            crop->update(deltaTime);

            if (crop->isReady())
                state = PlotState::Ready;
        }

        bool harvested()
        {
            if (state != PlotState::Ready || !crop)
                return false;

            crop.reset();
            state = PlotState::Harvested;
            reset();
            return true;
        }

        void reset()
        {
            
            state = PlotState::Untouched;
        }

        void draw(sf::RenderWindow& window) const
        {
            if (state == PlotState::Untouched)
                rectangle.setFillColor(sf::Color(100, 150, 60));
            else
                rectangle.setFillColor(sf::Color(110, 75, 45));

            window.draw(rectangle);

            if (crop)
                window.draw(crop->crop_image);
        }




    

//     Plot(sf::Vector2f position, sf::Vector2f size, double initialGrowthProgress) 
//     : rectangle(size),
      
//     {
        

    


//         // vegetable.setScale({1.5f, 1.5f});
//         // vegetable.setOrigin({32.f, 32.f});
//         // vegetable.setPosition(position + size / 2.f);
//     }
};
// Hello!