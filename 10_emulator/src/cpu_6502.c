#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#include "cpu_6502.h"
#include "cpu.h"
#include "cbase_conv.h"
#include "ccharp.h"
#include "cheap.h"
#include "interpreter.h"
#include "lexer.h"
#include "parser.h"



cpu_6502 cpu_6502_create() {
    cpu_6502 cpu = {0};

    cpu_6502_reset(&cpu);

    return cpu;
}


int cpu_6502_destroy(cpu_6502* cpu) {
    return cpu_6502_reset(cpu);
}




int cpu_6502_reset(cpu_6502* cpu) {
    cpu->type = CPU_TYPE_6502;
    cpu->ip = 0xFFFC;
    cpu->sp = 0x0100;
    cpu->reg_a = 0;
    cpu->reg_x = 0;
    cpu->reg_y = 0;
    cpu->ps = 0;

    for(int i = 0; i < CPU_6502_MAX_MEM; i++) {
        cpu->mem.data[i] = 0;
    }

    return RET_SUCCESS;
}



// Function to access memory at a specific address
unsigned char* cpu_6502_get_mem(cpu_6502_mem* mem, uint16_t address) {
    return &(mem->data[address]);
}

// Function to access memory at a specific address
unsigned char* cpu_6502_get_mem_zero_page(cpu_6502_mem* mem, uint16_t address, error* err) {
    if (address > CPU_6502_MEM_ZERO_PAGE_MAX) {
        // Handle out-of-bounds memory access here
        char *err_msg;
        char err_addr[2];
        err_addr[0] = address;
        err_addr[1] = '\0';
        char *str1 = "Memory address out of bounds";
        if (RET_ERR == error_create_message(&err_msg, str1, err_addr, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Address has exceeded the memory");
        return NULL;
    }
    
    return &(mem->data[address]);
}

// Function to access memory at a specific address
unsigned char* cpu_6502_get_mem_stack(cpu_6502_mem* mem, uint16_t address, error* err) {
    if (address < CPU_6502_MEM_STACK_MIN || address > CPU_6502_MEM_STACK_MAX) {
        // Handle out-of-bounds memory access here
        char *err_msg;
        char err_addr[2];
        err_addr[0] = address;
        err_addr[1] = '\0';
        char *str1 = "Memory address out of bounds";
        if (RET_ERR == error_create_message(&err_msg, str1, err_addr, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Address has exceeded the memory");
        return NULL;
    }
    
    return &(mem->data[address]);
}

// Function to access memory at a specific address
unsigned char* cpu_6502_get_mem_normal(cpu_6502_mem* mem, uint16_t address, error* err) {
    if (address < CPU_6502_MEM_NORMAL_MIN || address > CPU_6502_MEM_NORMAL_MAX) {
        // Handle out-of-bounds memory access here
        char *err_msg;
        char err_addr[2];
        err_addr[0] = address;
        err_addr[1] = '\0';
        char *str1 = "Memory address out of bounds";
        if (RET_ERR == error_create_message(&err_msg, str1, err_addr, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Address has exceeded the memory");
        return NULL;
    }
    
    return &(mem->data[address]);
}

// Function to access memory at a specific address
unsigned char* cpu_6502_get_mem_reserved(cpu_6502_mem* mem, uint16_t address, error* err) {
    if (address < CPU_6502_MEM_RESERVED_MIN) {
        // Handle out-of-bounds memory access here
        char *err_msg;
        char err_addr[2];
        err_addr[0] = address;
        err_addr[1] = '\0';
        char *str1 = "Memory address out of bounds";
        if (RET_ERR == error_create_message(&err_msg, str1, err_addr, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Address has exceeded the memory");
        return NULL;
    }
    
    return &(mem->data[address]);
}

void cpu_6502_print_state(cpu_6502* cpu, error* err) {
    char* ps_binary = cbase_conv_get_binary_from_charp(cpu->ps, err);
    printf("\n Registers |    IP |    SP |   A |   X |   Y | PS: NO-BDIZC       |\n");
    printf("           | %5d | %5d | %3d | %3d | %3d |     %8s (%3d) | \n", cpu->ip, cpu->sp, cpu->reg_a, cpu->reg_x, cpu->reg_y, ps_binary, cpu->ps);
    printf(" MEM       |   .................................................  |\n");
//    printf("\n *** CPU { ip: %5d, reg_a: %3d, reg_x: %3d, reg_y: %3d, ps: %8s (%3d) } \n", cpu->ip, cpu->reg_a, cpu->reg_x, cpu->reg_y, ps_binary, cpu->ps);
    free(ps_binary);
}




void cpu_6502_set_status_flag(cpu_6502* cpu, char flag, uint8_t bit, error* err) {
    char *err_msg;
    char err_flag[2];

    switch (flag) {
        case 'C': // carry flag
            cbase_conv_set_bit(&cpu->ps, 0, bit, err);
            return;

        case 'Z':  // zero flag
            cbase_conv_set_bit(&cpu->ps, 1, bit, err);
            return;

        case 'I': // interrupt disable flag
            cbase_conv_set_bit(&cpu->ps, 2, bit, err);
            return;
        
        case 'D': // decimal mode flag
            cbase_conv_set_bit(&cpu->ps, 3, bit, err);
            return;

        case 'B': // break command flag
            cbase_conv_set_bit(&cpu->ps, 4, bit, err);
            return;

        case 'V': // overflow flag
            cbase_conv_set_bit(&cpu->ps, 6, bit, err);
            return;

        case 'N': // negative flag
            cbase_conv_set_bit(&cpu->ps, 7, bit, err);
            return;

        default:
            err_flag[0] = flag;
            err_flag[1] = '\0';
            char *str1 = "unknown status flag";
            if (RET_ERR == error_create_message(&err_msg, str1, err_flag, err) ) {
                *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
            }
            *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Flag must be one of this: [CZIDBVN].");
            return;
    }
}


int cpu_6502_get_status_flag(cpu_6502* cpu, char flag, error* err) {
    char *err_msg = "";
    char err_flag[2];

    switch (flag) {
        case 'C': // carry flag
            return cbase_conv_get_bit(cpu->ps, 0, err);

        case 'Z':  // zero flag
            return cbase_conv_get_bit(cpu->ps, 1, err);

        case 'I': // interrupt disable flag
            return cbase_conv_get_bit(cpu->ps, 2, err);
        
        case 'D': // decimal mode flag
            return cbase_conv_get_bit(cpu->ps, 3, err);

        case 'B': // break command flag
            return cbase_conv_get_bit(cpu->ps, 4, err);

        case 'V': // overflow flag
            return cbase_conv_get_bit(cpu->ps, 6, err);

        case 'N': // negative flag
            return cbase_conv_get_bit(cpu->ps, 7, err);

        default:
            err_flag[0] = flag;
            err_flag[1] = '\0';
            char *str1 = "unknown status flag";
            if (RET_ERR == error_create_message(&err_msg, str1, err_flag, err) ) {
                *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
            }
            *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "Flag must be one of this: [CZIDBVN].");
            return 0;
    }
}





int cpu_6502_interpret_instruction_nop(parser_cst_node node, error* err) {
     if (0 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction LDA needs 0 parameter", "wrong number of parameters.");
    }

    return RET_SUCCESS;
}


int cpu_6502_interpret_instruction_lda(parser_cst_node node, cpu_6502* cpu, error* err) {
     if (1 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction LDA needs 1 parameter", "wrong number of parameters.");
    }

    int number = 0;
    if (RET_ERR == ccharp_string_to_int(&number, node.children[0].value) ) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
    }
    cpu->reg_a = number;

    if (0 == cpu->reg_a) cpu_6502_set_status_flag(cpu, 'Z', 1, err);
    if (1 == cbase_conv_get_bit(cpu->reg_a, 7, err) ) cpu_6502_set_status_flag(cpu, 'N', 1, err);

    return RET_SUCCESS;
}

int cpu_6502_interpret_instruction_ldx(parser_cst_node node, cpu_6502* cpu, error* err) {
    if (1 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction LDA needs 1 parameter", "wrong number of parameters.");
    }

    int number = 0;
    if (RET_ERR == ccharp_string_to_int(&number, node.children[0].value) ) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
    }
    cpu->reg_x = number;

    if (0 == cpu->reg_a) cpu_6502_set_status_flag(cpu, 'Z', 1, err);
    if (1 == cbase_conv_get_bit(cpu->reg_a, 7, err) ) cpu_6502_set_status_flag(cpu, 'N', 1, err);

    return RET_SUCCESS;
}

int cpu_6502_interpret_instruction_ldy(parser_cst_node node, cpu_6502* cpu, error* err) {
    if (1 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction LDA needs 1 parameter", "wrong number of parameters.");
    }

    int number = 0;
    if (RET_ERR == ccharp_string_to_int(&number, node.children[0].value) ) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
    }
    cpu->reg_y = number;

    if (0 == cpu->reg_a) cpu_6502_set_status_flag(cpu, 'Z', 1, err);
    if (1 == cbase_conv_get_bit(cpu->reg_a, 7, err) ) cpu_6502_set_status_flag(cpu, 'N', 1, err);

    return RET_SUCCESS;
}



int cpu_6502_interpret_instruction(parser_cst_node node, cpu_6502* cpu, error* err) {
    //parser_print_cst_node(node);
    //error_print(*err);
    
    ccharp_toupper_string(node.value);
    char *instruction = node.value;
    size_t instruction_len = strlen(instruction);

    printf("Instruction: %s\n", instruction);
    if (strncmp(instruction, "NOP", instruction_len) == 0) {
        cpu_6502_interpret_instruction_nop(node, err);
    
    } else if (strncmp(instruction, "LDA", instruction_len) == 0) {
        cpu_6502_interpret_instruction_lda(node, cpu, err);

    } else if (strncmp(instruction, "LDX", instruction_len) == 0) {
        cpu_6502_interpret_instruction_ldx(node, cpu, err);

    } else if (strncmp(instruction, "LDY", instruction_len) == 0) {
        cpu_6502_interpret_instruction_ldy(node, cpu, err);

    } else {
        char *err_msg = "";
        char *str1 = "unknown instruction";
        if (RET_ERR == error_create_message(&err_msg, str1, instruction, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, err_msg, "character instruction. please verify your input.");
        return RET_ERR;
    }

    cpu->ip++;

    return RET_SUCCESS;
}



// Get the next token from input
lexer_token cpu_6502_lexer_next_token(char *input, int *line, int *pos, error* err) {
    lexer_token token = lexer_create_token(err);
    
    int l = *line;
    int p = *pos;
    size_t length = strlen(input);
    token.line = l;
    token.pos = p;

    //printf("# %d - %ld - <%s>\n", p, length, input);

    // Check for newline
    if ('\n' == input[p] ) {
        //printf("newline\n");
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        l++;
        token.type = TOKEN_NEWLINE;
        *err = error_create_default();

        *line = l;
        *pos = p;
        return token;
    }

    // Skip whitespace
    while (p < (int) length && isspace(input[p])) {
        token.pos++;
        p++;
    }

    //printf("# %d - %ld - <%s>\n", p, length, input);

    // Check for end of input
    if (p == (int) length) {
        token.type = TOKEN_END_OF_INPUT;
        *err = error_create_default();
    
    // Check for comma (,)
    } else if (',' == input[p]) {
        //printf("-# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        token.type = TOKEN_COMMA;
        *err = error_create_default();
    
    // Check for literal
    } else if (isalpha(input[p])) {
        //printf("## %d\n", *pos);

        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring_as_long_as_char(&token.value, input, err);
        token.type = TOKEN_LITERAL;
        *err = error_create_default();

/*
        int j = 0;
        // TODO replace copy method!
        //char* token_str = (char*) heap_calloc(1, sizeof(char), err);
        //char token_str[MAX_TOKEN_VALUE];
        //if (NULL == token_str) {
        //    *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "Cannot allocate memory", "unclear, probably a programming mistake or unsifficient memory.");
        //}
        
        
        while (p < (int) length && isalpha(input[p])) {
            if (j >= MAX_TOKEN_VALUE) {
                *err = error_create(ERR_BOUNDARY, ERR_CRIT_ERROR, "too much input", "more input that internal data structure can handle.");
                if (RET_ERR == error_check(*err) ) {
                   break;
                }
            }
            // TODO replace char to string method
            
            //char char_string[2]; // Reserve space for character + null terminator
            //char_string[0] = input[p];
            //char_string[1] = '\0';
            //util_concat_strings(&token_str, token_str, char_string, err);
            //j++;
            //p++;
            token.value[j++] = input[p++];
            
        }
        token.value[j] = '\0';

        // token.value = token_str;
        //heap_free(token_str, err);
        */
        //p += 2;
        // l += p;
        //*pos = p;
        
        //token.type = TOKEN_STRING;

    // Check for numerical operands
    } else if (isdigit(input[p])) {
        //printf("## %d\n", *pos);

        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring_as_long_as_digit(&token.value, input, err);
        token.type = TOKEN_NUMBER;
        *err = error_create_default();

        /*
        int j = 0;
        // TODO replace copy method!
        while (j < MAX_TOKEN_VALUE && p < (int) length && isdigit(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_NUMBER;
        */

    // Check for numerical operands
    } else if ('#' == input[p] ) {
        printf("## %d\n", *pos);

        heap_free(token.value, err);
        p++;   // skipping the character #
        input += p;
        
        p += ccharp_copy_substring_as_long_as_digit(&token.value, input, err);
        token.type = TOKEN_NUMBER;
        *err = error_create_default();

        /*
        int j = 0;
        // TODO replace copy method!
        while (j < MAX_TOKEN_VALUE && p < (int) length && isdigit(input[p])) {
            token.value[j++] = input[p++];
        }
        token.value[j] = '\0';
        token.type = TOKEN_NUMBER;
        */

    // unknown
    } else {
        //printf("# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        
        heap_free(token.value, err);
        input += p;
        p += ccharp_copy_substring(&token.value, input, 0, 1, err);
        token.type = TOKEN_UNKNOWN;
        //printf("# %d - %ld - <%s> - <%s>\n", p, length, input, token.value);
        
        char *err_msg;
        char *str1 = "unknown character";
        if (RET_ERR == error_create_message(&err_msg, str1, token.value, err) ) {
            *err = error_create(ERR_INTERNAL, ERR_CRIT_SEVERE, "cannot cancatinate two strings", "unclear, probably a programming mistake or unsifficient memory.");
        }
        *err = error_create(ERR_LEXER, ERR_CRIT_WARN, err_msg, "character unknown. please verify your input.");
        heap_free(err_msg, err);
        //heap_free(err_msg, err);
        // util_print_error(*err);
        /* TODO think about it, if we are returning directly here or later
        if (RET_ERR == error_check(*err) ) {
            return 
        }
        */

    }

    *pos = p;
    *line = l;
    
    return token;
}


/*
int cpu_6502_interpret_instruction_mov(parser_cst_node node, cpu_6502* cpu, error* err) {
    // printf("MOV instruction\n");
    //parser_print_cst_node(node);
    //error_print(*err);

    if (2 != node.num_children) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "instruction MOV needs 2 parameter", "wrong number of parameters.");
    }

    int number = 0;
    //printf("-> %s\n", node.children[1].value);
    if (RET_ERR == ccharp_string_to_int(&number, node.children[1].value) ) {
        *err = error_create(ERR_LEXER, ERR_CRIT_ERROR, "conversion error of the number", "string is not a number");
    }
    cpu->reg_a = number; // atoi(node.children[2].value);

    return RET_SUCCESS;
}
*/