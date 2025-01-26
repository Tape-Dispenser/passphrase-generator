/*
 * Passphrase Generator: Command line tool to generate cryptographically secure passphrases
 * Copyright (C) 2025, Ada Gramiak, <adadispenser@gmail.com>
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

#include "lib/map.h"
#include <stdio.h>

int return_status;
char output;

int main() {
  printf("generating a new map...\n");
  struct CharMap test_map = new_map();
  printf("generated a new map.\n");
  
  printf("\n");
  
  printf("adding key: 'a', value: '1' to the map...\n");
  map_add(&test_map, 'a', '1');
  printf("added key to map.");
  
  printf("\n");

  printf("searching for key 'a' in map...\n");
  output;
  return_status = map_get(&test_map, 'a', &output);
  if (return_status != 0) {
    printf("Error! Failed to find key 'a' in test_map!");
    return -1;
  }
  printf("test_map contains key 'a' with value '%c' assosiated.\n", output);

  printf("\n");

  printf("updating key 'a' to value 'b' in test_map...\n");
  map_update(&test_map, 'a', 'b');
  printf("updated test_map.\n");

  printf("\n");


  printf("searching for key 'a' in map...\n");
  output;
  return_status = map_get(&test_map, 'a', &output);
  if (return_status != 0) {
    printf("Error! Failed to find key 'a' in test_map!");
    return -1;
  }
  printf("test_map contains key 'a' with value '%c' assosiated.\n", output);

  printf("\n");

  printf("deleting key 'a' from map...");
  map_delete(&test_map, 'a');
  printf("deleted key from map.\n");

  printf("\n");

  printf("searching for key 'a' in map...\n");
  output;
  return_status = map_get(&test_map, 'a', &output);
  if (return_status == 0) {
    printf("Error! Failed delete key 'a' in test_map, and is associated with value 'c'!", output);
    return -1;
  }
  printf("test_map does not contain key 'a'\n");
  
  printf("\n");

  

  printf("tests completed with no errors.\n");
  return 0;
}