#ifndef MAP_H
#define MAP_H

/* Map Format enums */
enum {
    MF_ID = (1 << 17) - 1,
    MF_ANIM = 1 << 17,
};

typedef struct _map_data {
    /* head data */
    unsigned int width;
    unsigned int height;
    unsigned int anim_count;
    unsigned int anim_ticks;

    /* animation data */
    unsigned int *anims;

    /* map data itself */
    unsigned int *data; 
} map_data;

void init_map();
void write_map(char *filename);
void read_map(char *filename);
void fill_map(int id);
void map_put(int id, int xt, int yt);
void map_new(unsigned int width, unsigned int height, unsigned int anim_count, unsigned int anim_ticks);

#endif
