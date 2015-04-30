/******************************************************
 * cpu.cpp - cpu implementation
 * created 150204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include <cstring>

#include <boost/bind.hpp>
#include <boost/chrono.hpp>
#include <iostream>

#include "cpu.h"
#include "opcodes.h"

#ifdef REG
#undef REG
#endif
/* Access register of this CPU */
#define REG(x) (*((WORD *)this + x))

#define EXTRACT_OPCODE(x)   (0x3F000000 & x) >> 24

boost::mutex CPU::m_screen;

void CPU::runloop()
{
    boost::chrono::high_resolution_clock::time_point start, stop;

    for ( ; ; )
    {
        start = boost::chrono::high_resolution_clock::now();
        /* block thread until we're assigned a program */
        cv.wait(lock, [this] { return *ReadyState == CPU_WORKING; } );
        stop = boost::chrono::high_resolution_clock::now();

        {
        boost::mutex::scoped_lock l(m_screen);
        std::cout << "Wait time:\t" << (stop - start).count() << std::endl;
        }

        /* @TODO: chrono here */
        // while ( *ReadyState == CPU_WORKING )
        start = boost::chrono::high_resolution_clock::now();
        for ( size_t i = 0; i < state.job_size; i++ )
        {
            fetch(state.data + state.program_counter);
            decode();
        }
        stop = boost::chrono::high_resolution_clock::now();

        {
        boost::mutex::scoped_lock l(m_screen);
        std::cout << "Execute time:\t" << (stop - start).count() << std::endl;
        }
        
        *ReadyState = CPU_IDLE;
    }
}

CPU::CPU()
{
    /* zero-initialize struct */
    state = {};
    // ReadyState = CPU_IDLE;

    /* set up our 'core' */
    lock = boost::unique_lock<boost::mutex>( mutex );
    thread = boost::thread(boost::bind( &CPU::runloop, this ));

    ReadyState = new CPU_STATE;
    *ReadyState = CPU_IDLE;
}

CPU::~CPU()
{
    thread.join();
    // delete[] registers;
}

CPU::operator WORD*() const
{
    return const_cast<WORD *>(state.registers);
}

void CPU::fetch(const WORD * instr)
{
    memcpy(&(state.instruction), instr, sizeof(WORD));
    state.program_counter++;
}

#define CPU_DECODE_CASE(instr, type) \
    case instr: { \
        INSTR_##type instruction = *((INSTR_##type *)&(this->state.instruction));
        //LOG_INSTR_##type( #instr, instruction); 
    
#define CPU_BREAK_CASE \
    break; \
    }

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

void * CPU::decode()
{
    switch (EXTRACT_OPCODE(state.instruction))
    {
        /* Accumulator    */
        CPU_DECODE_CASE(RD,   Register)
            CPU_BREAK_CASE
        CPU_DECODE_CASE(WR,   Register)
            CPU_BREAK_CASE
        /* Register       */
        CPU_DECODE_CASE(MOV,  Immediate)
            REG(instruction.d_reg) = REG(instruction.b_reg); CPU_BREAK_CASE
        CPU_DECODE_CASE(ADD,  Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) + REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(SUB,  Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) - REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(MUL,  Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) * REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(DIV,  Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) / REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(AND,  Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) & REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(OR,   Arithmatic)
            REG(instruction.d_reg) = REG(instruction.s_reg_a) | REG(instruction.s_reg_b); CPU_BREAK_CASE
        CPU_DECODE_CASE(SLT,  Arithmatic)
            REG(instruction.d_reg) = (REG(instruction.s_reg_a) < REG(instruction.s_reg_b)) ? 1 : 0; CPU_BREAK_CASE
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
            *ReadyState = CPU_IDLE;
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
            DLOG("Unknown opcode.");
            return nullptr;
            break;
    }

    /* auto fail tests for now */
    return nullptr;
}

#pragma clang diagnostic pop

#undef CPU_DECODE_CASE
#undef CPU_BREAK_CASE
