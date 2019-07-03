//
// Created by abclzr on 2019/7/3.
//

#include "../include/Register.h"

void Register::set(uint32_t x) {
    c = x;
}

uint32_t Register::get() {
    return c;
}

void Register::set_up20_0()
{
    c <<= 20;
    c >>= 20;
}

void Register::set_down12_0()
{
    c >>= 12;
    c <<= 12;
}

void Register::add(uint32_t x)
{
    c += x;
}
