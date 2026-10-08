#pragma once

#include "types.h"
namespace asm_isi {

struct ArmV8A_Math {
    static uint32_t __MRS(const uint8_t rt, const uint8_t op0, const uint8_t op1, const uint8_t crn, const uint8_t crm, const uint8_t op2) {
        return 0xD5200000 |
            (op0 << 19) | (op1 << 16) | (crn << 12) | (crm << 8) | (op2 << 5) | rt;
    }

    static uint32_t __NOP() {
        return 0xD503201F;
    }
};
}
