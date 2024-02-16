#include "s21_cat.h"

int main(int argc, char *argv[]) {
  flags cat_opt = {0};
  if (cat_flags(argc, argv, &cat_opt) == -1) {
    printf("usage: cat [-benstuv] [file ...]\n");
  } else {
    for (int i = 1; i < argc; i++) {
      if (argv[i][0] != '-') output(argv[i], &cat_opt);
    }
  }
  return 0;
}

void output(char *file, flags *cat_opt) {
  FILE *f = fopen(file, "r");
  if (f != NULL) {
    int c = 0, count_str = 0, space = 0, last = 10;
    while (c != EOF) {
      c = fgetc(f);
      if (cat_opt->fl_s == 1) {
        if (c == '\n' && last == '\n') {
          space++;
        } else
          space = 0;
        if (space > 1) {
          continue;
        }
      }
      if (cat_opt->fl_b == 1) {
        if (c == '\n' && last == '\n') {
        } else {
          if (last == '\n' && c != EOF) {
            printf("%6d\t", ++count_str);
          }
        }
      }
      if (cat_opt->fl_e == 1) {
        if (c == '\n') putchar('$');
      }
      if (cat_opt->fl_n == 1) {
        if (last == '\n' && c != EOF) {
          printf("%6d\t", ++count_str);
        }
      }
      if (cat_opt->fl_t == 1) {
        if (c == '\t') {
          c = 'I';
          printf("^");
        }
      }
      if (cat_opt->fl_v == 1) {
        if (c != 9 && c != 10 && c < 32 && c != EOF) {
          c = c + 64;
          printf("^");
        } else if (c == 127) {
          c = c - 64;
          printf("^");
        }
      }
      if (c != EOF) putchar(c);
      last = c;
    }
    fclose(f);
  } else
    fprintf(stderr, "No such file or directory\n");
}

int cat_flags(int argc, char *argv[], flags *cat_opt) {
  int opt = 0, error = 0;
  static struct option long_fl[] = {{"number-nonblank", 0, NULL, 'b'},
                                    {"number", 0, NULL, 'n'},
                                    {"squeeze-blank", 0, NULL, 's'},
                                    {NULL, 0, NULL, 0}};
  while ((opt = getopt_long(argc, argv, "+beEnstTv", long_fl, NULL)) != -1) {
    switch (opt) {
      case 'b':
        cat_opt->fl_b = 1;
        break;
      case 'e':
        cat_opt->fl_e = 1;
        cat_opt->fl_v = 1;
        break;
      case 'E':
        cat_opt->fl_e = 1;
        break;
      case 'n':
        cat_opt->fl_n = 1;
        break;
      case 's':
        cat_opt->fl_s = 1;
        break;
      case 't':
        cat_opt->fl_t = 1;
        cat_opt->fl_v = 1;
        break;
      case 'T':
        cat_opt->fl_t = 1;
        break;
      case 'v':
        cat_opt->fl_v = 1;
        break;
      default:
        error = -1;
        break;
    }
    if (cat_opt->fl_b) cat_opt->fl_n = 0;
  }
  return error;
}
