/******************************************************
 * cpu.cpp - cpu implementation
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <cstring>

#include "cpu.h"
#include "opcodes.h"

#ifdef R
#undef R
#endif
/* Access register of this CPU */
#define R(x) ((WORD *)this+(WORD *)x)


enum Instruction
{
    
};

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

#define CPU_DECODE_CASE(instr) \
    case instr: \
        DLOG(stringify(instr) ); \
        break;

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
        CPU_DECODE_CASE(RD)
        CPU_DECODE_CASE(WR)
        /* Register       */
        CPU_DECODE_CASE(MOV)
        CPU_DECODE_CASE(ADD)
        CPU_DECODE_CASE(SUB)
        CPU_DECODE_CASE(MUL)
        CPU_DECODE_CASE(DIV)
        CPU_DECODE_CASE(AND)
        CPU_DECODE_CASE(OR)
        CPU_DECODE_CASE(SLT)
        /* Immediate      */
        CPU_DECODE_CASE(ST)
        CPU_DECODE_CASE(LW)
        CPU_DECODE_CASE(MOVI)
        CPU_DECODE_CASE(ADDI)
        CPU_DECODE_CASE(MULI)
        CPU_DECODE_CASE(DIVI)
        CPU_DECODE_CASE(LDI)
        CPU_DECODE_CASE(SLTI)
        /* Flow           */
        CPU_DECODE_CASE(HLT)
        CPU_DECODE_CASE(NOP)
        CPU_DECODE_CASE(JMP)
        /* Branch         */
        CPU_DECODE_CASE(BEQ)
        CPU_DECODE_CASE(BNE)
        CPU_DECODE_CASE(BEZ)
        CPU_DECODE_CASE(BNZ)
        CPU_DECODE_CASE(BGZ)
        CPU_DECODE_CASE(BLZ)
        default:
            return nullptr;
            break;
    }

    /* auto fail tests for now */
    return nullptr;
}

#undef CPU_DECODE_CASE

