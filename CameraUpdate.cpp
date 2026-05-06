#include "CameraUpdate.h"
#include "PlayerUpdate.h"

FloatRect *CameraUpdate::getPositionPointer()
{
    return &m_Position;
}
void CameraUpdate::assemble(
    shared_ptr<LevelUpdate> levelUpdate,
    shared_ptr<PlayerUpdate> playerUpdate)
{
    m_PlayerPosition =
        playerUpdate->getPositionPointer();
}

InputReceiver *CameraUpdate::getInputReceiver()
{
    m_InputReceiver = new InputReceiver;
    m_ReceivesInput = true;
    return m_InputReceiver;
}

void CameraUpdate::handleInput()
{
    m_Position.size.x = 1.0f;
    for (const sf::Event &event : m_InputReceiver->getEvents())
    {
        // Handle mouse wheel event for zooming
        if (const auto *mouseWheelScrolled = event.getIf<sf::Event::MouseWheelScrolled>())
        {
            if (mouseWheelScrolled->wheel == sf::Mouse::Wheel::Vertical)
            {
                // Accumulate the zoom factor based on delta
                m_Position.size.x *= (mouseWheelScrolled->delta > 0) ? 0.95f : 1.05f;
            }
        }
    }
    m_InputReceiver->clearEvents();
}

void CameraUpdate::update(float fps)
{
    if (m_ReceivesInput)
    {
        handleInput();
        m_Position.position.x = m_PlayerPosition->position.x;
        m_Position.position.y = m_PlayerPosition->position.y;
    }
    else
    {
        m_Position.position.x = m_PlayerPosition->position.x;
        m_Position.position.y = m_PlayerPosition->position.y;
        m_Position.size.x = 1;
    }
}