#!/bin/bash
#

set -e
set -u

./output/test_utils
./output/test_scanner < <( echo "mov a, b")
./output/test_lexer
./output/test_parser
./output/test < <( echo "mov a, b")
./output/test < <( echo "mov a, 1111111111111111111111")
./output/test < <( echo "MOV abc, abcdeabcdeabcdeabcde")


./output/test < <(  cat tests_files/complex.s | ./tests_include/radamsa/bin/radamsa -n 1 | egrep -v '[^[:print:]]' | perl -pe 's/[^\x00-x20\x30-\x39\x41-\x5A\x60-\x7A]+/a/g' )
exit 
./output/test < <(  cat tests_files/regression.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind ./output/test < <(  cat tests_files/*.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind --leak-check=full --show-leak-kinds=all ./output/crackme < <( ./tests_include/radamsa/bin/radamsa -n 5 tests_files/* )
