#include "SoundEngine.h"
#include <assert.h>
SoundEngine *SoundEngine::m_s_Instance = nullptr;
bool SoundEngine::mMusicIsPlaying = false;
Music SoundEngine::music;
SoundBuffer SoundEngine::m_ClickBuffer;
std::optional<sf::Sound> SoundEngine::m_ClickSound;
SoundBuffer SoundEngine::m_JumpBuffer;
std::optional<sf::Sound> SoundEngine::m_JumpSound;

SoundEngine::SoundEngine()
{
    assert(m_s_Instance == nullptr);
    m_s_Instance = this;

    if (!m_ClickBuffer.loadFromFile("sound/hit.wav"))
    {
        // If loading fails, print an error and exit.
        throw std::runtime_error("Failed to load texture: sound/hit.wav");
    }
    m_ClickSound.emplace(m_ClickBuffer);

    if (!m_JumpBuffer.loadFromFile("sound/jump.wav"))
    {
        // If loading fails, print an error and exit.
        throw std::runtime_error("Failed to load texture: sound/jump.wav");
    }
    m_JumpSound.emplace(m_JumpBuffer);
}
void SoundEngine::playClick()
{
    m_ClickSound->play();
}
void SoundEngine::playJump()
{
    m_JumpSound->play();
}
void SoundEngine::startMusic()
{
    if(!music.openFromFile("music/music.wav"))
    {
        throw std::runtime_error("Failed to load texture: music/music.wav");
    }

    m_s_Instance->music.play();
    m_s_Instance->music.setLooping(true);
    mMusicIsPlaying = true;
}

void SoundEngine::pauseMusic()
{
    m_s_Instance->music.pause();
    mMusicIsPlaying = false;
}
void SoundEngine::resumeMusic()
{
    m_s_Instance->music.play();
    mMusicIsPlaying = true;
}
void SoundEngine::stopMusic()
{
    m_s_Instance->music.stop();
    mMusicIsPlaying = false;
}