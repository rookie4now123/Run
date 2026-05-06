#include "CameraGraphics.h"
#include "CameraUpdate.h"

CameraGraphics::CameraGraphics(
    RenderWindow *window, Texture *texture,
    Vector2f viewSize, FloatRect viewport) : m_Text(m_Font)
{
    m_Window = window;
    m_Texture = texture;
    m_View.setSize(viewSize);
    m_View.setViewport(viewport);
    // The mini map viewport is less than 1
    if (viewport.size.x < 1)
    {
        m_IsMiniMap = true;
    }
    else
    {
        // Only the full screen camera has the time text
        if (!m_Font.openFromFile("fonts/KOMIKAP_.ttf"))
        {
            throw std::runtime_error("Failed to load font: fonts/KOMIKAP_.ttf");
        }

        m_Text.setFillColor(Color(255, 0, 0, 255));
        m_Text.setScale({0.2f, 0.2f});
    }
};

void CameraGraphics::assemble(
    VertexArray &canvas,
    shared_ptr<Update> genericUpdate,
    IntRect texCoords)
{
    shared_ptr<CameraUpdate> cameraUpdate =
        static_pointer_cast<CameraUpdate>(genericUpdate);
    m_Position = cameraUpdate->getPositionPointer();
    m_VertexStartIndex = canvas.getVertexCount();

    canvas.resize(m_VertexStartIndex + 6);
    sf::Vector2f pos(texCoords.position);
    sf::Vector2f size(texCoords.size);
    sf::Vector2f topLeft = pos;
    sf::Vector2f topRight = pos + sf::Vector2f(size.x, 0.f);
    sf::Vector2f bottomRight = pos + size;
    sf::Vector2f bottomLeft = pos + sf::Vector2f(0.f, size.y);

    // Triangle 1 (Top-Left, Top-Right, Bottom-Right)
    canvas[m_VertexStartIndex + 0].texCoords = topLeft;
    canvas[m_VertexStartIndex + 1].texCoords = topRight;
    canvas[m_VertexStartIndex + 2].texCoords = bottomRight;

    // Triangle 2 (Top-Left, Bottom-Right, Bottom-Left)
    canvas[m_VertexStartIndex + 3].texCoords = topLeft;
    canvas[m_VertexStartIndex + 4].texCoords = bottomRight;
    canvas[m_VertexStartIndex + 5].texCoords = bottomLeft;
}

float *CameraGraphics::getTimeConnection()
{
    return &m_Time;
}

void CameraGraphics::draw(VertexArray &canvas)
{
    m_View.setCenter(m_Position->position);
    Vector2f scale = m_View.getSize(); 
    Vector2f startPosition = m_View.getCenter() - (scale / 2.f);

    // 3. Define the 4 corners of the view
    sf::Vector2f topLeft     = startPosition;
    sf::Vector2f topRight    = startPosition + sf::Vector2f(scale.x, 0.f);
    sf::Vector2f bottomRight = startPosition + scale;
    sf::Vector2f bottomLeft  = startPosition + sf::Vector2f(0.f, scale.y);

    // 4. Apply positions to the 6 vertices (matching the Triangles setup in assemble)
    // Triangle 1 (Top-Left, Top-Right, Bottom-Right)
    canvas[m_VertexStartIndex + 0].position = topLeft;
    canvas[m_VertexStartIndex + 1].position = topRight;
    canvas[m_VertexStartIndex + 2].position = bottomRight;

    // Triangle 2 (Top-Left, Bottom-Right, Bottom-Left)
    canvas[m_VertexStartIndex + 3].position = topLeft;
    canvas[m_VertexStartIndex + 4].position = bottomRight;
    canvas[m_VertexStartIndex + 5].position = bottomLeft;
    if (m_IsMiniMap)
    {
        if (m_View.getSize().x <
                MAX_WIDTH &&
            m_Position->size.x > 1)
        {
            m_View.zoom(m_Position->size.x);
        }
        else if (m_View.getSize().x >
                     MIN_WIDTH &&
                 m_Position->size.x < 1)
        {
            m_View.zoom(m_Position->size.x);
        }
    }
    m_Window->setView(m_View);
    // Draw the time UI but only in the main camera
    if (!m_IsMiniMap)
    {
        m_Text.setString(std::to_string(m_Time));
        m_Text.setPosition(
            m_Window->mapPixelToCoords(Vector2i(5, 5)));
        m_Window->draw(m_Text);
    }
    // Draw the main canvas
    RenderStates states;
    states.texture = m_Texture;
    m_Window->draw(canvas, states);
    //m_Window->draw(canvas, m_Texture);
}