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

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <getopt.h>
#include <string.h>
#include "lib/map.h"

unsigned int length = 16;
char* seperator = " ";
unsigned char words = 5;

struct CharMap number_map;

// mutators will have a 1 in x chance of applying per character
unsigned int mutation_chance = 4;

unsigned char length_mode = 0;

unsigned char capitalize = 0;
unsigned char numbers = 0;
unsigned char misspell = 0;
unsigned char special_chars = 0;

int is_alpha(char input) {
  if (input >= 'A' && input <= 'Z') {
    return 1;
  } 
  if (input >= 'a' && input <= 'z') {
    return 1;
  }
  return 0;
}

char lowercase(char input) {
  // convert alphabetic character to lowercase
  if (!is_alpha(input)) {
    return 0;
  }
  if (input >= 'a' && input <= 'z') {
    return input;
  }
  return (input - 'A' + 'a');
}

unsigned short rng() {
  // read 2 bytes from /dev/random
  unsigned short output;
  FILE* random = fopen("/dev/random", "rb");
  fread(&output, sizeof(short), 1, random);
  fclose(random);
  return output;
}

char* get_word() {
  // get a random word from words.txt

  // init variables
  unsigned short index = rng();
  char c = 0;
  unsigned short line_num = 0;
  unsigned short line_index = 0;
  size_t line_len = 1;
  char* line = malloc(line_len * sizeof(char));

  // open words.txt
  FILE* words = NULL;
  words = fopen("./words.txt", "r");
  if (words == NULL) {
    puts("ERROR: Unable to open wordlist!");
    puts("Please ensure a file named words.txt exists in the same directory as the executable.");
    exit(-1);
  }

  // read each line of words.txt into the line variable
  while (c != EOF) {
    c = fgetc(words);
    if (c == '\n') {
      // end of line
      if (line_num == index) {
        line[line_index] = 0; // add null terminator
        fclose(words);
        return line + (5 * sizeof(char)); // 5 characters ahead to cut out the tab and hex index
      }
      line_num++;
      line_index = 0;
      continue;
    }
    // add character to line
    line[line_index] = c;
    line_index++;
    // resize line if necessary
    if (line_index == line_len) {
      line = realloc(line, ++line_len);
    }
  }
  // this should never be called unless line.txt gets shortened
  fclose(words);
  printf("ERROR: could not find word on line %u!", index);
  exit(-1);
}

int stoi(char* input) {
  // convert numerical string to int
  int i = 0;
  char c;
  int output = 0;
  while (i <= strlen(input)) {
    c = input[i];
    if (c == 0) {
      break;
    }
    if (c >= '0' && c <= '9') {
      output = output * 10 + (c - '0'); // convert numerical character to integer, append to output        
    } else {
      printf("Error: expected an integer argument, got \"%s\" instead.\n", input);
      exit(-1);
    }
    i++;
  }
  return output;
}

void help() {
  puts("passphrase: passphrase [-cnmp] [-l number] [-w number] [-s string]");
  puts("    Generate a passphrase");
  puts("");
  puts("    Options:");
  puts("      -h \t\t:    Print this menu.");
  puts("      -c \t\t:    Randomy capitalize letters (example: anTimoNY)");
  puts("      -n \t\t:    Randomy replace letters with numbers (example: ant1m0ny)");
  puts("      -m \t\t:    Randomy misspell words (example: animuny)");
  puts("      -p \t\t:    Randomy add special characters (example: @ntim*ny)");
  puts("      -l [number]\t:    Generate password of a specific length. If no length is specified, the default is 16 characters.");
  puts("      -w <number>\t:    Specify the number of words in passphrase. Default is 5.");
  puts("      -u <number>\t:    Specify mutator chance. (1 in x) Default is 4.");
  puts("      -s <\"string\">\t:    Specify the seperator to be used between words. If multiple characters are provided they will be chosen from randomly. Default is space. (0x20)");
  puts("");
  puts("    Exit Status:");
  puts("    Returns success unless words.txt is unable to be found, or if bad arguments are given.");

}

char* gen_passphrase() {
  // generate string of words, the output of this function can be used as a passphrase if no modifiers are selected
  char* passphrase = malloc(sizeof(char));
  char* word;
  unsigned int seperator_count = strlen(seperator);
  if (length_mode) {
    // TODO: Write length mode generation
    // generate a passphrase of a certain character count
    passphrase = realloc(passphrase, length * sizeof(char)); // idk why i always put * sizeof(char) in mallocs it does nothing :skull:
    word = get_word();
    if (misspell) {
      
    }
  } else {
    // generate a passphrase of a certain word count
    int i = 0;
    while (i < words) {
      word = get_word();
      // resize passphrase for concatenation and seperator character
      passphrase = realloc(passphrase, (strlen(passphrase) + strlen(word) + 2) * sizeof(char));
      passphrase = strcat(passphrase, word);
      if (seperator_count <= 1) {
        passphrase = strcat(passphrase, seperator);
      } else {
        int index = rng() % strlen(seperator);
        char* temp = malloc(2 * sizeof(char)); 
        temp[0] = seperator[index];
        temp[1] = 0;
        passphrase = strcat(passphrase, temp);
        free(temp);
      }
      i++;
    }
  }
  // remove trailing seperator
  passphrase[strlen(passphrase) - 1] = 0;
  return passphrase;
}

char* random_caps(char* input) {
  // capitalize letters randomly based on globally specified mutation chance
  int i = 0;
  int string_length = strlen(input);
  while (i < string_length) {
    if (rng() % mutation_chance != 0) {
      i++;
      continue;
    }
    if (input[i] < 'a' || input[i] > 'z') {
      i++;
      continue;
    }
    input[i] = input[i] - 'a' + 'A';
    i++;
  }
  return input;
}

char* random_numbers(char* input) {
  // replace letters with numbers randomly based on globally specified mutation chance
  int i = 0;
  while (i < strlen(input)) {
    char c = input[i];
    if (rng() % mutation_chance != 0) {
      i++;
      continue;
    }
    if (!is_alpha(c)) {
      i++;
      continue;
    }
    c = lowercase(c);
    char replaced;
    int return_code = map_get(&number_map, c, &replaced);
    /*
    if (return_code != 0) {
      printf("Warning! character %c not in number list!\n", c);
    }
    */
    input[i] = replaced;
    i++;
  }
  return input;
}

int main(int argc, char **argv) {
  


  int option;
  char* temp_arg;

  // parse arguments
  while ((option = getopt(argc, argv, ":hcnmpl:w:u:s:")) != -1) {
    switch (option) {
      case 'h':
        // print info and exit
        help();
        exit(0);
      case 'c':
        capitalize = 1;
        break;
      case 'n':
        numbers = 1;
        break;
      case 'm':
        misspell = 1;
        break;
      case 'p':
        special_chars = 1;
        break;
      case 'l':
        length_mode = 1;
        length = stoi(optarg);
        break;
      case 'w':
        words = stoi(optarg);
        break;
      case 's':
        seperator = malloc((strlen(optarg) + 1) * sizeof(char));
        strcpy(seperator, optarg);
        break;
      case 'u':
        mutation_chance = stoi(optarg);
        break;
      case ':':
        if (optopt == 'l') {
          length_mode = 1;
          break;
        }
        printf("Option \'%c\' missing value.\n", optopt);
        exit(-1);
      case '?':
        printf("Unknown option \'%c\'\n", optopt);
        exit(-1);
      default:
        printf("if you manage to get this error im genuinely impressed. (and hate getopt)\n");
        exit(-1);
    }
  }
  while (optind < argc) {      
    printf("extra arguments: %s\n", argv[optind]);  
    optind++;
  }

  // debug
  /*
  printf("Capitalize: %i\n", capitalize);
  printf("Numbers: %i\n", numbers);
  printf("Misspell: %i\n", misspell);
  printf("Special Characters: %i\n", special_chars);
  printf("Length Mode: %i\n", length_mode);
  printf("Length: %i\n", length);
  printf("Word Count: %i\n", words);
  printf("Seperator Characters: \"%s\"\n", seperator);
  */

  // initialize maps
  number_map = full_map("abegiloqstz", "48361109572");

  // generate passphrase
  char* passphrase = gen_passphrase();

  // apply mutators if applicable
  if (capitalize) {
    random_caps(passphrase);
  }

  if (numbers) {
    random_numbers(passphrase);
  }
  // print passphrase to terminal
  printf("%s\n", passphrase);
  exit(0);
}
