#include <SDL_mixer.h>

#ifndef AUDIO_H
#define AUDIO_H

// Array size of music_list and chunk_list
#define MUSIC_SIZE 10
#define CHUNK_SIZE 100

class Audio
{
private:
    // An array of all saved musics and chunks
    Mix_Music *music_list;
    Mix_Chunk *chunk_list;
        
public:
    Audio();
    ~Audio();

    int AddMusic(char *filename);
    int AddChunk(char *filename);
};

#endif
