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
    int32_t get(reg_address);
    void set(reg_address, int32_t);
};

#endif //RISCV_REGISTERCONTROLLER_H
