//
// Created by abclzr on 2019/7/5.
//

#ifndef RISCV_BUFFER_H
#define RISCV_BUFFER_H

#include "Instruction.h"

class buffer : public Instruction {
public:
    uint32_t num;
    uint32_t adr;
    mem_address npc;
    bool pd;

    buffer();

    void reset() override;

    buffer & operator=(const buffer &);
};

#endif //RISCV_BUFFER_H
