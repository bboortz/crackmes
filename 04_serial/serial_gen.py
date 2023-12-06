#!/usr/bin/env python


def gen_serial_block1():
    MIN = 1
    MAX = 36
    a = MIN
    b = MIN
    c = MIN
    d = MIN

    while (a <= MAX):
        print(a)
        b = 0
        while (b <= MAX):
            c = 0
            while (c <= MAX):
                d = 0
                while (d <= MAX):
                    add = a + b + c + d
                    mul = a * b * c * d
                    if add == mul:
                        print("found: %d == %d (%d, %d, %d, %d)" % (add, mul, a, b, c, d) )
#                    else:
#                        print("not found: %d != %d (%d, %d, %d, %d)" % (add, mul, a, b, c, d) )
                    d += 1
                c += 1
            b += 1
        a += 1



def gen_serial_block2():
    MIN = 1
    MAX = 36
    a = MIN
    b = MIN
    c = MIN
    d = MIN

    while (a <= MAX):
        print(a)
        b = 0
        while (b <= MAX):
            c = 0
            while (c <= MAX):
                d = 0
                while (d <= MAX):
                    add = a + b + c + d
                    mul = (a + b) * (c + d)
                    if add == mul:
                        print("found: %d == %d (%d, %d, %d, %d)" % (add, mul, a, b, c, d) )
#                    else:
#                        print("not found: %d != %d (%d, %d, %d, %d)" % (add, mul, a, b, c, d) )
                    d += 1
                c += 1
            b += 1
        a += 1


gen_serial_block1()
gen_serial_block2()
