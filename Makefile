SHELL = /bin/sh

CC = gcc
CFLAGS = -Wall -Werror -Wextra -g -std=c++17 
LFLAGS = -lpthread -lgtest -pthread 
GFLAGS = -fprofile-arcs -ftest-coverage

EXE_NAME = tests

LIB_SRC = $(wildcard lib/*.tpp lib/**/*.tpp)
TEST_SRC = $(wildcard test/*.cpp)

GCOV_NAME = gcov_tests.info

.PHONY: all clean style_check style_fix test gcov_report rebuild valgrind_test

all: clean test

test:
	@rm -f $(EXE_NAME)
	@$(CC) $(CFLAGS) $(TEST_SRC) -o $(EXE_NAME) $(LFLAGS) -lstdc++ -lm
	@./$(EXE_NAME)

gcov_report: clean
	@$(CC) $(CFLAGS) $(TEST_SRC) -o $(EXE_NAME) --coverage $(LFLAGS) $(GFLAGS)
	./$(EXE_NAME)
	@lcov -t "gcov_tests" -o $(GCOV_NAME) -c -d . \
		--exclude '/usr/include/c++/11/*' \
		--exclude '/usr/include/c++/11/bits/*' \
		--exclude '/usr/include/c++/11/ext/*' \
		--exclude '/usr/include/gtest/*' \
		--exclude '/usr/include/gtest/internal/*'
	genhtml -o report $(GCOV_NAME)
	@rm -rf *.gcno *.gcda *.gcov $(GCOV_NAME) *.o

clean:
	@rm -f $(EXE_NAME) *.o .clang-format
	@rm -rf ./lib/*.o ./lib/**/*.o ./test/*.o *.gcno *.gcda ./report
	@rm -rf $(EXE_NAME)

style_check:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -Werror -n test/*.cpp test/*.h lib/**/*.tpp lib/**/*.h *.h lib/*.tpp lib/*.h
	@rm -rf .clang-format

style_fix:
	@cp ../materials/linters/.clang-format .clang-format
	clang-format -i test/*.cpp test/*.h lib/**/*.tpp lib/**/*.h *.h
	@rm -rf .clang-format

rebuild: clean test

valgrind_test: rebuild
	valgrind --tool=memcheck --leak-check=yes --show-leak-kinds=all --track-origins=yes -s ./$(EXE_NAME)