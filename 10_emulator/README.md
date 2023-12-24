# build
```
make clean all
```

# task
* Let the crackme print "Correct password!"

# solution
* the solution can be found in SOLUTION.md

# Architecture

Tier #  |
1       | representation   | scanner, lexer, parser, interpreter
2       | machine          | register, stack, heap
3       | core             | error, heap, stack, string

## Upper Architecture
Main    --> Scanner
            --> Lexer
            --> Parser
            --> Interpreter

## Bottom Architecture

error
heap
stack
string


        

# Ref
* https://sta.c64.org/cbm64mem.html
* http://www.6502.org/users/obelisk/
* https://www.c64-wiki.com/wiki/Assembler
* 


# Memory

==4118266== 
==4118266== HEAP SUMMARY:
==4118266==     in use at exit: 7,818 bytes in 706 blocks
==4118266==   total heap usage: 1,090 allocs, 384 frees, 369,845 bytes allocated
==4118266== 
==4118266== LEAK SUMMARY:
==4118266==    definitely lost: 5,821 bytes in 501 blocks
==4118266==    indirectly lost: 216 bytes in 200 blocks
==4118266==      possibly lost: 0 bytes in 0 blocks
==4118266==    still reachable: 1,781 bytes in 5 blocks
==4118266==         suppressed: 0 bytes in 0 blocks
==4118266== Rerun with --leak-check=full to see details of leaked memory
==4118266== 
==4118266== Use --track-origins=yes to see where uninitialised values come from
==4118266== For lists of detected and suppressed errors, rerun with: -s
==4118266== ERROR SUMMARY: 35221 errors from 51 contexts (suppressed: 0 from 0)


==4118416== 
==4118416== HEAP SUMMARY:
==4118416==     in use at exit: 7,734 bytes in 661 blocks
==4118416==   total heap usage: 1,135 allocs, 474 frees, 409,040 bytes allocated
==4118416== 
==4118416== LEAK SUMMARY:
==4118416==    definitely lost: 5,737 bytes in 456 blocks
==4118416==    indirectly lost: 216 bytes in 200 blocks
==4118416==      possibly lost: 0 bytes in 0 blocks
==4118416==    still reachable: 1,781 bytes in 5 blocks
==4118416==         suppressed: 0 bytes in 0 blocks
==4118416== Rerun with --leak-check=full to see details of leaked memory
==4118416== 
==4118416== Use --track-origins=yes to see where uninitialised values come from
==4118416== For lists of detected and suppressed errors, rerun with: -s
==4118416== ERROR SUMMARY: 41631 errors from 58 contexts (suppressed: 0 from 0)