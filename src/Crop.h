#pragma once

#include <SFML/Graphics.hpp>
#include <filesystem>
#include <memory>
#include <string>
#include <optional>

enum class CropType{
	None,
	Carrot,
	Potato
};



struct Crop
{

    CropType type = CropType::None;
    float age = 0.f;
    float growthDuration;
	sf::Texture texture;
    sf::Sprite crop_image;

	Crop(const std::filesystem::path& iconPath,  float duration, CropType type)
    : growthDuration(duration),
      texture(iconPath),
      crop_image(texture),
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
    }

    bool isReady() const
    {
        return age >= growthDuration;
    }
};