/******************************************************
 * instructions.h - instruction definitions
 * created 150211 jonathan howard (j@hovverd.com)
 ******************************************************/

#pragma once

#include <cstdio>
#define BUFFER_OFFSET(i) ((char*)NULL+(i))

typedef struct INSTR_Arithmatic
{
    uint32_t filter:2;
    uint32_t opcode:6;
    uint32_t s_reg_a:4;
    uint32_t s_reg_b:4;
    uint32_t d_reg:4;
    uint32_t padding:12;
} INSTR_Arithmatic;

typedef struct INSTR_Register
{
    uint32_t filter:2;
    uint32_t opcode:6;
    uint32_t reg_a:4;
    uint32_t reg_b:4;
    uint32_t address:16;
} INSTR_Register;

typedef struct INSTR_Immediate
{
    uint32_t filter:2;
    uint32_t opcode:6;
    uint32_t b_reg:4;
    uint32_t d_reg:4;
    uint32_t padding:16;
} INSTR_Immediate;

typedef struct INSTR_Flow
{
    uint32_t filter:2;
    uint32_t opcode:6;
    uint32_t address:24;
} INSTR_Flow;

typedef struct INSTR_Branch
{
    uint32_t filter:2;
    uint32_t opcode:6;
    uint32_t b_reg:4;
    uint32_t d_reg:4;
    uint32_t address:16;
} INSTR_Branch;

#define LOG_INSTR_Arithmatic(op,i) \
    printf("[CPU]\t" op "\ts_reg_a: R(%u), s_reg_b: R(%u), d_reg R(%u)\n", i.s_reg_a, i.s_reg_b, i.d_reg)
#define LOG_INSTR_Register(op,i) \
    printf("[CPU]\t" op "\treg_a: R(%u), reg_b: R(%u), address: %p\n", i.reg_a, i.reg_b, BUFFER_OFFSET(i.address))
#define LOG_INSTR_Immediate(op,i) \
    printf("[CPU]\t" op "\tb_reg: R(%u), d_reg: R(%u), d_reg R(%u)\n", i.b_reg, i.d_reg, i.d_reg)
#define LOG_INSTR_Flow(op,i) \
    printf("[CPU]\t" op "\taddress: %p\n", BUFFER_OFFSET(i.address))
#define LOG_INSTR_Branch(op,i) \
    printf("[CPU]\t" op "\tb_reg: R(%u), d_reg: R(%u), address: %p\n", i.b_reg, i.d_reg, BUFFER_OFFSET(i.address))

/* Accumulator    */
#define RD      0x00 // read into accumulator
#define WR      0x01 // write from accumulator
/* Register       */
#define MOV     0x04 // move from register to register
#define ADD     0x05 // add S-registers to D-register
#define SUB     0x06 // subtract S1-S2 to D-register
#define MUL     0x07 // multiply S-registers to D-register
#define DIV     0x08 // divide S1 / S2 to D-register
#define AND     0x09 // logical & s-registers to d-register
#define OR      0x0A // logical | s-registers to d-register
#define SLT     0x10 // d-reg = S1 < S2 ? 1 : 0
/* Immediate      */
#define ST      0x02 // write from register to address
#define LW      0x03 // load from address to register
#define MOVI    0x0B // transfer address/data directly into a register
#define ADDI    0x0C // adds a data directly to a register
#define MULI    0x0D // multiplies directly to a register
#define DIVI    0x0E // divides directly to a register
#define LDI     0x0F // Loads to a register
#define SLTI    0x11 // d-reg = S1 < Data ? 1 : 0
/* Flow           */
#define HLT     0x12 // logical end of program
#define NOP     0x13 // no operation
#define JMP     0x14 // jump to a location
/* Branch         */
#define BEQ     0x15 // branch if b-reg == d-reg
#define BNE     0x16 // branch if b-reg <> d-reg
#define BEZ     0x17 // branch if b-reg == 0
#define BNZ     0x18 // branch if b-reg <> 0
#define BGZ     0x19 // branch if b-reg > 0
#define BLZ     0x1A // branch if b-reg < 0
