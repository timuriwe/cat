#include "my_cat.h"

#include <errno.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char* argv[]) {
  flag_t flags;
  set_flags(&flags);
  int* file_paths = calloc(argc, sizeof(int));
  if (file_paths == NULL) {
    fprintf(stderr, "my_cat: %s\n", strerror(errno));
    exit(errno);
  }
  read_arguments(argc, argv, &flags, file_paths);
  print(argc, argv, &flags, file_paths);
  free(file_paths);
  return 0;
}

void print(int argc, char* argv[], flag_t* flags, int* file_paths) {
  for (int i = 1; i < argc; i++) {
    if (file_paths[i]) {
      print_file(argv[i], flags);
    }
  }
}

void print_file(char* path, flag_t* flags) {
  FILE* file;
  file = fopen(path, "r");

  if (file != NULL) {
    char symbol = getc(file);

    if (symbol != EOF) {
      if (flags->n) {
        printf("%6d\t", ++flags->count_of_lines);
      }
      if (flags->b) {
        if (symbol != '\n') {
          printf("%6d\t", ++flags->count_of_lines);
        } else {
          printf("      \t");
        }
      }
    }

    while (symbol != EOF) {
      char next_symbol = getc(file);
      if (symbol == '\n') {
        if (flags->e) {
          putchar('$');
        }
        putchar(symbol);
        if (flags->s) {
          if (next_symbol == '\n') {
            while (next_symbol == '\n') {
              next_symbol = getc(file);
            }
            fseek(file, -2, SEEK_CUR);
            next_symbol = getc(file);
          }
        }
        if ((flags->n) && (next_symbol != EOF)) {
          printf("%6d\t", ++flags->count_of_lines);
        }
        if ((flags->b) && (next_symbol != EOF)) {
          if (next_symbol != '\n') {
            printf("%6d\t", ++flags->count_of_lines);
          }
        }
      } else {
        print_symbol(symbol, flags);
      }
      symbol = next_symbol;
    }
    fclose(file);
  } else {
    fprintf(stderr, "my_cat: %s: %s\n", path, strerror(errno));
  }
}

void print_symbol(char symbol, flag_t* flags) {
  if (symbol < 32 || symbol == 127) {
    if (symbol == '\t') {
      if (flags->t) {
        printf("^I");
      } else {
        putchar('\t');
      }
    } else if (flags->v) {
      if (symbol < 0) {
        printf("M-");
        print_symbol(symbol + 128, flags);
      } else {
        printf("^%c", (symbol + 64) % 128);
      }
    } else {
      putchar(symbol);
    }
  } else {
    putchar(symbol);
  }
}

void read_arguments(int argc, char* argv[], flag_t* flags, int* file_paths) {
  for (int i = 1; i < argc; i++) {
    if (argv[i][0] == '-') {
      read_flags(argv[i], flags);
    } else {
      file_paths[i] = 1;
    }
  }
}

void read_flags(char* str, flag_t* flags) {
  str++;
  int read_end = 0;
  while (read_end == 0) {
    if (*str == '-') {
      if (strcmp(str, "-number-nonblank") == 0) {
        flags->b = 1;
        flags->n = 0;
        read_end = 1;
      } else if (strcmp(str, "-number") == 0) {
        if (flags->b == 0) {
          flags->n = 1;
        }
        read_end = 1;
      } else if (strcmp(str, "-squeeze-blank") == 0) {
        flags->s = 1;
        read_end = 1;
      } else {
        fprintf(stderr, "my_cat: unrecognized option '-%s'\n", str);
        exit(1);
      }
    } else if (*str == 'v') {
      flags->v = 1;
    } else if (*str == 'b') {
      flags->b = 1;
      flags->n = 0;
    } else if (*str == 'E') {
      flags->e = 1;
    } else if (*str == 'e') {
      flags->e = 1;
      flags->v = 1;
    } else if (*str == 'n') {
      if (flags->b == 0) {
        flags->n = 1;
      }
    } else if (*str == 's') {
      flags->s = 1;
    } else if (*str == 'T') {
      flags->t = 1;
    } else if (*str == 't') {
      flags->t = 1;
      flags->v = 1;
    } else if (*str == '\0') {
      read_end = 1;
    } else {
      fprintf(stderr, "my_cat: invalid option -- '%c'\n", *str);
      exit(1);
    }
    str++;
  }
}

void set_flags(flag_t* flags) {
  flags->v = 0;
  flags->b = 0;
  flags->e = 0;
  flags->n = 0;
  flags->s = 0;
  flags->t = 0;
  flags->count_of_lines = 0;
}
