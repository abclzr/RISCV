//
// Created by abclzr on 2019/7/3.
//

#ifndef RISCV_MEMORYCONTROLLER_H
#define RISCV_MEMORYCONTROLLER_H

#include "configure.h"

class MemoryController {
private:
    uint8_t mem[MAX_ADDRESS];

public:
    MemoryController();

    uint32_t read(mem_address);

    uint16_t read_16(mem_address);

    uint8_t read_8(mem_address);

    void write(mem_address, uint32_t);

    void write_16(mem_address, uint16_t);

    void write_8(mem_address, uint8_t);
};

#endif //RISCV_MEMORYCONTROLLER_H
