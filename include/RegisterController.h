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
    uint8_t lock[32];
    uint8_t lock_pc;

public:
    RegisterController();
    uint32_t get(reg_address);
    void set(reg_address, uint32_t);
    void add(reg_address, uint32_t);
    void set_up20(reg_address, uint32_t);
    void set_down12(reg_address, uint32_t);

    uint32_t get_pc();
    void set_pc(uint32_t);
    void add_pc(uint32_t);

    void lock_on(reg_address);
    void lock_off(reg_address);
    void lock_on_pc();
    void lock_off_pc();

    void unlock_all();
    bool is_lock(reg_address);
    bool is_lock_pc();
};

#endif //RISCV_REGISTERCONTROLLER_H
