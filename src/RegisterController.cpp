//
// Created by abclzr on 2019/7/3.
//

#include "../include/RegisterController.h"
int32_t RegisterController::get(reg_address id)
{
    return reg[id].get();
}

void RegisterController::set(reg_address id, int32_t x)
{
    reg[id].set(x);
}
