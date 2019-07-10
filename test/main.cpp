#include <iostream>
#include "Instruction.h"
#include "MemoryController.h"
#include "RegisterController.h"
#include <stdexcept>
#include "Stage.h"
#include <iomanip>

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

IF s1;
ID s2;
EX s3;
MEM s4;
WB s5;

bool stop_IF;
bool need_jump;
bool need_pause;

MemoryController mem;
RegisterController reg;

bool flow() {
    if (s1.buf.type == INVALID && s2.buf.type == INVALID
    && s3.buf.type == INVALID && s4.buf.type == INVALID
    && s5.buf.type == INVALID && stop_IF) return false;

    if (false) {
        std::cout << std::hex << std::setw(10) << s1.buf.ins;
        std::cout << std::hex << std::setw(10) << s2.buf.ins;
        std::cout << std::hex << std::setw(10) << s3.buf.ins;
        std::cout << std::hex << std::setw(10) << s4.buf.ins;
        std::cout << std::hex << std::setw(10) << s5.buf.ins << std::endl;
//        std::cout << stop_IF << std:: endl;
    }

    need_jump = false;
    s5.execute(&mem, &reg, need_jump);
    s5.reset();
    if (need_jump) {
        s4.reset();
        s3.reset();
        s2.reset();
        s1.reset();
        stop_IF = false;
        reg.unlock_all();
        return true;
    }

    if (s5.buf.type == INVALID) {
        need_pause = false;
        s4.execute(&mem, &reg, need_pause);
        if (need_pause) ;
        else {
            s5.buf = s4.buf;
            s4.reset();
        }
    }

    if (s4.buf.type == INVALID) {
        need_pause = false;
        s3.execute(&mem, &reg, need_pause);
        if (need_pause) ;
        else {
            s4.buf = s3.buf;
            s3.reset();
        }
    }

    if (s3.buf.type == INVALID) {
        need_pause = false;
        s2.execute(&mem, &reg, need_pause);
        if (need_pause) ;
        else {
            s3.buf = s2.buf;
            s2.reset();
        }
    }

    if (stop_IF) return true;

    if (s2.buf.ins == 0) {
        need_pause = false;
        s1.execute(&mem, &reg, need_pause);
        if (need_pause) ;
        else {
            s2.buf = s1.buf;
            s1.reset();
        }
    }

    if (s2.buf.ins == 0x00c68223) stop_IF = true, s2.reset();

    return true;
}

int main() {
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

    s1.reset(); s2.reset(); s3.reset(); s4.reset(); s5.reset(); stop_IF = false;

    while (flow());

    printf("%d\n", reg.get(10) & (1 << 8) - 1);

    return 0;
}