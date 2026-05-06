#include "SFML/Graphics.hpp"
#include <vector>
#include "GameObject.h"
#include "Factory.h"
#include "InputDispatcher.h"

const int SCREEN_WIDTH = 800;
const int SCREEN_HEIGHT = 600;

using namespace std;
using namespace sf;

int main()
{
    // Create a video mode object
    sf::VideoMode vm({SCREEN_WIDTH, SCREEN_HEIGHT}, 32);
    // Create and open a window for the game
    sf::RenderWindow window(VideoMode::getDesktopMode(), "Pong Game", State::Windowed);

    sf::VertexArray canvas(sf::PrimitiveType::Triangles);
    InputDispatcher inputDispatcher(&window);
    vector<GameObject> gameObjects;
    Factory factory(&window);

    factory.loadLevel(gameObjects,
                      canvas,
                      inputDispatcher);
    Clock clock;
    const Color BACKGROUND_COLOR(100, 100, 100, 255);
    // This call will send the vector of game objects
    // the canvas to draw on and the input dispatcher
    // to the factory to set up the game.
    int score = 0;
    int lives = 3;


    Font font;

    if (!font.openFromFile("fonts/KOMIKAP_.ttf"))
    {
        return -1;
    }
    sf::Text hud(font, "Score: 0 Lives: 3", 75);

    hud.setFillColor(Color::White);
    hud.setPosition({20, 20});

    while (window.isOpen())
    {
        float timeTakenInSeconds = clock.restart().asSeconds();
        inputDispatcher.dispatchInputEvents();
        window.clear(BACKGROUND_COLOR);
        for (auto &gameObject : gameObjects)
        {
            gameObject.update(timeTakenInSeconds);
        }
        for (auto &gameObject : gameObjects)
        {
            gameObject.draw(canvas);
        }
        window.draw(canvas, factory.m_Texture);
        window.draw(hud);
        window.display();
    }
    return 0;
}