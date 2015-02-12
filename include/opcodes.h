/******************************************************
 * instructions.h - instruction definitions
 * created 140211 jonathan howard (j@hovverd.com)
 ******************************************************/

#define stringify(s) #s

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
#define BEZ     0x17 // branch if b-reg != 0
#define BNZ     0x18 // branch if b-reg <> 0
#define BGZ     0x19 // branch if b-reg > 0
#define BLZ     0x1A // branch if b-reg < 0
