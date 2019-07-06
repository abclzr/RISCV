#include <iostream>
#include "Instruction.h"
#include "MemoryController.h"
#include "RegisterController.h"
#include <stdexcept>
#include "Stage.h"

char s[1000003];

uint32_t trans(char c) {
    if ('0' <= c && c <= '9') return c - '0';
    else if ('A' <= c && c <= 'F') return c - 'A' + 10;
    else if ('a' <= c && c <= 'f') return c - 'a' + 10;
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
    MemoryController mem;
    RegisterController reg;

    uint32_t tmp = 0;

    while (~scanf("%s", s)) {
        if (s[0] == '@') {
            tmp = get_hex(s + 1, strlen(s) - 1);
        } else {
            int len = strlen(s);
            for (int i = 0; i < len; i += 3) {
                uint32_t num = get_hex(s + i, 2);
                mem.write(tmp, num);
                ++tmp;
            }
        }
    }

    IF s1;
    ID s2;
    EX s3;
    MEM s4;
    WB s5;
    /*
    tmp = 0;
    while (true) {
        Instruction ins(mem.read(tmp));
        if (ins.ins == 0x00c68223) break;
        ins.execute(&mem, &reg);
        tmp = reg.get_pc();
    }
     */

    /*
    while (true) {
        s1.execute(&mem, &reg);
        if (s1.buf.ins == 0x00c68223) break;
        s2.buf = s1.buf;
        s2.execute(&mem, &reg);
        s3.buf = s2.buf;
        s3.execute(&mem, &reg);
        s4.buf = s3.buf;
        s4.execute(&mem, &reg);
        s5.buf = s4.buf;
        s5.execute(&mem, &reg);
    }
    */

    printf("%d\n", reg.get(10) & (1 << 8) - 1);

    return 0;
}