#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <string>

enum class CropType{
	None,
	Carrot,
	Potato
};

enum class GrowthStage{
	
    None,
    Seedling,
    Sprout,
    Grown
};

struct Crop
{
    CropType type = CropType::None;
    GrowthStage stage = GrowthStage::None;
    float age = 0.f;
	sf::Texture texture;
    sf::Sprite crop_image;
`
	Crop(const std::filesystem::path& iconPath, double initialGrowthProgress)
	: age(initialGrowthProgress),
      texture(iconPath),
	  crop_image(texture)
	{

    }

    void update(float deltaTime)
    {
        age += deltaTime;
    }

    bool isReady() const
    {
        return age >= 10;
    }
};