//
// Created by abclzr on 2019/7/5.
//

#ifndef RISCV_STAGE_H
#define RISCV_STAGE_H

#include "buffer.h"

class Stage {
public:
    buffer buf;

    bool pd_MEM(InstructionType);
    void reset();

    virtual void execute(MemoryController *, RegisterController *, bool &) = 0;
};

class IF : public Stage {
public:
    void execute(MemoryController *, RegisterController *, bool &) override ;
};

class ID : public Stage {
public:
    void execute(MemoryController *, RegisterController *, bool &) override ;
};

class EX : public Stage {
public:
    void execute(MemoryController *, RegisterController *, bool &) override ;
};

class MEM : public Stage {
public:
    void execute(MemoryController *, RegisterController *, bool &) override ;
};

class WB : public Stage {
public:
    void execute(MemoryController *, RegisterController *, bool &) override ;
};

#endif //RISCV_STAGE_H
