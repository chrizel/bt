#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>

// Array size of music_list and chunk_list
#define MUSIC_SIZE 10
#define CHUNK_SIZE 100

class Audio {
private:
    // An array of all saved musics and chunks
    Mix_Music **music_list;
    Mix_Chunk **chunk_list;
    int size_music, size_chunk;
        
public:
    Audio();
    ~Audio();

    void init();

    int AddMusic(char *filename);
    int AddChunk(char *filename);

    void PlayMusic(int id);
    void StopMusic();
    void PlayChunk(int id);
};

#endif
