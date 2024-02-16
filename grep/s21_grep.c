#include "s21_grep.h"

int main(int argc, char *argv[]) {
  char *pattern = NULL;
  flags grep_opt = {0};
  int flag_count = 0;
  grep_flags(argc, argv, &grep_opt, &flag_count);
  pattern = grep_opt.pattern;

  if (pattern == NULL) {
    fprintf(stderr,
            "Usage: %s -e pattern [-i] [-v] [-c] [-l] [-n] [-s] [-h] [-o] "
            "filename\n",
            argv[0]);
    exit(EXIT_FAILURE);
  }

  output(argc, argv, flag_count, grep_opt);
  return 0;
}
void output(int argc, char *argv[], int flag_count, flags grep_opt) {
  int line_number = 0, match_count = 0;
  char line[MAX_LINE_LENGTH], *match = NULL, *filename = NULL;
  FILE *fp = NULL;
  int reti = 0;
  for (int i = flag_count + 1; i < argc; i++) {
    filename = argv[i];
    fp = fopen(filename, "r");
    regex_t reg;
    if (fp == NULL || grep_opt.fl_e > 1) {
      if (!grep_opt.fl_s) {
        fprintf(stderr, "Error opening file: %s\n", filename);
        exit(EXIT_FAILURE);
      }
    }
    reti = regcomp(&reg, grep_opt.pattern,
                   grep_opt.fl_i ? REG_ICASE : REG_EXTENDED);
    while (fgets(line, MAX_LINE_LENGTH, fp) != NULL) {
      line_number++;
      reti = regexec(&reg, line, 0, NULL, 0);
      if (!reti && !grep_opt.fl_v) {
        match_count++;
        if (!grep_opt.fl_c) {
          if (grep_opt.fl_l == 1 && match_count == 1) {
            printf("%s\n", filename);
            break;
          }
          if (grep_opt.fl_n == 1) {
            printf("%d:", line_number);
          }
          if (grep_opt.fl_o == 1) {
            printf("%s", match);
          } else {
            if (argc - flag_count <= 2) {
              printf("%s", line);
            } else {
              if (grep_opt.fl_n) {
                printf("%s:%d:%s", filename, line_number, line);
              } else {
                printf("%s:%s", filename, line);
              }
            }
          }
        }
      }
      if (reti) {
        if (grep_opt.fl_v) {
          if (grep_opt.fl_n == 1) {
            printf("%d:", line_number);
          }
          printf("%s", line);
          if (line[strlen(line) - 1] != '\n') printf("\n");
        }
      }
    }
    if (grep_opt.fl_c) {
      if (argc - flag_count <= 2) {
        printf("%d\n", match_count);
      } else {
        printf("%s:%d\n", filename, match_count);
      }
    }
    match_count = 0;
    line_number = 0;
    regfree(&reg);
    fclose(fp);
  }
}

void grep_flags(int argc, char *argv[], flags *grep_opt, int *flag_count) {
  int opt = 0;
  while ((opt = getopt(argc, argv, "eivclnosh")) != -1) {
    switch (opt) {
      case 'e':
        grep_opt->fl_e += 1;
        break;
      case 'i':
        grep_opt->fl_i += 1;
        break;
      case 'v':
        grep_opt->fl_v += 1;
        break;
      case 'c':
        grep_opt->fl_c += 1;
        break;
      case 'l':
        grep_opt->fl_l += 1;
        break;
      case 'n':
        grep_opt->fl_n += 1;
        break;
      case 's':
        grep_opt->fl_s += 1;
        break;
      case 'h':
        grep_opt->fl_h += 1;
        break;
      case 'o':
        grep_opt->fl_o += 1;
        break;
      default:
        fprintf(stderr, "Unknown option\n");
        exit(EXIT_FAILURE);
    }
  }
  grep_opt->pattern = argv[optind];
  *flag_count = optind;
}
