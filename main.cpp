#include <iostream>
#include "Instruction.h"
#include "MemoryController.h"
#include "RegisterController.h"
#include <stdexcept>

char s[1000003];

uint32_t trans(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('A' <= c && c <= 'F') return c - 'A';
    else if ('a' <= c && c <= 'f') return c - 'a';
    else throw std::invalid_argument("233");
}

uint32_t get_hex(char *c, int len)
{
    uint32_t ret = 0;
    for (int i = 0; i < len; ++i)
        ret = ret * 16 + trans(c[i]);
    return ret;
}

int main() {
    freopen("naive.data", "r", stdin);

    MemoryController mem;
    RegisterController reg;

    uint32_t tmp = 0;

    while (~scanf("%s", s)) {
        if (s[0] == '@') {
            tmp = get_hex(s + 1, strlen(s) - 1);
        } else {
            int len = strlen(s);
            for (int i = 0; i < len; i += 2) {
                uint32_t num = get_hex(s + i, 2);
                mem.write(tmp, num);
                ++tmp;
            }
        }
    }

    tmp = 0;
    while (tmp != 0x00c6823) {
        Instruction ins(mem.read(tmp));
        ins.execute(&mem, &reg);
        tmp = reg.get_pc();
    }

    printf("%d\n", reg.get(10) & (1 << 8) - 1);

    return 0;
}