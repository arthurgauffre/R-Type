/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlAudio
*/

#include <audios/SfmlAudio.hpp>

/**
 * @brief Construct a new SfmlAudio object.
 *
 * This constructor initializes a new instance of the SfmlAudio class.
 */
SfmlAudio::SfmlAudio()
{
}

/**
 * @brief Destructor for the SfmlAudio class.
 *
 * This destructor is responsible for cleaning up any resources
 * that the SfmlAudio class may have acquired during its lifetime.
 * Currently, it does not perform any specific actions.
 */
SfmlAudio::~SfmlAudio()
{
}

/**
 * @brief Creates a sound from the given file path and stores it in the internal sound map.
 *
 * This function loads a sound buffer from the specified file path and associates it with a new sound object.
 * The sound and its buffer are stored in internal maps, and a unique identifier is returned.
 *
 * @param path The file path to the sound file to be loaded.
 * @return A unique identifier for the created sound. If the sound could not be loaded, returns static_cast<size_t>(-1).
 */
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

/**
 * @brief Creates a music object from the specified file path and stores it in the music container.
 *
 * This function creates a new music object using the SFML library, loads the music file from the given path,
 * and stores the music object in the internal container. It returns the index of the newly created music object.
 *
 * @param path The file path to the music file to be loaded.
 * @return The index of the newly created music object in the internal container.
 */
size_t SfmlAudio::createMusic(const std::string &path)
{
    std::shared_ptr<sf::Music> music = std::make_shared<sf::Music>();
    music->openFromFile(path);
    _musics[_musics.size()] = music;
    return _musics.size() - 1;
}

/**
 * @brief Updates the sound buffer for a given sound ID.
 *
 * This function updates the sound buffer associated with the specified sound ID.
 * If the sound ID exists in the _sounds map, it attempts to load a new sound buffer
 * from the provided file path. If the loading is successful, it updates the sound
 * buffer in the _soundBuffers map and sets the new buffer for the sound.
 *
 * @param id The unique identifier for the sound to be updated.
 * @param path The file path to the new sound buffer to be loaded.
 */
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


/**
 * @brief Updates the music associated with the given ID by loading a new file from the specified path.
 *
 * This function checks if a music object with the given ID exists in the _musics map. If it does,
 * it attempts to open the music file from the provided path and update the music object.
 *
 * @param id The unique identifier for the music object to be updated.
 * @param path The file path to the new music file to be loaded.
 */
void SfmlAudio::updateMusic(size_t id, const std::string &path)
{
    if (_musics.find(id) != _musics.end()) {
        _musics[id]->openFromFile(path);
    }
}

/**
 * @brief Plays the sound associated with the given ID.
 *
 * This function checks if a sound with the specified ID exists in the
 * _sounds map. If it does, the sound is played.
 *
 * @param id The unique identifier of the sound to be played.
 */
void SfmlAudio::playSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id]->play();
}

/**
 * @brief Plays the music associated with the given ID.
 *
 * This function checks if a music track with the specified ID exists in the
 * _musics map. If it does, the music track is played.
 *
 * @param id The ID of the music track to be played.
 */
void SfmlAudio::playMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->play();
}

/**
 * @brief Stops the sound associated with the given ID.
 *
 * This function stops the sound that corresponds to the provided ID if it exists in the sound map.
 *
 * @param id The unique identifier of the sound to be stopped.
 */
void SfmlAudio::stopSound(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        _sounds[id]->stop();
}

/**
 * @brief Stops the music associated with the given ID.
 *
 * This function checks if a music track with the specified ID exists in the
 * _musics map. If it does, the music track is stopped.
 *
 * @param id The unique identifier of the music track to stop.
 */
void SfmlAudio::stopMusic(size_t id)
{
    if (_musics.find(id) != _musics.end())
        _musics[id]->stop();
}

/**
 * @brief Checks if a sound with the given ID is currently playing.
 *
 * @param id The unique identifier of the sound to check.
 * @return true if the sound is playing, false otherwise.
 */
bool SfmlAudio::isSoundPlaying(size_t id)
{
    if (_sounds.find(id) != _sounds.end())
        return _sounds[id]->getStatus() == sf::Sound::Playing;
    return false;
}

/**
 * @brief Checks if the music with the given ID is currently playing.
 *
 * This function searches for the music with the specified ID in the _musics map.
 * If the music is found, it checks its status to determine if it is playing.
 *
 * @param id The unique identifier of the music to check.
 * @return true if the music is playing, false otherwise.
 */
bool SfmlAudio::isMusicPlaying(size_t id)
{
    if (_musics.find(id) != _musics.end())
        return _musics[id]->getStatus() == sf::Music::Playing;
    return false;
}

/**
 * @brief Factory function to create an instance of SfmlAudio.
 *
 * This function creates a new instance of the SfmlAudio class and returns it as a pointer to the IAudio interface.
 *
 * @return IAudio* Pointer to the newly created SfmlAudio instance.
 */
EXPORT_API IAudio *createAudio()
{
    return new SfmlAudio();
}
