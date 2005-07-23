#include "audio.h"
#include "alloc.h"
#include "game.h"

Audio::Audio()
{
    int i;

    // Initialize audio
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);
    Mix_AllocateChannels(MIXER_CHANNELS);

    // Reseve memory for arrays and set to NULL
    music_list = MALLOC_ARRAY(Mix_Music *, MUSIC_SIZE);
    chunk_list = MALLOC_ARRAY(Mix_Chunk *, CHUNK_SIZE);
    for (i = 0; i < MUSIC_SIZE; i++) 
        music_list[i] = NULL;
    for (i = 0; i < CHUNK_SIZE; i++)
        chunk_list[i] = NULL;
    size_music = MUSIC_SIZE;
    size_chunk = CHUNK_SIZE;
    game->print("Audio ready");
}

Audio::~Audio()
{
    int i;

    for (i = 0; i < size_music; i++)
	if (music_list[i] != NULL)
	    Mix_FreeMusic(music_list[i]);

    for (i = 0; i < size_chunk; i++)
	if (chunk_list[i] != NULL)
	    Mix_FreeChunk(chunk_list[i]);
}

int Audio::addMusic(char *filename)
{
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
	Mix_Music **new_list = REALLOC_ARRAY(Mix_Music *, music_list,
					    size_music + MUSIC_SIZE);
	size_music += MUSIC_SIZE;
	index = size_music;
    }

    // Load and add to list
    music = Mix_LoadMUS(filename);
    music_list[index] = music;

    // Return music id
    return index;
}

int Audio::addChunk(char *filename)
{
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
	Mix_Chunk **new_list = MALLOC_ARRAY(Mix_Chunk *, 
					    size_chunk + CHUNK_SIZE);
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
}

void Audio::deleteMusic(int i)
{
    Mix_FreeMusic(music_list[i]);
    music_list[i] = NULL;
}

void Audio::deleteChunk(int i)
{
    Mix_FreeChunk(chunk_list[i]);
    chunk_list[i] = NULL;
}

void Audio::playMusic(int i)
{
    //Mix_Music *music;
    //    music = Mix_LoadMUS(music_list[id]);
    //    music = Mix_LoadMUS(RESOURCE_DIR("data/the-brain.mp3"));
    Mix_PlayMusic(music_list[i], 1);
}

void Audio::stopMusic()
{
    // TODO
}

void Audio::playChunk(int i)
{
    Mix_PlayChannel(-1, chunk_list[i], 0);
}
