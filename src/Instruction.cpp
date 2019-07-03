//
// Created by abclzr on 2019/7/3.
//

#include "Instruction.h"
Instruction::Instruction() : ins(0), type(INVALID), opcode(0), rd(0), rs1(0), rs2(0), imm(0) {}

Instruction::Instruction(uint32_t i) : ins(i)
{
    analysize(i);
}

//To be analysized:
//type
//opcode
//rd, rs1, rs2
//imm
void Instruction::analysize(uint32_t i)
{
    opcode = get_interval(i, 0, 6);
    rd = get_interval(i, 7, 11);
    uint8_t i12 = get_interval(i, 12, 14);
    rs1 = get_interval(i, 15, 19);
    rs2 = get_interval(i, 20, 24);
    switch (opcode) {
    case 0x37: //0110111
        type = LUI;
        push(imm, 12, 31, i, 12);
        break;
    case 0x17: //0010111
        type = AUIPC;
        push(imm, 12, 31, i, 12);
        break;
    case 0x6f: //1101111
        type = JAL;
        push(imm, 12, 19, i, 12);
        push(imm, 11, 11, i, 20);
        push(imm, 1, 10, i, 21);
        push(imm, 20, 20, i, 31);
        break;
    case 0x67: //1100111
        type = JALR;
        push(imm, 0, 11, i, 20);
        break;
    case 0x63: //1100011
        push(imm, 11, 11, i, 7);
        push(imm, 1, 4, i, 8);
        push(imm, 5, 10, i, 25);
        push(imm, 12, 12, i, 31);
        switch (i12) {
        case 0: type = BEQ; break;
        case 1: type = BNE; break;
        case 4: type = BLT; break;
        case 5: type = BGE; break;
        case 6: type = BLTU; break;
        case 7: type = BGEU; break;
        default: type = INVALID;
        }
        break;
    case 0X03: //0000011
        push(imm, 0, 11, i, 20);
        switch (i12) {
        case 0: type = LB; break;
        case 1: type = LH; break;
        case 2: type = LW; break;
        case 4: type = LBU; break;
        case 5: type = LHU; break;
        default: type = INVALID;
        }
        break;
    case 0x23: //0100011
        push(imm, 0, 4, i, 7);
        push(imm, 5, 11, i, 25);
        switch (i12) {
        case 0: type = SB; break;
        case 1: type = SH; break;
        case 2: type = SW; break;
        default: type = INVALID;
        }
        break;
    case 0x13: //0010011
        push(imm, 0, 11, i, 20);
        switch (i12) {
        case 0: type = ADDI; break;
        case 2: type = SLTI; break;
        case 3: type = SLTIU; break;
        case 4: type = XORI; break;
        case 6: type = ORI; break;
        case 7: type = ANDI; break;
        case 1: type = SLLI; imm = rs2; break;
        case 5: imm = rs2; get_interval(i, 30, 30) == 0 ? type = SRLI : type = SRAI; break;
        default: type = INVALID;
        }
        break;
    case 0x33: //0110011
        switch (i12) {
        case 0: get_interval(i, 30, 30) == 0 ? type = ADD : type = SUB; break;
        case 1: type = SLL; break;
        case 2: type = SLT; break;
        case 3: type = SLTU; break;
        case 4: type = XOR; break;
        case 5: get_interval(i, 30, 30) == 0 ? type = SRL : type = SRA; break;
        case 6: type = OR; break;
        case 7: type = AND; break;
        default: type = INVALID; break;
        }
        break;
    default:
        type = INVALID;
        break;
    };
}

uint32_t get_interval(uint32_t i, int l, int r)
{
    i >>= l;
    i &= ((1 << (r - l + 1)) - 1);
    return i;
}

void push(uint32_t& x, int l, int r, uint32_t i, int L)
{
    i = get_interval(i, L, L + r - l);
    x |= (i << l);
}
