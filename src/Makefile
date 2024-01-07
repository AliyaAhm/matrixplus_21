LIBRARY_NAME = s21_matrix_oop.a
CC = gcc
SRC_FILES = s21_matrix.cc
HEADER = s21_matrix_oop.h
OBJ_FILES = $(SRC_FILES:%.cc=%.o)
OS = $(shell uname)

ifeq ($(OS), Linux)
	CFLAGS = -g -std=c++17 -lstdc++ -pedantic -Wall -Wextra -Werror
	CHECK_FLAGS =  -lgtest -lstdc++ -pthread 
	MEM_CHECK = valgrind -s --tool=memcheck --trace-children=yes --leak-check=yes --leak-check=full -s
	GCOV = lcov -t test_unit.out -o s21_matrix_tests.info -c -d .
else
	CFLAGS = -g -lstdc++ -std=c++17 -pedantic -Wall -Wextra -Werror
	CHECK_FLAGS = -lgtest
	MEM_CHECK = CK_FORK=no leaks --atExit -- ./test_unit.out
	GCOV = lcov -t test_unit.out -o s21_matrix_tests.info -c -d . --ignore-errors mismatch
endif


.PHONY: all clean check_style test gcov_report

all: $(LIBRARY_NAME)

$(LIBRARY_NAME) : 
	$(CC) $(CFLAGS) -c $(SRC_FILES)
	ar rcs $(LIBRARY_NAME) s21_matrix.o
	ranlib $(LIBRARY_NAME)
clean:
	rm -rf *.a *.o *.so *.gcda *.gcno *.gch *.info *.html *.css test *.txt test.info test.dSYM *.out report
	
test: clean $(LIBRARY_NAME)
	$(CC) $(CFLAGS) test_matrix.cc $(LIBRARY_NAME) $(CHECK_FLAGS) -o test_unit.out     
	./test_unit.out
	
leaks: test
	$(MEM_CHECK) ./test_unit.out

gcov_report: all
	$(CC) $(CFLAGS) --coverage test_matrix.cc $(SRC_FILES) $(CHECK_FLAGS) -o gсov_report.o
	./gсov_report.o 
	$(GCOV)
	genhtml -o report s21_matrix_tests.info
	rm -f *.gcno *.gcda *.info gсov_report.o *.gcov

check_style:
	clang-format -n -style=Google s21_matrix_oop.h s21_matrix.cc test_matrix.cc