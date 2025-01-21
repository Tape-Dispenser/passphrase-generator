/*
 * map.c: Map library written for passphrase generator
 * Copyright (C) 2025, Ada Gramiak
 *   Co-author: Stella
 *   Contact: <adadispenser@gmail.com>
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
CharMap new_map() {
  struct CharMap map;
  map.keys = malloc(sizeof(char));
  map.keys[0] = 0;
  map.values = malloc(sizeof(char));
  map.values[0] = 0;
  return map;
}

// add key-value pair (input new key and new value)
int map_add(CharMap* map, char key, char value) {
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
int map_get(CharMap* map, char key, char* output) {
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
int map_update(CharMap* map, char key, char value) {
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
int map_delete(CharMap* map, char key) {
  // returns 0 on success
  // returns -1 if key-value pair does not exist in map
  int index = 0;
  while (index < strlen(map->keys)) {
    if (!map->keys[index] == key) {
      index++;
      continue;
    }
    // strlen will return length of string but since one character is removed no pointer math is required
    int new_size = strlen(map->keys);
    // create new string containing all characters after key-value pair to delete

    // paste new string at the index of the key-value pair to delete (overwriting pair to delete)

    // add a new null terminator

    // shrink allocated memory size for string
    return 0;
  }
  return -1;
}