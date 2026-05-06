#include "InputDispatcher.h"
InputDispatcher::InputDispatcher(RenderWindow *window)
{
    m_Window = window;
}

void InputDispatcher::dispatchInputEvents()
{
    while (const std::optional event = m_Window->pollEvent())
    {
        // 1. Handle Global Window Events (Directly in Dispatcher)
        if (event->is<sf::Event::Closed>())
        {
            m_Window->close();
        }

        for (const auto& ir : m_InputReceivers)
        {
            // Since 'event' is a std::optional, we use '*event' 
            // to pass the actual sf::Event to your receivers
            ir->addEvent(*event);
        }
    }
}

void InputDispatcher::registerNewInputReceiver(InputReceiver* ir)
{
    m_InputReceivers.push_back(ir);
}