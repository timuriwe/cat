#ifndef SRC_CAT_S21_CAT_H_
#define SRC_CAT_S21_CAT_H_

struct cat_flag_type {
  int v;
  int b;
  int e;
  int n;
  int s;
  int t;
  int count_of_lines;
};

typedef struct cat_flag_type flag_t;

void set_flags(flag_t* flags);
void read_arguments(int argc, char* argv[], flag_t* flags, int* fpath);
void read_flags(char* str, flag_t* flags);
void print(int argc, char* argv[], flag_t* flags, int* file_paths);
void print_file(char* path, flag_t* flags);
void print_symbol(char symbol, flag_t* flags);

#endif  // SRC_CAT_S21_CAT_H_
