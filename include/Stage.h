//
// Created by abclzr on 2019/7/5.
//

#ifndef RISCV_STAGE_H
#define RISCV_STAGE_H

#include "buffer.h"

class Stage {
public:
    buffer buf;

    virtual void execute(MemoryController *, RegisterController *) = 0;
};

class IF : Stage {
public:
    void execute(MemoryController *, RegisterController *) override ;
};

class ID : Stage {
public:
    void execute(MemoryController *, RegisterController *) override ;
};

class EX : Stage {
public:
    void execute(MemoryController *, RegisterController *) override ;
};

class MEM : Stage {
public:
    void execute(MemoryController *, RegisterController *) override ;
};

class WB : Stage {
public:
    void execute(MemoryController *, RegisterController *) override ;
};

#endif //RISCV_STAGE_H
