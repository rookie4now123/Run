#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
using namespace sf;
using namespace std;

class InputReceiver
{
private:
    std::vector<sf::Event> m_Events;

public:
    void addEvent(const sf::Event &event);

    // Return a const reference to protect the data from accidental outside modification
    const std::vector<sf::Event> &getEvents() const;

    void clearEvents();
};