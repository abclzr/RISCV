//
// Created by abclzr on 2019/7/3.
//

#include "../include/Register.h"

void Register::set(int32_t x) {
    c = x;
}

int32_t Register::get() {
    return c;
}