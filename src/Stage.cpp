//
// Created by abclzr on 2019/7/5.
//

#include "Stage.h"

void IF::execute(MemoryController* mem, RegisterController* reg)
{
    mem_address npc = reg->get_pc();
    buf.reset();
    buf.ins = mem->read(npc);
}

void ID::execute(MemoryController* mem, RegisterController* reg)
{
    buf.analysize(buf.ins);
}

void EX::execute(MemoryController* mem, RegisterController* reg)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
//        reg->set_up20(buf.rd, buf.imm);
        break;
    case AUIPC:
        buf.num = reg->get_pc() + buf.imm;
//        reg->set(buf.rd, num);
        break;
    case JAL:
        buf.adr = reg->get_pc() + 4;
//        reg->set(buf.rd, reg->get_pc() + 4);
//        reg->add_pc(buf.imm);
//        return;
        break;
    case JALR:
        buf.adr = reg->get_pc() + 4;
//        reg->set(buf.rd, reg->get_pc() + 4);
        buf.num = buf.imm + reg->get(buf.rs1);
        buf.num ^= (buf.num & 1);
//        reg->set_pc(num);
//        return;
        break;
    case BEQ:
        buf.pd = (reg->get(buf.rs1) == reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case BNE:
        buf.pd = (reg->get(buf.rs1) != reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case BLT:
        buf.pd = ((int) reg->get(buf.rs1) < (int) reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case BGE:
        buf.pd = ((int) reg->get(buf.rs1) >= (int) reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case BLTU:
        buf.pd = (reg->get(buf.rs1) < reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case BGEU:
        buf.pd = (reg->get(buf.rs1) >= reg->get(buf.rs2)); //{reg->add_pc(buf.imm); return;}
        break;
    case LB:
        buf.adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8(adr);
//        reg->set(buf.rd, num);
        break;
    case LH:
        buf.adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16(adr);
//        reg->set(buf.rd, num);
        break;
    case LW:
        buf.adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read(adr);
//        reg->set(buf.rd, num);
        break;
    case LBU:
        buf.adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8u(adr);
//        reg->set(buf.rd, num);
        break;
    case LHU:
        buf.adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16u(adr);
//        reg->set(buf.rd, num);
        break;
    case SB:
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
//        mem->write_8(adr, num);
        break;
    case SH:
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
//        mem->write_16(adr, num);
        break;
    case SW:
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
//        mem->write(adr, num);
        break;
    case ADDI:
        buf.num = reg->get(buf.rs1);
//        reg->set(buf.rd, num + buf.imm);
        break;
    case SLTI:
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num < (int) buf.imm ? 1 : 0);
//        reg->set(buf.rd, (int) buf.num < (int) buf.imm ? 1 : 0);
        break;
    case SLTIU:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num < buf.imm ? 1 : 0);
//        reg->set(buf.rd, num < buf.imm ? 1 : 0);
        break;
    case XORI:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num ^ buf.imm);
//        reg->set(buf.rd, num ^ buf.imm);
        break;
    case ORI:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num | buf.imm);
//        reg->set(buf.rd, num | buf.imm);
        break;
    case ANDI:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num & buf.imm);
//        reg->set(buf.rd, num & buf.imm);
        break;
    case SLLI:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num << buf.shamt);
//        reg->set(buf.rd, num << buf.shamt);
        break;
    case SRLI:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num >> buf.shamt);
//        reg->set(buf.rd, num >> buf.shamt);
        break;
    case SRAI:
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num >> buf.shamt);
//        reg->set(buf.rd, (int) num >> buf.shamt);
        break;
    case ADD:
        buf.num = reg->get(buf.rs1) + reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SUB:
        buf.num = reg->get(buf.rs1) - reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SLL:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num << get_interval(reg->get(buf.rs2), 0, 4));
//        reg->set(buf.rd, num << get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case SLT:
        buf.num = ((int) reg->get(buf.rs1) < (int) reg->get(buf.rs2) ? 1 : 0);
//        reg->set(buf.rd, (int) reg->get(buf.rs1) < (int) reg->get(buf.rs2) ? 1 : 0);
        break;
    case SLTU:
        buf.num = (reg->get(buf.rs1) < reg->get(buf.rs2) ? 1 : 0);
//        reg->set(buf.rd, reg->get(buf.rs1) < reg->get(buf.rs2) ? 1 : 0);
        break;
    case XOR:
        buf.num = reg->get(buf.rs1) ^ reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SRL:
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num >> get_interval(reg->get(buf.rs2), 0, 4));
//        reg->set(buf.rd, num >> get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case SRA:
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num >> get_interval(reg->get(buf.rs2), 0, 4));
//        reg->set(buf.rd, (int) num >> get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case OR:
        buf.num = reg->get(buf.rs1) | reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case AND:
        buf.num = reg->get(buf.rs1) & reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    default: break;
    }
//    reg->add_pc(4);
}

void MEM::execute(MemoryController* mem, RegisterController* reg)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
//        reg->set_up20(buf.rd, buf.imm);
        break;
    case AUIPC:
//        num = reg->get_pc() + buf.imm;
//        reg->set(buf.rd, num);
        break;
    case JAL:
//        reg->set(buf.rd, reg->get_pc() + 4);
//        reg->add_pc(buf.imm);
//        return;
        break;
    case JALR:
//        reg->set(buf.rd, reg->get_pc() + 4);
//        num = buf.imm + reg->get(buf.rs1);
//        num ^= (num & 1);
//        reg->set_pc(num);
//        return;
        break;
    case BEQ:
//        if (reg->get(buf.rs1) == reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case BNE:
//        if (reg->get(buf.rs1) != reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case BLT:
//        if ((int) reg->get(buf.rs1) < (int) reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case BGE:
//        if ((int) reg->get(buf.rs1) >= (int) reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case BLTU:
//        if (reg->get(buf.rs1) < reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case BGEU:
//        if (reg->get(buf.rs1) >= reg->get(buf.rs2)) {reg->add_pc(buf.imm); return;}
        break;
    case LB:
//        adr = reg->get(buf.rs1) + buf.imm;
        buf.num = mem->read_8(buf.adr);
//        reg->set(buf.rd, num);
        break;
    case LH:
//        adr = reg->get(buf.rs1) + buf.imm;
        buf.num = mem->read_16(buf.adr);
//        reg->set(buf.rd, num);
        break;
    case LW:
//        adr = reg->get(buf.rs1) + buf.imm;
        buf.num = mem->read(buf.adr);
//        reg->set(buf.rd, num);
        break;
    case LBU:
//        adr = reg->get(buf.rs1) + buf.imm;
        buf.num = mem->read_8u(buf.adr);
//        reg->set(buf.rd, num);
        break;
    case LHU:
//        adr = reg->get(buf.rs1) + buf.imm;
        buf.num = mem->read_16u(buf.adr);
//        reg->set(buf.rd, num);
        break;
    case SB:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
        mem->write_8(buf.adr, buf.num);
        break;
    case SH:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
        mem->write_16(buf.adr, buf.num);
        break;
    case SW:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
        mem->write(buf.adr, buf.num);
        break;
    case ADDI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num + buf.imm);
        break;
    case SLTI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, (int) num < (int) buf.imm ? 1 : 0);
        break;
    case SLTIU:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num < buf.imm ? 1 : 0);
        break;
    case XORI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num ^ buf.imm);
        break;
    case ORI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num | buf.imm);
        break;
    case ANDI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num & buf.imm);
        break;
    case SLLI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num << buf.shamt);
        break;
    case SRLI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num >> buf.shamt);
        break;
    case SRAI:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, (int) num >> buf.shamt);
        break;
    case ADD:
//        num = reg->get(buf.rs1) + reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SUB:
//        num = reg->get(buf.rs1) - reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SLL:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num << get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case SLT:
//        reg->set(buf.rd, (int) reg->get(buf.rs1) < (int) reg->get(buf.rs2) ? 1 : 0);
        break;
    case SLTU:
//        reg->set(buf.rd, reg->get(buf.rs1) < reg->get(buf.rs2) ? 1 : 0);
        break;
    case XOR:
//        num = reg->get(buf.rs1) ^ reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case SRL:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, num >> get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case SRA:
//        num = reg->get(buf.rs1);
//        reg->set(buf.rd, (int) num >> get_interval(reg->get(buf.rs2), 0, 4));
        break;
    case OR:
//        num = reg->get(buf.rs1) | reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    case AND:
//        num = reg->get(buf.rs1) & reg->get(buf.rs2);
//        reg->set(buf.rd, num);
        break;
    default: break;
    }
//    reg->add_pc(4);
}

void WB::execute(MemoryController* mem, RegisterController* reg)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
        reg->set_up20(buf.rd, buf.imm);
        break;
    case AUIPC:
//        num = reg->get_pc() + buf.imm;
        reg->set(buf.rd, buf.num);
        break;
    case JAL:
        reg->set(buf.rd, buf.adr);
        reg->add_pc(buf.imm);
        return;
        break;
    case JALR:
        reg->set(buf.rd, buf.adr);
//        num = buf.imm + reg->get(buf.rs1);
//        num ^= (num & 1);
        reg->set_pc(buf.num);
        return;
        break;
    case BEQ:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case BNE:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case BLT:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case BGE:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case BLTU:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case BGEU:
        if (buf.pd) {reg->add_pc(buf.imm); return;}
        break;
    case LB:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8(adr);
        reg->set(buf.rd, buf.num);
        break;
    case LH:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16(adr);
        reg->set(buf.rd, buf.num);
        break;
    case LW:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read(adr);
        reg->set(buf.rd, buf.num);
        break;
    case LBU:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8u(adr);
        reg->set(buf.rd, buf.num);
        break;
    case LHU:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16u(adr);
        reg->set(buf.rd, buf.num);
        break;
    case SB:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
//        mem->write_8(adr, num);
        break;
    case SH:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
//        mem->write_16(adr, num);
        break;
    case SW:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = reg->get(buf.rs2);
//        mem->write(adr, num);
        break;
    case ADDI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num + buf.imm);
        break;
    case SLTI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SLTIU:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case XORI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case ORI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case ANDI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SLLI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SRLI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SRAI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case ADD:
//        num = reg->get(buf.rs1) + reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        break;
    case SUB:
//        num = reg->get(buf.rs1) - reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        break;
    case SLL:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SLT:
        reg->set(buf.rd, buf.num);
        break;
    case SLTU:
        reg->set(buf.rd, buf.num);
        break;
    case XOR:
//        num = reg->get(buf.rs1) ^ reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        break;
    case SRL:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case SRA:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        break;
    case OR:
//        num = reg->get(buf.rs1) | reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        break;
    case AND:
//        num = reg->get(buf.rs1) & reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        break;
    default: break;
    }
    reg->add_pc(4);
}