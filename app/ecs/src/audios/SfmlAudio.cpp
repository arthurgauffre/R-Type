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
    auto buffer = std::make_shared<sf::SoundBuffer>();
    if (!buffer->loadFromFile(path)) {
        return static_cast<size_t>(-1);
    }

    auto sound = std::make_shared<sf::Sound>();
    sound->setBuffer(*buffer);

    size_t id = _sounds.size();
    _sounds[id] = sound;
    _soundBuffers[id] = buffer;

    return id;
}

size_t SfmlAudio::createMusic(const std::string &path)
{
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
    music->openFromFile(path);
    _musics[_musics.size()] = music;
    return _musics.size() - 1;
}

void SfmlAudio::updateSound(size_t id, const std::string &path)
{
    if (_sounds.find(id) != _sounds.end()) {
        auto buffer = std::make_shared<sf::SoundBuffer>();
        if (!buffer->loadFromFile(path)) {
            return;
        }
        
        _soundBuffers[id] = buffer;
        _sounds[id]->setBuffer(*buffer);
    }
}


void SfmlAudio::updateMusic(size_t id, const std::string &path)
{
    if (_musics.find(id) != _musics.end()) {
        _musics[id]->openFromFile(path);
    }
}

void SfmlAudio::playSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id]->play();
}

void SfmlAudio::playMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->play();
}

void SfmlAudio::stopSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id]->stop();
}

void SfmlAudio::stopMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->stop();
}

bool SfmlAudio::isSoundPlaying(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        return _sounds[id]->getStatus() == sf::Sound::Playing;
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
