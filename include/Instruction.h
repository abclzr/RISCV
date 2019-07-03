//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_INSTRUCTION_H
#define RISCV_INSTRUCTION_H

#include "configure.h"

enum InstructionType {
  LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU,
  SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB,
  SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND
};

class Instruction {

};

#endif //RISCV_INSTRUCTION_H
