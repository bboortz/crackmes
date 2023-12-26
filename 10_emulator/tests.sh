#!/bin/bash
#

set -e
set -u

./output/test_scanner < <( echo "lda 1")
./output/test_lexer
./output/test_parser
./output/test_interpreter
./output/test_cpu_6502

./output/test < <( echo "lda 1")
./output/test < <( echo "lda 2")
./output/test < <( echo "lda 5")


exit 
./output/test < <(  cat tests_files/complex.s | ./tests_include/radamsa/bin/radamsa -n 1 | egrep -v '[^[:print:]]' | perl -pe 's/[^\x00-x20\x30-\x39\x41-\x5A\x60-\x7A]+/a/g' )
./output/test < <(  cat tests_files/regression.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind ./output/test < <(  cat tests_files/*.s | ./tests_include/radamsa/bin/radamsa -n 1 )
valgrind --leak-check=full --show-leak-kinds=all ./output/crackme < <( ./tests_include/radamsa/bin/radamsa -n 5 tests_files/* )
