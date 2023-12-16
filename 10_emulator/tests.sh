#!/bin/bash
#

set -e
set -u

./output/test_scanner < <( echo "mov a, b")
./output/test_lexer
./output/test_parser
./output/test < <( echo "mov a, b")
./output/test < <( echo "mov a, 1111111111111111111111")
./output/test < <( echo "MOV abc, abcdeabcdeabcdeabcde")
./output/test < <(  cat tests_files/complex.s | ./tests_include/radamsa/bin/radamsa -n 1 )
./output/test < <(  cat tests_files/regression.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind ./output/test < <(  cat tests_files/*.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind --leak-check=full --show-leak-kinds=all ./output/crackme < <( ./tests_include/radamsa/bin/radamsa -n 5 tests_files/* )
