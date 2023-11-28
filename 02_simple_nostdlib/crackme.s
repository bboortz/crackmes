; Disassembly of file: crackme.o
; Tue Nov 28 22:02:34 2023
; Type: ELF32
; Syntax: NASM
; Instruction set: Pentium


global _start: function
global __x86.get_pc_thunk.ax: function

extern _GLOBAL_OFFSET_TABLE_                            ; byte


SECTION .text   align=1 exec                            ; section number 1, code


SECTION .data   align=1 noexec                          ; section number 2, data


SECTION .bss    align=1 noexec                          ; section number 3, bss


SECTION .text._start align=1 exec                       ; section number 4, code

_start: ; Function begin
        push    ebp                                     ; 0000 _ 55
        mov     ebp, esp                                ; 0001 _ 89. E5
        sub     esp, 16                                 ; 0003 _ 83. EC, 10
        call    __x86.get_pc_thunk.ax                   ; 0006 _ E8, FFFFFFFC(rel)
        add     eax, _GLOBAL_OFFSET_TABLE_-$            ; 000B _ 05, 00000001(GOT r)
        mov     dword [ebp-9H], 829645169               ; 0010 _ C7. 45, F7, 31736171
        mov     byte [ebp-5H], 0                        ; 0017 _ C6. 45, FB, 00
        mov     dword [ebp-0EH], 846422384              ; 001B _ C7. 45, F2, 32736170
        mov     byte [ebp-0AH], 0                       ; 0022 _ C6. 45, F6, 00
        mov     dword [ebp-4H], 0                       ; 0026 _ C7. 45, FC, 00000000
        jmp     ?_002                                   ; 002D _ EB, 04

?_001:  add     dword [ebp-4H], 1                       ; 002F _ 83. 45, FC, 01
?_002:  lea     edx, [ebp-9H]                           ; 0033 _ 8D. 55, F7
        mov     eax, dword [ebp-4H]                     ; 0036 _ 8B. 45, FC
        add     eax, edx                                ; 0039 _ 01. D0
        movzx   eax, byte [eax]                         ; 003B _ 0F B6. 00
        test    al, al                                  ; 003E _ 84. C0
        jz      ?_003                                   ; 0040 _ 74, 29
        lea     edx, [ebp-0EH]                          ; 0042 _ 8D. 55, F2
        mov     eax, dword [ebp-4H]                     ; 0045 _ 8B. 45, FC
        add     eax, edx                                ; 0048 _ 01. D0
        movzx   eax, byte [eax]                         ; 004A _ 0F B6. 00
        test    al, al                                  ; 004D _ 84. C0
        jz      ?_003                                   ; 004F _ 74, 1A
        lea     edx, [ebp-9H]                           ; 0051 _ 8D. 55, F7
        mov     eax, dword [ebp-4H]                     ; 0054 _ 8B. 45, FC
        add     eax, edx                                ; 0057 _ 01. D0
        movzx   edx, byte [eax]                         ; 0059 _ 0F B6. 10
        lea     ecx, [ebp-0EH]                          ; 005C _ 8D. 4D, F2
        mov     eax, dword [ebp-4H]                     ; 005F _ 8B. 45, FC
        add     eax, ecx                                ; 0062 _ 01. C8
        movzx   eax, byte [eax]                         ; 0064 _ 0F B6. 00
        cmp     dl, al                                  ; 0067 _ 38. C2
        jz      ?_001                                   ; 0069 _ 74, C4
?_003:  lea     edx, [ebp-9H]                           ; 006B _ 8D. 55, F7
        mov     eax, dword [ebp-4H]                     ; 006E _ 8B. 45, FC
        add     eax, edx                                ; 0071 _ 01. D0
        movzx   eax, byte [eax]                         ; 0073 _ 0F B6. 00
        test    al, al                                  ; 0076 _ 84. C0
        jnz     ?_004                                   ; 0078 _ 75, 1D
        lea     edx, [ebp-0EH]                          ; 007A _ 8D. 55, F2
        mov     eax, dword [ebp-4H]                     ; 007D _ 8B. 45, FC
        add     eax, edx                                ; 0080 _ 01. D0
        movzx   eax, byte [eax]                         ; 0082 _ 0F B6. 00
        test    al, al                                  ; 0085 _ 84. C0
        jnz     ?_004                                   ; 0087 _ 75, 0E
        mov     eax, 1                                  ; 0089 _ B8, 00000001
        mov     ebx, 0                                  ; 008E _ BB, 00000000
        syscall                                         ; 0093 _ 0F 05
        jmp     ?_005                                   ; 0095 _ EB, 0D

?_004:  mov     eax, 1                                  ; 0097 _ B8, 00000001
        mov     ebx, 2                                  ; 009C _ BB, 00000002
        syscall                                         ; 00A1 _ 0F 05
        nop                                             ; 00A3 _ 90
?_005:  nop                                             ; 00A4 _ 90
        leave                                           ; 00A5 _ C9
        ret                                             ; 00A6 _ C3
; _start End of function


SECTION .text.__x86.get_pc_thunk.ax align=1 exec        ; section number 5, code

__x86.get_pc_thunk.ax:; Function begin
        mov     eax, dword [esp]                        ; 0000 _ 8B. 04 24
        ret                                             ; 0003 _ C3
; __x86.get_pc_thunk.ax End of function


SECTION .note.gnu.property align=4 noexec               ; section number 6, const

        db 04H, 00H, 00H, 00H, 18H, 00H, 00H, 00H       ; 0000 _ ........
        db 05H, 00H, 00H, 00H, 47H, 4EH, 55H, 00H       ; 0008 _ ....GNU.
        db 02H, 00H, 01H, 0C0H, 04H, 00H, 00H, 00H      ; 0010 _ ........
        db 01H, 00H, 00H, 00H, 01H, 00H, 01H, 0C0H      ; 0018 _ ........
        db 04H, 00H, 00H, 00H, 01H, 00H, 00H, 00H       ; 0020 _ ........


