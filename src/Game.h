#include <SFML/Graphics.hpp>

class Game
{
    public:
        Game();
        void run();
    private:
        void precessEvents();
        void update();
        void render();
    
   
    private:
        sf::RenderWindow window;
        sf::CircleShape character;

    
};