#pragma once
#include <cstdint>

#include "types.h"
namespace asm_isi {

class ArmV8_A : protected FixedBufferSizeEmitter<uint32_t> {
public:
    // https://www.scs.stanford.edu/~zyedidia/arm64/nop.html
    uint32_t NOP() {
        return emitter(__NOP());
    }

    static uint32_t __MRS(const uint8_t rt, const uint8_t op0, const uint8_t op1, const uint8_t crn, const uint8_t crm, const uint8_t op2) {
        return 0xD5200000 |
            (op0 << 19) | (op1 << 16) | (crn << 12) | (crm << 8) | (op2 << 5) | rt;
    }

    static uint32_t __NOP() {
        return 0xD503201F;
    }
    [[nodiscard]] auto get_asm() const {
        return std::span{reinterpret_cast<const uint8_t *>(asm_buffer_stream.data()), asm_buffer_stream.size() * 4};
    }
};
}
