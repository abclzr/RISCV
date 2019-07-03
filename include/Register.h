//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_REGISTER_H
#define RISCV_REGISTER_H

#include "configure.h"

class Register {
private:
    int32_t c;

public:
    Register() : c(0) {}

    void set(int32_t);

    int32_t get();
};


#endif //RISCV_REGISTER_H
