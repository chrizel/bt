#include <iostream>
#include "audio.h"

Audio::Audio()
{
    init();
}

Audio::~Audio()
{
    free();
}

void Audio::init()
{
#ifndef DISABLE_AUDIO
    int i;

    // Initialize audio
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(MIXER_CHANNELS);

    // Reseve memory for arrays and set to NULL
    music_list = new Mix_Music*[MUSIC_SIZE];
    chunk_list = new Mix_Chunk*[CHUNK_SIZE];
    for (i = 0; i < MUSIC_SIZE; i++) 
	music_list[i] = NULL;
    for (i = 0; i < CHUNK_SIZE; i++)
	chunk_list[i] = NULL;
    size_music = MUSIC_SIZE;
    size_chunk = CHUNK_SIZE;
#endif
}

void Audio::free()
{
    int i;

    for (i = 0; i < size_music; i++)
	if (music_list[i] != NULL)
	    Mix_FreeMusic(music_list[i]);

    for (i = 0; i < size_chunk; i++)
	if (chunk_list[i] != NULL)
	    Mix_FreeChunk(chunk_list[i]);
}

int Audio::AddMusic(char *filename)
{
#ifndef DISABLE_AUDIO
    Mix_Music *music;
    int index = -1;
    int i;

    // Searching for a free place
    for (i = 0; i < size_music; i++) {
	if (music_list[i] == NULL) {
	    index = i;
	    break;
	}
    }

    // If no place was found... a new will created...
    if (index == -1) {
	Mix_Music **new_list = new Mix_Music*[size_music + MUSIC_SIZE];
	for (i = 0; i < size_music; i++)
	    new_list[i] = music_list[i];
	size_music += MUSIC_SIZE;
	index = size_music;
    }

    // Load and add to list
    music = Mix_LoadMUS(filename);
    music_list[index] = music;

    // Return music id
    return index;
#endif
}

int Audio::AddChunk(char *filename)
{
#ifndef DISABLE_AUDIO
    Mix_Chunk *chunk;
    int index = -1;
    int i;

    // Searching for a free place
    for (i = 0; i < size_chunk; i++) {
	if (music_list[i] == NULL) {
	    index = i;
	    break;
	}
    }

    // If no place was found... a new will created...
    if (index == -1) {
	Mix_Chunk **new_list = new Mix_Chunk*[size_chunk + CHUNK_SIZE];
	for (i = 0; i < size_chunk; i++)
	    new_list[i] = chunk_list[i];
	size_chunk += CHUNK_SIZE;
	index = size_chunk;
    }

    // Load and add to list
    chunk = Mix_LoadWAV(filename);
    chunk_list[index] = chunk;

    // Return chunk id
    return index;
#endif
}

void Audio::DeleteMusic(int id)
{
#ifndef DISABLE_AUDIO
    Mix_FreeMusic(music_list[id]);
    music_list[id] = NULL;
#endif
}

void Audio::DeleteChunk(int id)
{
#ifndef DISABLE_AUDIO
    Mix_FreeChunk(chunk_list[id]);
    chunk_list[id] = NULL;
#endif
}

void Audio::PlayMusic(int id)
{
#ifndef DISABLE_AUDIO
    //Mix_Music *music;
    //    music = Mix_LoadMUS(music_list[id]);
    //    music = Mix_LoadMUS("data/the-brain.mp3");
    //printf("test\n");
    Mix_PlayMusic(music_list[id], 1);
#endif
}

void Audio::StopMusic()
{
#ifndef DISABLE_AUDIO
    // TODO
#endif
}

void Audio::PlayChunk(int id)
{
#ifndef DISABLE_AUDIO
    Mix_PlayChannel(-1, chunk_list[id], 0);
#endif
}
