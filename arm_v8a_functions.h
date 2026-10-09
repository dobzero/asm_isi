#pragma once

namespace asm_isi {

struct ArmV8A_Functions {
    static uint32_t __RET() {
        return 0xD65F03C0;
    }
    static uint32_t __B(const uint64_t pc, const uint64_t target) {
        const intptr_t offset_bytes = static_cast<intptr_t>(target - pc);
        const intptr_t offset_imm = offset_bytes / 4;
        const uint32_t imm26 = static_cast<uint32_t>(offset_imm & 0x03FFFFFF);
        return 0x14000000 | imm26;
    }
};
}
