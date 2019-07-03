//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_INSTRUCTION_H
#define RISCV_INSTRUCTION_H

#include "configure.h"

enum InstructionType {
  LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU,
  SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB,
  SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND, INVALID
};

uint32_t get_interval(uint32_t, int, int);

void push(uint32_t &, int, int, uint32_t, int);

class Instruction {
public:
    uint32_t ins;
    InstructionType type;
    uint8_t opcode;
    reg_address rd, rs1, rs2;
    uint32_t imm;

    Instruction();

    explicit Instruction(uint32_t);

    void analysize(uint32_t);
};

#endif //RISCV_INSTRUCTION_H
