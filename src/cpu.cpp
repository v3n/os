/******************************************************
 * cpu.cpp - cpu implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <cstring>

#include "cpu.h"
#include "opcodes.h"

#ifdef R
#undef R
#endif
/* Access register of this CPU */
#define R(x) (*((WORD *)this + x))

#define EXTRACT_TYPECODE(x) (0x003 << 30 & x) >> 30
#define EXTRACT_OPCODE(x)   (0x06F << 24 & x) >> 24

#define EXTRACT_BASE_REG(x) (0x00F << 24 & x) >> 24 
#define EXTRACT_DEST_REG(x) (0x00F << 20 & x) >> 20
#define EXTRACT_JMP_ADDR(x) (0xFFF << 0 & x) >> 0

CPU::CPU()
{
    // registers = WORD[16];
    instruction = NULL;
    program_counter = 0;
}

CPU::~CPU()
{
    // delete[] registers;
}

CPU::operator WORD*() const
{
    return const_cast<WORD *>(&registers);
}

void CPU::fetch(const WORD * instr)
{
    memcpy(&instruction, instr, sizeof(WORD));
    program_counter++;
}

#define CPU_DECODE_CASE(instr, type) \
    case instr: { \
        DLOG( #instr ); \
        INSTR_##type instruction = *((INSTR_##type *)&(this->instruction));
    
#define CPU_BREAK_CASE \
    break; \
    }

void * CPU::decode()
{
    DLOG("%X %X %X %X", instruction >> (sizeof(WORD)*8 - 2),
                        EXTRACT_OPCODE(instruction),
                        0xF << 8 & instruction,
                        0xF << 0 & instruction
        );

    switch (EXTRACT_OPCODE(instruction))
    {
        /* Accumulator    */
        CPU_DECODE_CASE(RD,   Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(WR,   Register)
            CPU_BREAK_CASE
        /* Register       */
        CPU_DECODE_CASE(MOV,  Immediate)
            R(instruction.d_reg) = R(instruction.b_reg); CPU_BREAK_CASE
        CPU_DECODE_CASE(ADD,  Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) + R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(SUB,  Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) - R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(MUL,  Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) * R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(DIV,  Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) / R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(AND,  Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) & R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(OR,   Arithmatic)
            R(instruction.d_reg) = R(instruction.s_reg_a) | R(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(SLT,  Arithmatic)
            R(instruction.d_reg) = (R(instruction.s_reg_a) < R(instruction.s_reg_b)) ? 1 : 0; CPU_BREAK_CASE
        /* Immediate      */
        CPU_DECODE_CASE(ST,   Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(LW,   Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(MOVI, Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(ADDI, Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(MULI, Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(DIVI, Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(LDI,  Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(SLTI, Register)
            CPU_BREAK_CASE
        /* Flow           */
        CPU_DECODE_CASE(HLT,  Flow)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(NOP,  Flow)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(JMP,  Flow)
            CPU_BREAK_CASE
        /* Branch         */
        CPU_DECODE_CASE(BEQ,  Branch)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(BNE,  Branch)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(BEZ,  Branch)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(BNZ,  Branch)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(BGZ,  Branch)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(BLZ,  Branch)
            CPU_BREAK_CASE
        default:
            return nullptr;
            break;
    }

    /* auto fail tests for now */
    return nullptr;
}

#undef CPU_DECODE_CASE

