#include <gameTile.h>

GameTile::GameTile(std::string textureName, float x, float y, bool passable, bool exit){
    if (!setUpSprite("build/images/Безымянный.png")){
        return;
    }
    pos = sf::Vector2f(x,y);
    sprite.setPosition(pos);
    isPassable = passable;
    isExit = exit;


}

bool GameTile::setUpSprite(std::string textureName){
    if(!texture.loadFromFile("build/images/Безымянный.png")){
        return false;
    }
    texture.setSmooth(true);
    sprite.setTexture(texture);
    sprite.setTextureRect(sf::IntRect({0, 0}, {55, 55}));
    return true;
}