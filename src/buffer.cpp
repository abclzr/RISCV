//
// Created by abclzr on 2019/7/5.
//

#include "buffer.h"
buffer::buffer() : Instruction()
{
    num = 0;
    adr = 0;
    pd = false;
}
buffer& buffer::operator=(const buffer& other)
{
    if (this == &other) return *this;
    Instruction::operator=(other);
    num = other.num;
    adr = other.adr;
    pd = other.pd;
}

void buffer::reset()
{
    Instruction::reset();
    num = 0;
    adr = 0;
    pd = false;
}
