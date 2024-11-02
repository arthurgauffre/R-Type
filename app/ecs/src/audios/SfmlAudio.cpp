/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlAudio
*/

#include <audios/SfmlAudio.hpp>

SfmlAudio::SfmlAudio()
{
}

SfmlAudio::~SfmlAudio()
{
}

size_t SfmlAudio::createSound(const std::string &path)
{
    sf::SoundBuffer buffer;
    buffer.loadFromFile(path);
    sf::Sound sound;
    sound.setBuffer(buffer);
    _sounds[_sounds.size()] = sound;
    return _sounds.size() - 1;
}

size_t SfmlAudio::createMusic(const std::string &path)
{
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
    music->openFromFile(path);
    _musics[_musics.size()] = music;
    return _musics.size() - 1;
}

void SfmlAudio::playSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id].play();
}

void SfmlAudio::playMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->play();
}

void SfmlAudio::stopSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id].stop();
}

void SfmlAudio::stopMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->stop();
}

bool SfmlAudio::isSoundPlaying(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        return _sounds[id].getStatus() == sf::Sound::Playing;
    return false;
}

bool SfmlAudio::isMusicPlaying(size_t id)
{
    if (_musics.find(id) != _musics.end())
        return _musics[id]->getStatus() == sf::Music::Playing;
    return false;
}

EXPORT_API IAudio *createAudio()
{
    return new SfmlAudio();
}
