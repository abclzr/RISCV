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
//imm, shamt
void Instruction::analysize(uint32_t i)
{
    opcode = get_interval(i, 0, 6);
    rd = get_interval(i, 7, 11);
    uint8_t i12 = get_interval(i, 12, 14);
    rs1 = get_interval(i, 15, 19);
    shamt = rs2 = get_interval(i, 20, 24);
    imm = 0;
    switch (opcode) {
    case 0x37: //0110111
        type = LUI;
        imm = get_U_imm(i);
        break;
    case 0x17: //0010111
        type = AUIPC;
        imm = get_U_imm(i);
        break;
    case 0x6f: //1101111
        type = JAL;
        imm = get_J_imm(i);
        break;
    case 0x67: //1100111
        type = JALR;
        imm = get_I_imm(i);
        break;
    case 0x63: //1100011
        imm = get_B_imm(i);
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
        imm = get_I_imm(i);
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
        imm = get_S_imm(i);
        switch (i12) {
        case 0: type = SB; break;
        case 1: type = SH; break;
        case 2: type = SW; break;
        default: type = INVALID;
        }
        break;
    case 0x13: //0010011
        imm = get_I_imm(i);
        switch (i12) {
        case 0: type = ADDI; break;
        case 2: type = SLTI; break;
        case 3: type = SLTIU; break;
        case 4: type = XORI; break;
        case 6: type = ORI; break;
        case 7: type = ANDI; break;
        case 1: type = SLLI; break;
        case 5: get_interval(i, 30, 30) == 0 ? type = SRLI : type = SRAI; break;
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

void Instruction::execute(MemoryController* mem, RegisterController* reg)
{
    if (type == INVALID) return;
    uint32_t num;
    uint32_t adr;
    switch (type) {
    case LUI:
        reg->set_up20(rd, imm);
        break;
    case AUIPC:
        num = reg->get_pc() + imm;
        reg->set(rd, num);
        break;
    case JAL:
        reg->set(rd, reg->get_pc() + 4);
        reg->add_pc(imm);
        return;
        break;
    case JALR:
        reg->set(rd, reg->get_pc() + 4);
        num = imm + reg->get(rs1);
        num ^= (num & 1);
        reg->set_pc(num);
        return;
        break;
    case BEQ:
        if (reg->get(rs1) == reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case BNE:
        if (reg->get(rs1) != reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case BLT:
        if ((int) reg->get(rs1) < (int) reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case BGE:
        if ((int) reg->get(rs1) >= (int) reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case BLTU:
        if (reg->get(rs1) < reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case BGEU:
        if (reg->get(rs1) >= reg->get(rs2)) {reg->add_pc(imm); return;}
        break;
    case LB:
        adr = reg->get(rs1) + imm;
        num = mem->read_8(adr);
        reg->set(rd, num);
        break;
    case LH:
        adr = reg->get(rs1) + imm;
        num = mem->read_16(adr);
        reg->set(rd, num);
        break;
    case LW:
        adr = reg->get(rs1) + imm;
        num = mem->read(adr);
        reg->set(rd, num);
        break;
    case LBU:
        adr = reg->get(rs1) + imm;
        num = mem->read_8u(adr);
        reg->set(rd, num);
        break;
    case LHU:
        adr = reg->get(rs1) + imm;
        num = mem->read_16u(adr);
        reg->set(rd, num);
        break;
    case SB:
        adr = reg->get(rs1) + imm;
        num = reg->get(rs2);
        mem->write_8(adr, num);
        break;
    case SH:
        adr = reg->get(rs1) + imm;
        num = reg->get(rs2);
        mem->write_16(adr, num);
        break;
    case SW:
        adr = reg->get(rs1) + imm;
        num = reg->get(rs2);
        mem->write(adr, num);
        break;
    case ADDI:
        num = reg->get(rs1);
        reg->set(rd, num + imm);
        break;
    case SLTI:
        num = reg->get(rs1);
        reg->set(rd, (int) num < (int) imm ? 1 : 0);
        break;
    case SLTIU:
        num = reg->get(rs1);
        reg->set(rd, num < imm ? 1 : 0);
        break;
    case XORI:
        num = reg->get(rs1);
        reg->set(rd, num ^ imm);
        break;
    case ORI:
        num = reg->get(rs1);
        reg->set(rd, num | imm);
        break;
    case ANDI:
        num = reg->get(rs1);
        reg->set(rd, num & imm);
        break;
    case SLLI:
        num = reg->get(rs1);
        reg->set(rd, num << shamt);
        break;
    case SRLI:
        num = reg->get(rs1);
        reg->set(rd, num >> shamt);
        break;
    case SRAI:
        num = reg->get(rs1);
        reg->set(rd, (int) num >> shamt);
        break;
    case ADD:
        num = reg->get(rs1) + reg->get(rs2);
        reg->set(rd, num);
        break;
    case SUB:
        num = reg->get(rs1) - reg->get(rs2);
        reg->set(rd, num);
        break;
    case SLL:
        num = reg->get(rs1);
        reg->set(rd, num << get_interval(reg->get(rs2), 0, 4));
        break;
    case SLT:
        reg->set(rd, (int) reg->get(rs1) < (int) reg->get(rs2) ? 1 : 0);
        break;
    case SLTU:
        reg->set(rd, reg->get(rs1) < reg->get(rs2) ? 1 : 0);
        break;
    case XOR:
        num = reg->get(rs1) ^ reg->get(rs2);
        reg->set(rd, num);
        break;
    case SRL:
        num = reg->get(rs1);
        reg->set(rd, num >> get_interval(reg->get(rs2), 0, 4));
        break;
    case SRA:
        num = reg->get(rs1);
        reg->set(rd, (int) num >> get_interval(reg->get(rs2), 0, 4));
        break;
    case OR:
        num = reg->get(rs1) | reg->get(rs2);
        reg->set(rd, num);
        break;
    case AND:
        num = reg->get(rs1) & reg->get(rs2);
        reg->set(rd, num);
        break;
    default: break;
    }
    reg->add_pc(4);
}

Instruction& Instruction::operator=(const Instruction& other)
{
    if (this == &other) return *this;
    ins = other.ins;
    type = other.type;
    opcode = other.opcode;
    rd = other.rd;
    rs1 = other.rs1;
    rs2 = other.rs2;
    imm = other.imm;
    shamt = other.shamt;
    return *this;
}

void Instruction::reset()
{
    ins = 0;
    type = INVALID;
    opcode = 0;
    rd = 0;
    rs1 = 0;
    rs2 = 0;
    imm = 0;
    shamt = 0;
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

uint32_t get_I_imm(uint32_t i)
{
    uint32_t num = (int) i >> 20;
    return num;
}

uint32_t get_S_imm(uint32_t i)
{
    uint32_t num = (int) i >> 20;
    num ^= get_interval(num, 0, 4);
    push(num, 0, 4, i, 7);
    return num;
}

uint32_t get_B_imm(uint32_t i)
{
    uint32_t num = (int) i >> 20;
    num ^= get_interval(num, 11, 11) << 11;
    num |= get_interval(i, 7, 7) << 11;
    num ^= get_interval(num, 0, 4);
    push(num, 1, 4, i, 8);
    return num;
}

uint32_t get_U_imm(uint32_t i)
{
    uint32_t num = i;
    num ^= get_interval(i, 0, 11);
    return num;
}

uint32_t get_J_imm(uint32_t i)
{
    uint32_t num = (int) i >> 20;
    num ^= get_interval(num, 0, 0);
    num ^= get_interval(num, 11, 19) << 11;
    push(num, 11, 11, i, 20);
    push(num, 12, 19, i, 12);
    return num;
}
