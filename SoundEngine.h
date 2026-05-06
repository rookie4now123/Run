#pragma once
#include <SFML/Audio.hpp>
#include <optional>
#include <string>
using namespace sf;

class SoundEngine
{
private:
    static Music music;
    static SoundBuffer m_ClickBuffer;
    static std::optional<sf::Sound> m_ClickSound;
    static SoundBuffer m_JumpBuffer;
    static std::optional<sf::Sound> m_JumpSound;

public:
    SoundEngine();
    static SoundEngine *m_s_Instance;
    static bool mMusicIsPlaying;
    static void startMusic();
    static void pauseMusic();
    static void resumeMusic();
    static void stopMusic();
    static void playClick();
    static void playJump();
};