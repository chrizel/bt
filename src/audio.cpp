#include "audio.h"

Audio::Audio()
{
    init();
}

Audio::~Audio()
{
    // TODO
}

void Audio::init()
{
    int i;

    // Initialize audio
    Mix_OpenAudio(22050, MIX_DEFAULT_FORMAT, 2, 1024);

    // Reseve memory for arrays and set to NULL
    music_list = new Mix_Music*[MUSIC_SIZE];
    chunk_list = new Mix_Chunk*[CHUNK_SIZE];
    for (i = 0; i < MUSIC_SIZE; i++) 
	music_list[i] = NULL;
    for (i = 0; i < CHUNK_SIZE; i++)
	chunk_list[i] = NULL;
    size_music = MUSIC_SIZE;
    size_chunk = CHUNK_SIZE;
}

int Audio::AddMusic(char *filename)
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
}

int Audio::AddChunk(char *filename)
{
    // TODO
}

void Audio::PlayMusic(int id)
{
    //Mix_Music *music;
    //    music = Mix_LoadMUS(music_list[id]);
    //    music = Mix_LoadMUS("data/the-brain.mp3");
    //printf("test\n");
    Mix_PlayMusic(music_list[id], 1);
}

void Audio::StopMusic()
{

}

void Audio::PlayChunk(int id)
{

}
