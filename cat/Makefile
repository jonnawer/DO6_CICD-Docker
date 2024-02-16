CC=gcc
CFLAGS=-g -Wall -Werror -Wextra
SOURCES=s21_cat.c


s21_cat:
	$(CC) $(CFLAGS) $(SOURCES) -o s21_cat
clang:
	clang-format -n *.c *.h

test:
	bash test_func_cat_GNU.sh

s21_cat.o: s21_cat.c s21_cat.h

cat21: clean s21_cat

clean:
	rm -rf *.o s21_cat
