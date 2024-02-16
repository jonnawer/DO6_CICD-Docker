CC=gcc
CFLAGS=-g -Wall -Werror -Wextra
SOURCES=s21_grep.c


s21_cat:
	$(CC) $(CFLAGS) $(SOURCES) -o s21_grep

clang:
	@clang-format -style=Google -dump-config > .clang-format
	clang-format -n *.c *.h

test:
	bash test_func_grep_GNU.sh

s21_cat.o: s21_grep.c s21_grep.h

cat21: clean s21_grep

clean:
	rm -rf *.o s21_grep