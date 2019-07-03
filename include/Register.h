//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_REGISTER_H
#define RISCV_REGISTER_H

#include "configure.h"

class Register {
private:
    uint32_t c;

public:
    Register() : c(0) {}

    void set(uint32_t);

    void set_up20_0();

    void set_down12_0();

    void add(uint32_t);

    uint32_t get();
};


#endif //RISCV_REGISTER_H
