/*

basic help:
----------

How to create the class:
 Audio audio = new Audio();
SDL_mixer will be started and free memory to save chunks and musics will be
allocated.

How to add a music and a chunk:
 int myMusic = audio.AddMusic(filename);
 int myChunk = audio.AddChunk(filename);
The functions AddMusic and AddChunk will add a special id into myMusic and
myChunk.

How to play music and chunk:
 audio.PlayMusic(myMusic);
 audio.PlayChunk(myChunk);
myMusic and myChunk tells the class which music or chunk should be played.

*/

#ifndef AUDIO_H
#define AUDIO_H

#include <SDL.h>
#include <SDL_mixer.h>

// Array size of music_list and chunk_list
#ifndef MUSIC_SIZE
#define MUSIC_SIZE 10
#endif
#ifndef CHUNK_SIZE
#define CHUNK_SIZE 100
#endif

#ifndef MIXER_CHANNELS
#define MIXER_CHANNELS 5
#endif

class Audio {
private:
    // An array for musics and chunks
    Mix_Music **music_list;
    Mix_Chunk **chunk_list;
    int size_music, size_chunk;
        
public:
    Audio();
    ~Audio();

    void init();
    void free();

    int AddMusic(char *filename);
    int AddChunk(char *filename);

    void DeleteMusic(int id);
    void DeleteChunk(int id);

    void PlayMusic(int id);
    void StopMusic();
    void PlayChunk(int id);
};

#endif
