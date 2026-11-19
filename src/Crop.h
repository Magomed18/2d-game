#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <string>
#include <optional>
#include <iostream>

enum class CropType{
	None,
	Carrot,
	Potato
};

enum class GrowthStage
{
    Seed,
    Sprout,
    Grown
};



struct Crop
{

    float age = 0.f;
    float growthDuration;
    CropType type = CropType::None;
    sf::Texture seedTexture;
    sf::Texture sproutTexture;
    sf::Texture grownTexture;
    sf::Sprite crop_image;

	Crop(const std::filesystem::path& seedPath, const std::filesystem::path& sproutPath, const std::filesystem::path& grownPath, float duration, CropType type)
    : growthDuration(duration),
      seedTexture(seedPath),
      sproutTexture(sproutPath),
      grownTexture(grownPath),
      crop_image(seedTexture),
      type(type)
{
    const auto bounds = crop_image.getLocalBounds();

    crop_image.setOrigin(
        bounds.position + bounds.size / 2.f
    );
}

    void update(float deltaTime)
    {
        age += deltaTime;
        const auto stage = getStage();

        if (stage == GrowthStage::Seed)
        {
            crop_image.setTexture(seedTexture);
        }
        else if (stage == GrowthStage::Sprout)
        {
            crop_image.setTexture(sproutTexture);
        }
        else if (stage == GrowthStage::Grown)
        {
            crop_image.setTexture(grownTexture);
        }
    }

    // bool isReady() const
    // {
    //     return age >= growthDuration;
    //     std::cout << "Crop is ready for harvest!" << std::endl;
    // }


    GrowthStage getStage() const
    {
        if (age >= growthDuration)
            return GrowthStage::Grown;

        if (age >= growthDuration / 2.f)
            return GrowthStage::Sprout;

        return GrowthStage::Seed;
    }

};