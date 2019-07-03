//
// Created by abclzr on 2019/7/3.
//

#include "MemoryController.h"
MemoryController::MemoryController()
{
    memset(mem, 0, sizeof(mem));
}

uint32_t MemoryController::read(mem_address adr)
{
    uint32_t ans;
    memcpy(&ans, mem + adr, 4);
    return ans;
}

uint16_t MemoryController::read_16(mem_address adr) {
    uint16_t ans;
    memcpy(&ans, mem + adr, 2);
    return ans;
}

uint8_t MemoryController::read_8(mem_address adr) {
    return mem[adr];
}

void MemoryController::write(mem_address adr, uint32_t x) {
    memcpy(mem + adr, &x, 4);
}

void MemoryController::write_16(mem_address adr, uint16_t x) {
    memcpy(mem + adr, &x, 2);
}

void MemoryController::write_8(mem_address adr, uint8_t x) {
    mem[adr] = x;
}