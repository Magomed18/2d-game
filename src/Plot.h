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

        bool prepare()
        {
            if (state != PlotState::Untouched)
                return false;

            rectangle.setFillColor(sf::Color(110, 75, 45));
            state = PlotState::Prepared;
            return true;
        }


        bool plant(const std::filesystem::path& seedPath, const std::filesystem::path& sproutPath, const std::filesystem::path& grownPath, float growthDuration, CropType type)
        {
            if (state != PlotState::Prepared || crop.has_value())
                return false;

            crop.emplace(seedPath, sproutPath, grownPath, growthDuration, type);

            const auto center =
                rectangle.getPosition() + rectangle.getSize() / 2.f;

            crop->crop_image.setPosition(center);

            state = PlotState::Planted;
            return true;
        }
        // {
        //     if (state != PlotState::Prepared || crop.has_value())
        //         return false;

        //     crop.emplace(imagePath, 10.f, CropType::Carrot);

        //     const auto center =
        //         rectangle.getPosition() + rectangle.getSize() / 2.f;

        //     crop->crop_image.setPosition(center);

        //     state = PlotState::Planted;
        //     return true;
        // }

        void update(float deltaTime)
        {
            if (state != PlotState::Planted || !crop)
                return;

            crop->update(deltaTime);

            

        }

        bool harvest()
        {
            if (!crop || crop->getStage() != GrowthStage::Grown)
                return false;

            crop.reset();
            state = PlotState::Untouched;
            return true;
        }

        void draw(sf::RenderWindow& window) const
        {

            window.draw(rectangle);

            if (!crop)
                return;
            
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