#ifndef S21_GREP_H
#define S21_GREP_H

#include <getopt.h>
#include <regex.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_LINE_LENGTH 1024

typedef struct {
  int fl_e;  //шаблон
  int fl_i;  //игнорирование регистра
  int fl_v;  //инвертация поиска соответствий
  int fl_c;  //вывод количества совпадающих файлов
  int fl_l;  //вывод совпадающих файлов
  int fl_n;  //Предваряет каждую строку вывода номером строки из файла ввода
  int fl_s;  //подавление ошибки
  int fl_h;  //совпадающие строки с именами файлов
  int fl_o;  //совпадающие части строки
  char *pattern;
} flags;

void output(int argc, char *argv[], int flag_count, flags grep_opt);
void grep_flags(int argc, char *argv[], flags *grep_opt, int *flag_count);

#endif
