/******************************************************
 * cpu_tests.cpp - cpu unit tests
 * created 140204 jonathan howard (j@hovverd.com)
 ******************************************************/

#include "gtest/gtest.h"

#include "utils.h"
#include "cpu.h"
#include "opcodes.h"

TEST(OpCode, IsCorrectSize)
{
    ASSERT_TRUE(sizeof(INSTR_Arithmatic) == 4);
    ASSERT_TRUE(sizeof(INSTR_Register) == 4);
    ASSERT_TRUE(sizeof(INSTR_Immediate) == 4);
    ASSERT_TRUE(sizeof(INSTR_Flow) == 4);
    ASSERT_TRUE(sizeof(INSTR_Branch) == 4);
}

TEST(CPU_Fetch, InitializesToNULL)
{
    CPU * cpu = new CPU();
    ASSERT_EQ(*REG(cpu, -2), NULL);
}

