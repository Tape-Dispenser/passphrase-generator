/*
 * map.c: Map library written for passphrase generator
 * Copyright (C) 2025-2026, Ada Gramiak, <adadispenser@gmail.com>
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

#ifndef MAP_H
#define MAP_H

typedef struct CharMap {
    char* keys;
    char* values;
} CharMap;

struct CharMap empty_map();

struct CharMap full_map(char* keys, char* values);

int map_add(struct CharMap* map, char key, char value);

int map_get(struct CharMap* map, char key, char* output);

int map_update(struct CharMap* map, char key, char value);

int map_delete(struct CharMap* map, char key);

#endif
