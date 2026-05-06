#include "PlayerGraphics.h"
#include "PlayerUpdate.h"

void PlayerGraphics::assemble(sf::VertexArray& canvas, std::shared_ptr<Update> genericUpdate, sf::IntRect texCoords)
{
    m_PlayerUpdate = std::static_pointer_cast<PlayerUpdate>(genericUpdate);
    m_Position = m_PlayerUpdate->getPositionPointer();
    
    m_VertexStartIndex = canvas.getVertexCount();
    
    // SFML 3: We need 6 vertices for a rectangle (2 triangles)
    canvas.resize(canvas.getVertexCount() + 6);

    sf::Vector2f pos = sf::Vector2f(texCoords.position);
    sf::Vector2f size = sf::Vector2f(texCoords.size);

    // Triangle 1 (Vertices 0, 1, 2)
    canvas[m_VertexStartIndex + 0].texCoords = pos;
    canvas[m_VertexStartIndex + 1].texCoords = pos + sf::Vector2f(size.x, 0);
    canvas[m_VertexStartIndex + 2].texCoords = pos + size;

    // Triangle 2 (Vertices 3, 4, 5 -> which are 2, 3, 0)
    canvas[m_VertexStartIndex + 3].texCoords = pos + size;
    canvas[m_VertexStartIndex + 4].texCoords = pos + sf::Vector2f(0, size.y);
    canvas[m_VertexStartIndex + 5].texCoords = pos;
}

void PlayerGraphics::draw(VertexArray &canvas)
{
    const Vector2f &position = m_Position->position;
    const Vector2f &scale = m_Position->size;
    canvas[m_VertexStartIndex + 0].position = position;
    canvas[m_VertexStartIndex + 1].position = position + sf::Vector2f(scale.x, 0);
    canvas[m_VertexStartIndex + 2].position = position + scale;

    // Triangle 2
    canvas[m_VertexStartIndex + 3].position = position + scale;
    canvas[m_VertexStartIndex + 4].position = position + sf::Vector2f(0, scale.y);
    canvas[m_VertexStartIndex + 5].position = position;
}