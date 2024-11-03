/*
** EPITECH PROJECT, 2024
** R-Type
** File description:
** AAudio
*/

#pragma once

#include <r-type/IAudio.hpp>

class AAudio : public IAudio {
    public:
        AAudio(): IAudio(){};
        virtual ~AAudio() = default;

        /**
         * @brief Creates a sound from the specified file path.
         * 
         * This function loads a sound from the given file path and returns an identifier
         * for the created sound. The identifier can be used to reference the sound in
         * subsequent operations.
         * 
         * @param path The file path to the sound file.
         * @return A size_t identifier for the created sound.
         */
        virtual size_t createSound(const std::string &path) = 0;
        /**
         * @brief Creates a music object from the specified file path.
         * 
         * This function loads a music file from the given path and creates a music object
         * that can be used for playback. The function returns a unique identifier for the
         * created music object.
         * 
         * @param path The file path to the music file.
         * @return A unique identifier for the created music object.
         */
        virtual size_t createMusic(const std::string &path) = 0;

        /**
         * @brief Updates the sound associated with the given ID.
         * 
         * This function updates the sound resource identified by the specified ID
         * with the new sound file located at the provided path.
         * 
         * @param id The unique identifier of the sound to be updated.
         * @param path The file path to the new sound resource.
         */
        virtual void updateSound(size_t id, const std::string &path) = 0;
        /**
         * @brief Updates the music track with the specified ID.
         * 
         * This function updates the music track associated with the given ID to the new
         * track specified by the path. The path should point to a valid audio file.
         * 
         * @param id The unique identifier of the music track to be updated.
         * @param path The file path to the new music track.
         */
        virtual void updateMusic(size_t id, const std::string &path) = 0;

        /**
         * @brief Plays a sound based on the provided sound ID.
         * 
         * This function is responsible for playing a sound corresponding to the given
         * sound ID. The implementation of this function should handle the retrieval
         * and playback of the sound.
         * 
         * @param id The unique identifier of the sound to be played.
         */
        virtual void playSound(size_t id) = 0;
        /**
         * @brief Plays the music track associated with the given ID.
         * 
         * This function starts playing the music track that corresponds to the specified ID.
         * 
         * @param id The unique identifier of the music track to be played.
         */
        virtual void playMusic(size_t id) = 0;

        /**
         * @brief Stops the sound associated with the given ID.
         * 
         * This function stops the playback of a sound that was previously started.
         * The sound is identified by the provided ID.
         * 
         * @param id The unique identifier of the sound to stop.
         */
        virtual void stopSound(size_t id) = 0;
        /**
         * @brief Stops the music with the given ID.
         * 
         * This function stops the playback of the music track identified by the specified ID.
         * 
         * @param id The unique identifier of the music track to stop.
         */
        virtual void stopMusic(size_t id) = 0;

        /**
         * @brief Checks if a sound is currently playing.
         * 
         * @param id The unique identifier of the sound.
         * @return true if the sound is playing, false otherwise.
         */
        virtual bool isSoundPlaying(size_t id) = 0;
        /**
         * @brief Check if the music with the given ID is currently playing.
         * 
         * @param id The unique identifier of the music track.
         * @return true if the music is playing, false otherwise.
         */
        virtual bool isMusicPlaying(size_t id) = 0;

    protected:
    private:
};
