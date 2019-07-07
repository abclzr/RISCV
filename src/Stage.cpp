//
// Created by abclzr on 2019/7/5.
//

#include "Stage.h"

void IF::execute(MemoryController* mem, RegisterController* reg, bool &flag)
{
    mem_address npc = reg->get_pc();
    buf.reset();
    buf.ins = mem->read(npc);
    buf.npc = npc;
    reg->add_pc(4);
}

void ID::execute(MemoryController* mem, RegisterController* reg, bool &flag)
{
    buf.analysize(buf.ins);
}

void EX::execute(MemoryController* mem, RegisterController* reg, bool &flag)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
        reg->lock_on(buf.rd);
        break;
    case AUIPC:
        buf.num = buf.npc + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case JAL:
        buf.adr = buf.npc + 4;
        reg->lock_on(buf.rd);
        reg->lock_on_pc();
        break;
    case JALR:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = buf.npc + 4;
        buf.num = buf.imm + reg->get(buf.rs1);
        buf.num ^= (buf.num & 1);
        reg->lock_on(buf.rd);
        reg->lock_on_pc();
        break;
    case BEQ:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = (reg->get(buf.rs1) == reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case BNE:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = (reg->get(buf.rs1) != reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case BLT:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = ((int) reg->get(buf.rs1) < (int) reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case BGE:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = ((int) reg->get(buf.rs1) >= (int) reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case BLTU:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = (reg->get(buf.rs1) < reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case BGEU:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.pd = (reg->get(buf.rs1) >= reg->get(buf.rs2));
        reg->lock_on_pc();
        break;
    case LB:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case LH:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case LW:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case LBU:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case LHU:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        reg->lock_on(buf.rd);
        break;
    case SB:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
        break;
    case SH:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
        break;
    case SW:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.adr = reg->get(buf.rs1) + buf.imm;
        buf.num = reg->get(buf.rs2);
        break;
    case ADDI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        reg->lock_on(buf.rd);
        break;
    case SLTI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num < (int) buf.imm ? 1 : 0);
        reg->lock_on(buf.rd);
        break;
    case SLTIU:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num < buf.imm ? 1 : 0);
        reg->lock_on(buf.rd);
        break;
    case XORI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num ^ buf.imm);
        reg->lock_on(buf.rd);
        break;
    case ORI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num | buf.imm);
        reg->lock_on(buf.rd);
        break;
    case ANDI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num & buf.imm);
        reg->lock_on(buf.rd);
        break;
    case SLLI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num << buf.shamt);
        reg->lock_on(buf.rd);
        break;
    case SRLI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num >> buf.shamt);
        reg->lock_on(buf.rd);
        break;
    case SRAI:
        if (reg->is_lock(buf.rs1)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num >> buf.shamt);
        reg->lock_on(buf.rd);
        break;
    case ADD:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1) + reg->get(buf.rs2);
        reg->lock_on(buf.rd);
        break;
    case SUB:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1) - reg->get(buf.rs2);
        reg->lock_on(buf.rd);
        break;
    case SLL:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num << get_interval(reg->get(buf.rs2), 0, 4));
        reg->lock_on(buf.rd);
        break;
    case SLT:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = ((int) reg->get(buf.rs1) < (int) reg->get(buf.rs2) ? 1 : 0);
        reg->lock_on(buf.rd);
        break;
    case SLTU:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = (reg->get(buf.rs1) < reg->get(buf.rs2) ? 1 : 0);
        reg->lock_on(buf.rd);
        break;
    case XOR:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1) ^ reg->get(buf.rs2);
        reg->lock_on(buf.rd);
        break;
    case SRL:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = (buf.num >> get_interval(reg->get(buf.rs2), 0, 4));
        reg->lock_on(buf.rd);
        break;
    case SRA:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1);
        buf.num = ((int) buf.num >> get_interval(reg->get(buf.rs2), 0, 4));
        reg->lock_on(buf.rd);
        break;
    case OR:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1) | reg->get(buf.rs2);
        reg->lock_on(buf.rd);
        break;
    case AND:
        if (reg->is_lock(buf.rs1) || reg->is_lock(buf.rs2)) {flag = true; return;}
        buf.num = reg->get(buf.rs1) & reg->get(buf.rs2);
        reg->lock_on(buf.rd);
        break;
    default: break;
    }
}

void MEM::execute(MemoryController* mem, RegisterController* reg, bool &flag)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
        break;
    case AUIPC:
        break;
    case JAL:
        break;
    case JALR:
        break;
    case BEQ:
        break;
    case BNE:
        break;
    case BLT:
        break;
    case BGE:
        break;
    case BLTU:
        break;
    case BGEU:
        break;
    case LB:
        buf.num = mem->read_8(buf.adr);
        break;
    case LH:
        buf.num = mem->read_16(buf.adr);
        break;
    case LW:
        buf.num = mem->read(buf.adr);
        break;
    case LBU:
        buf.num = mem->read_8u(buf.adr);
        break;
    case LHU:
        buf.num = mem->read_16u(buf.adr);
        break;
    case SB:
        mem->write_8(buf.adr, buf.num);
        break;
    case SH:
        mem->write_16(buf.adr, buf.num);
        break;
    case SW:
        mem->write(buf.adr, buf.num);
        break;
    case ADDI:
        break;
    case SLTI:
        break;
    case SLTIU:
        break;
    case XORI:
        break;
    case ORI:
        break;
    case ANDI:
        break;
    case SLLI:
        break;
    case SRLI:
        break;
    case SRAI:
        break;
    case ADD:
        break;
    case SUB:
        break;
    case SLL:
        break;
    case SLT:
        break;
    case SLTU:
        break;
    case XOR:
        break;
    case SRL:
        break;
    case SRA:
        break;
    case OR:
        break;
    case AND:
        break;
    default: break;
    }
}

void WB::execute(MemoryController* mem, RegisterController* reg, bool &flag)
{
    if (buf.type == INVALID) return;
    switch (buf.type) {
    case LUI:
        reg->set_up20(buf.rd, buf.imm);
        reg->lock_off(buf.rd);
        break;
    case AUIPC:
//        num = buf.npc + buf.imm;
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case JAL:
        reg->set(buf.rd, buf.adr);
        reg->lock_off(buf.rd);
        reg->add_pc(buf.imm - 4);
        reg->lock_off_pc();
        flag = true;
        return;
        break;
    case JALR:
        reg->set(buf.rd, buf.adr);
        reg->lock_off(buf.rd);
//        num = buf.imm + reg->get(buf.rs1);
//        num ^= (num & 1);
        reg->set_pc(buf.num);
        reg->lock_off_pc();
        flag = true;
        return;
        break;
    case BEQ:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case BNE:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case BLT:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case BGE:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case BLTU:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case BGEU:
        reg->lock_off_pc();
        if (buf.pd) {reg->add_pc(buf.imm - 4); flag = true; return;}
        break;
    case LB:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8(adr);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case LH:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16(adr);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case LW:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read(adr);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case LBU:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_8u(adr);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case LHU:
//        adr = reg->get(buf.rs1) + buf.imm;
//        num = mem->read_16u(adr);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
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
        reg->lock_off(buf.rd);
        break;
    case SLTI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SLTIU:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case XORI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case ORI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case ANDI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SLLI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SRLI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SRAI:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case ADD:
//        num = reg->get(buf.rs1) + reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SUB:
//        num = reg->get(buf.rs1) - reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SLL:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SLT:
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SLTU:
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case XOR:
//        num = reg->get(buf.rs1) ^ reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SRL:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case SRA:
//        num = reg->get(buf.rs1);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case OR:
//        num = reg->get(buf.rs1) | reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    case AND:
//        num = reg->get(buf.rs1) & reg->get(buf.rs2);
        reg->set(buf.rd, buf.num);
        reg->lock_off(buf.rd);
        break;
    default: break;
    }
}

void Stage::reset() {
    buf.reset();
}
