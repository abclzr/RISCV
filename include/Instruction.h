//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_INSTRUCTION_H
#define RISCV_INSTRUCTION_H

#include "configure.h"
#include "MemoryController.h"
#include "RegisterController.h"

enum InstructionType {
  LUI, AUIPC, JAL, JALR, BEQ, BNE, BLT, BGE, BLTU, BGEU, LB, LH, LW, LBU, LHU,
  SB, SH, SW, ADDI, SLTI, SLTIU, XORI, ORI, ANDI, SLLI, SRLI, SRAI, ADD, SUB,
  SLL, SLT, SLTU, XOR, SRL, SRA, OR, AND, INVALID
};

uint32_t get_interval(uint32_t, int, int);

uint32_t get_I_imm(uint32_t);
uint32_t get_S_imm(uint32_t);
uint32_t get_B_imm(uint32_t);
uint32_t get_U_imm(uint32_t);
uint32_t get_J_imm(uint32_t);

void push(uint32_t &, int, int, uint32_t, int);

class Instruction {
public:
    uint32_t ins;
    InstructionType type;
    uint8_t opcode;
    reg_address rd, rs1, rs2;
    uint32_t imm, shamt;

    Instruction();

    void reset();

    explicit Instruction(uint32_t);

    void analysize(uint32_t);

    void execute(MemoryController *, RegisterController *);

    Instruction & operator=(const Instruction &);
};

#endif //RISCV_INSTRUCTION_H
