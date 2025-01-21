#ifndef MAP_H
#define MAP_H

typedef struct CharMap {
    char* keys;
    char* values;
};

int map_add(CharMap* map, char key, char value);

int map_get(CharMap* map, char key, char* output);

int map_edit(CharMap* map, char key, char value);

int map_delete(CharMap* map, char key, char value);

#endif
