#pragma once
#include <unordered_map>
#include <cstdint>
#include <string>

#include "arm_v8a_functions.h"
#include "arm_v8a_math.h"
namespace asm_isi {

struct ArmV8A_All : protected FixedBufferSize<uint32_t> {
    // https://www.scs.stanford.edu/~zyedidia/arm64/nop.html
    uint32_t NOP() {
        return write_inst(ArmV8A_Math::__NOP());
    }
    uint32_t RET() {
        return write_inst(ArmV8A_Functions::__RET());
    }
    uint32_t B(const std::string &label) {
        if (labels.contains(label)) {
            return write_inst(ArmV8A_Functions::__B(get_pc(), labels[label]));
        }
        fix_branches_at.emplace_back(label, get_pc());
        return write_inst(0);
    }

    uint32_t MRS(const uint8_t rt, const uint8_t op0, const uint8_t op1, const uint8_t crn, const uint8_t crm, const uint8_t op2) {
        return write_inst(ArmV8A_Math::__MRS(rt, op0, op1, crn, crm, op2));
    }
    std::vector<uint8_t> read_asm_list() const;

    uint64_t get_pc() const {
        return asm_buffer_stream.size() * 4;
    }
    void label(const std::string &label);
    std::unordered_map<std::string, uint64_t> labels;
    std::vector<std::pair<std::string, uint64_t>> fix_branches_at;
};
}
