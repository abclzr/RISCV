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
    uint32_t ans = 0;
    memcpy(&ans, mem + adr, 4);
    return ans;
}

uint32_t MemoryController::read_16(mem_address adr)
{
    uint32_t ans = 0;
    memcpy(&ans, mem + adr, 2);
    if ((ans >> 15) & 1) ans |= ((-1) << 16);
    return ans;
}

uint32_t MemoryController::read_8(mem_address adr)
{
    uint32_t ans = 0;
    memcpy(&ans, mem + adr, 1);
    if ((ans >> 7) & 1) ans |= ((-1) << 8);
    return ans;
}

void MemoryController::write(mem_address adr, uint32_t x) {
    memcpy(mem + adr, &x, 4);
}

void MemoryController::write_16(mem_address adr, uint32_t x) {
    memcpy(mem + adr, &x, 2);
}

void MemoryController::write_8(mem_address adr, uint32_t x) {
    mem[adr] = x;
}

uint32_t MemoryController::read_16u(mem_address adr)
{
    uint32_t ans = 0;
    memcpy(&ans, mem + adr, 2);
    return ans;
}

uint32_t MemoryController::read_8u(mem_address adr)
{
    uint32_t ans = 0;
    memcpy(&ans, mem + adr, 1);
    return ans;
}
