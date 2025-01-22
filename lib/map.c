/*
 * map.c: Map library written for passphrase generator
 * Copyright (C) 2025, Ada Gramiak, <adadispenser@gmail.com>
 *   Special thanks to: Stella
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Affero General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Affero General Public License for more details.
 *
 * You should have received a copy of the GNU Affero General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#include <stdlib.h>

typedef struct CharMap {
  char* keys;
  char* values;
};

// create a new map with empty lists (map constructor)
struct CharMap new_map() {
  struct CharMap map;
  map.keys = malloc(sizeof(char));
  map.keys[0] = 0;
  map.values = malloc(sizeof(char));
  map.values[0] = 0;
  return map;
}

// add key-value pair (input new key and new value)
int map_add(struct CharMap* map, char key, char value) {
  // returns 0 on success
  // returns -1 if key-value pair already exists in map
  char temp;
  if (map_get(map, key, &temp) == 0) {
    return -1;
  }
  int map_len = strlen(map->keys);
  map->keys = realloc(map->keys, (map_len + 2) * sizeof(char)); // map_len + 2 accounts for null terminator and the character to be added
  map->keys[map_len] = key; // add key to keys
  map->keys[map_len + 1] = 0; // add null terminator to keys
  map->values = realloc(map->values, (map_len + 2) * sizeof(char));
  map->values[map_len] = value;
  map->values[map_len + 1] = 0;
  return 0;
}

// get value (input key)
int map_get(struct CharMap* map, char key, char* output) {
  // returns 0 on success
  // returns -1 if key-value pair does not exist in map
  int index = 0;
  while (index < strlen(map->keys)) {
    if (map->keys[index] == key) {
      output = map->values[index];
      return 0;
    }
    index++;
  }
  return -1;
}

// edit value in pair (input key and new value)
int map_update(struct CharMap* map, char key, char value) {
  // returns 0 on success
  // returns -1 if key-value pair does not exist in map
  int index = 0;
  while (index < strlen(map->keys)) {
    if (map->keys[index] == key) {
      map->values[index] = value;
      return 0;
    }
    index++;
  }
  return -1;
}

// remove key-value pair (input key to remove)
int map_delete(struct CharMap* map, char key) {
  // returns 0 on success
  // returns -1 if key-value pair does not exist in map
  int index = 0;
  while (index < strlen(map->keys)) {
    if (!map->keys[index] == key) {
      index++;
      continue;
    }
    // get index of last entry (strlen)
    int last_entry = strlen(map->keys);
    // overwrite the entry at index with the last entry in the map
    map->keys[index] = map->keys[last_entry];
    map->values[index] = map->values[last_entry];
    // overwrite the duplicate entry at the end of the map with a null terminator
    map->keys[last_entry] = 0;
    map->values[last_entry] = 0;
    // shrink allocated memory size for string
    // original strlen will point to the last character of the original string, which is where the new null terminator will go,
    // therefore no pointer math is needed for malloc
    map->keys = realloc(map->keys, last_entry * sizeof(char));
    map->values = realloc(map->values, last_entry * sizeof(char));
    return 0;
  }
  return -1;
}
