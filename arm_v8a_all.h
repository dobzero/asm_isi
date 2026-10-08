#pragma once
#include <cstdint>

#include "arm_v8a_math.h"
namespace asm_isi {

struct ArmV8A_All : protected FixedBufferSizeEmitter<uint32_t> {
    // https://www.scs.stanford.edu/~zyedidia/arm64/nop.html
    uint32_t NOP() {
        return emitter(ArmV8A_Math::__NOP());
    }

    uint32_t MRS(const uint8_t rt, const uint8_t op0, const uint8_t op1, const uint8_t crn, const uint8_t crm, const uint8_t op2) {
        return emitter(ArmV8A_Math::__MRS(rt, op0, op1, crn, crm, op2));
    }
    auto read_asm_list() const {
        std::vector<uint8_t> bytes_asm;
        bytes_asm.reserve(asm_buffer_stream.size() * 4);

        for (const auto &inst_arm : asm_buffer_stream) {
            bytes_asm.emplace_back(inst_arm&0xFF);
            bytes_asm.emplace_back((inst_arm>>8)&0xFF);
            bytes_asm.emplace_back((inst_arm>>16)&0xFF);
            bytes_asm.emplace_back((inst_arm>>24)&0xFF);
        }
        return bytes_asm;
    }
};
}
