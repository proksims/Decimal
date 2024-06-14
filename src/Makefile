CC = gcc
FLAGS = -Wall -Werror -Wextra 

all: clean s21_decimal.a

s21_decimal.a: 
	$(CC) $(FLAGS) -c "s21_decimal.c" "s21_decimal.h"
	ar rc s21_decimal.a s21_decimal.o
	ranlib s21_decimal.a

# for linux: -lrt -lm -lsubunit
test: clean s21_decimal.a
	$(CC) $(FLAGS) s21_decimal.c test.c -lcheck  -o test
	./test

gcov_report: 
	$(CC) --coverage test.c s21_decimal.c $(FLAGS) -lcheck -o test
	./test
	lcov -t "test" -o test.info -c -d .
	genhtml -o report test.info
	open report/index.html

clean:
	rm -rf *.o *.a *.g* *.out
	rm -rf s21_decimal
	rm -rf test.info test report

rebuild: clean all

style:
	clang-format -style=google -i ./s21_decimal.c
	clang-format -style=google -i ./s21_decimal.h
	clang-format -style=google -i ./test.c
	clang-format -style=google -n ./s21_decimal.c
	clang-format -style=google -n ./s21_decimal.h
	clang-format -style=google -n ./test.c

21: 
	$(CC) $(FLAGS) s21_decimal.c -lm -o s21_decimal
	./s21_decimal