//
// Created by abclzr on 2019/7/3.
//

#include "../include/RegisterController.h"
uint32_t RegisterController::get(reg_address id)
{
    return reg[id].get();
}

void RegisterController::set(reg_address id, uint32_t x)
{
    if (id == 0) return;
    reg[id].set(x);
}

void RegisterController::set_up20(reg_address id, uint32_t x)
{
    if (id == 0) return;
    reg[id].set(x);
    reg[id].set_down12_0();
}

void RegisterController::set_down12(reg_address id, uint32_t x)
{
    if (id == 0) return;
    reg[id].set(x);
    reg[id].set_up20_0();
}

void RegisterController::add(reg_address id, uint32_t x)
{
    if (id == 0) return;
    reg[id].add(x);
}

void RegisterController::set_pc(uint32_t x)
{
    pc.set(x);
}

void RegisterController::add_pc(uint32_t x)
{
    pc.add(x);
}

uint32_t RegisterController::get_pc()
{
    return pc.get();
}

RegisterController::RegisterController() {
    memset(lock, 0, sizeof(lock));
    lock_pc = 0;
}

void RegisterController::lock_on(reg_address id) {
    ++lock[id];
}

void RegisterController::lock_off(reg_address id) {
    --lock[id];
}

void RegisterController::lock_on_pc() {
    ++lock_pc;
}

void RegisterController::lock_off_pc() {
    --lock_pc;
}

bool RegisterController::is_lock(reg_address id) {
    return lock[id] != 0;
}

bool RegisterController::is_lock_pc() {
    return lock_pc != 0;
}

void RegisterController::unlock_all() {
    memset(lock, 0, sizeof(lock));
    lock_pc = 0;
}
