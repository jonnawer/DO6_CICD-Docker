#ifndef S21_CAT_H
#define S21_CAT_H

#include <getopt.h>
#include <stdio.h>

typedef struct {
  int fl_b;  //нумерация непустых строки
  int fl_e;  // v + отображение символов конца строки как $
  int fl_n;  //нумеруция все выходные строки
  int fl_s;  //сжимает несколько смежных пустых строк
  int fl_t;  // v + также отображение табов ^I
  int fl_v;  //все непечатные символы кроме -e -b
} flags;

void output(char *file, flags *cat_opt);
int cat_flags(int argc, char *argv[], flags *cat_opt);

#endif
