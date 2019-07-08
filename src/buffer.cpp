//
// Created by abclzr on 2019/7/5.
//

#include "buffer.h"
buffer::buffer() : Instruction()
{
    num = 0;
    adr = 0;
    pd = false;
    npc = 0;
    R1 = 0;
    R2 = 0;
}
buffer& buffer::operator=(const buffer& other)
{
    if (this == &other) return *this;
    Instruction::operator=(other);
    num = other.num;
    adr = other.adr;
    pd = other.pd;
    npc = other.npc;
    R1 = other.R1;
    R2 = other.R2;
    return *this;
}

void buffer::reset()
{
    Instruction::reset();
    num = 0;
    adr = 0;
    pd = false;
    npc = 0;
    R1 = 0;
    R2 = 0;
}
