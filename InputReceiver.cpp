#include "InputReceiver.h"
void InputReceiver::addEvent(const sf::Event &event)
{
    m_Events.push_back(event);
}

const std::vector<sf::Event> &InputReceiver::getEvents() const
{
    return m_Events;
}

void InputReceiver::clearEvents()
{
    m_Events.clear();
}