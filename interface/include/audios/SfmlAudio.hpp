/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** SfmlAudio
*/

#pragma once

#include <SFML/Audio.hpp>
#include <r-type/AAudio.hpp>

class SfmlAudio: public AAudio {
    public:
        /**
         * @class SfmlAudio
         * @brief A class that handles audio functionalities using the SFML library.
         *
         * This class provides methods to manage and control audio playback, 
         * including loading audio files, playing, pausing, and stopping sounds.
         */
        SfmlAudio();
        /**
         * @brief Destructor for the SfmlAudio class.
         * 
         * This destructor is responsible for cleaning up any resources
         * that were allocated by the SfmlAudio class.
         */
        ~SfmlAudio();

        /**
         * @brief Creates a sound from the given file path.
         * 
         * This function loads a sound from the specified file path and returns an identifier
         * for the created sound. The identifier can be used to manage the sound within the system.
         * 
         * @param path The file path to the sound file.
         * @return A size_t identifier for the created sound.
         */
        size_t createSound(const std::string &path) override;
        /**
         * @brief Creates a music object from the specified file path.
         * 
         * This function loads a music file from the given path and creates a music object
         * that can be played, paused, or stopped. The music object is managed internally
         * and can be referenced using the returned identifier.
         * 
         * @param path The file path to the music file to be loaded.
         * @return A unique identifier for the created music object.
         */
        size_t createMusic(const std::string &path) override;

        /**
         * @brief Updates the sound associated with the given ID.
         * 
         * This function updates the sound resource identified by the specified ID
         * with a new sound file located at the provided path.
         * 
         * @param id The unique identifier of the sound to be updated.
         * @param path The file path to the new sound resource.
         */
        void updateSound(size_t id, const std::string &path) override;
        /**
         * @brief Updates the music with the specified ID.
         * 
         * This function updates the music resource identified by the given ID with a new audio file located at the specified path.
         * 
         * @param id The unique identifier of the music resource to be updated.
         * @param path The file path to the new audio file.
         */
        void updateMusic(size_t id, const std::string &path) override;

        /**
         * @brief Plays a sound based on the given sound ID.
         * 
         * This function will play the sound associated with the provided ID.
         * 
         * @param id The unique identifier of the sound to be played.
         */
        void playSound(size_t id) override;
        /**
         * @brief Plays the music associated with the given ID.
         * 
         * This function will start playing the music track that corresponds to the specified ID.
         * 
         * @param id The unique identifier of the music track to be played.
         */
        void playMusic(size_t id) override;

        /**
         * @brief Stops the sound with the given ID.
         * 
         * This function stops the playback of the sound identified by the specified ID.
         * If the sound is already stopped, this function has no effect.
         * 
         * @param id The unique identifier of the sound to stop.
         */
        void stopSound(size_t id) override;
        /**
         * @brief Stops the music with the given ID.
         * 
         * This function stops the playback of the music track identified by the specified ID.
         * 
         * @param id The unique identifier of the music track to stop.
         */
        void stopMusic(size_t id) override;

        /**
         * @brief Checks if a sound with the given ID is currently playing.
         * 
         * @param id The unique identifier of the sound.
         * @return true if the sound is playing, false otherwise.
         */
        bool isSoundPlaying(size_t id) override;
        /**
         * @brief Checks if the music with the given ID is currently playing.
         * 
         * @param id The unique identifier of the music track.
         * @return true if the music is playing, false otherwise.
         */
        bool isMusicPlaying(size_t id) override;

    protected:
    private:
        /**
         * @brief A map that associates unique identifiers with shared pointers to sf::Sound objects.
         * 
         * This unordered map is used to manage and access sound objects efficiently using their unique identifiers.
         * 
         * @key size_t The unique identifier for each sound.
         * @value std::shared_ptr<sf::Sound> A shared pointer to an sf::Sound object.
         */
        std::unordered_map<size_t, std::shared_ptr<sf::Sound>> _sounds;
        /**
         * @brief A map that associates unique identifiers with shared pointers to sf::SoundBuffer objects.
         * 
         * This unordered map is used to store and manage sound buffers, allowing for efficient retrieval
         * and sharing of sound resources within the application. Each sound buffer is identified by a 
         * unique size_t key.
         */
        std::unordered_map<size_t, std::shared_ptr<sf::SoundBuffer>> _soundBuffers;
        /**
         * @brief A map that associates unique identifiers with shared pointers to sf::Music objects.
         * 
         * This unordered map uses size_t as the key type and std::shared_ptr<sf::Music> as the value type.
         * It allows for efficient retrieval and management of music resources by their unique identifiers.
         */
        std::unordered_map<size_t, std::shared_ptr<sf::Music>> _musics;
};
