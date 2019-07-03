//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_REGISTERCONTROLLER_H
#define RISCV_REGISTERCONTROLLER_H

#include "Register.h"

class RegisterController {
private:
    Register reg[32];
    Register pc;

public:
    uint32_t get(reg_address);
    void set(reg_address, uint32_t);
    void add(reg_address, uint32_t);
    void set_up20(reg_address, uint32_t);
    void set_down12(reg_address, uint32_t);

    uint32_t get_pc();
    void set_pc(uint32_t);
    void add_pc(uint32_t);
};

#endif //RISCV_REGISTERCONTROLLER_H
