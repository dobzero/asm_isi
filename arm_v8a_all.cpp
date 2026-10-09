#include "arm_v8a_all.h"

#include <stdexcept>

namespace asm_isi {
    std::vector<uint8_t> ArmV8A_All::read_asm_list() const {
        std::vector<uint8_t> bytes_asm;
        bytes_asm.reserve(asm_buffer_stream.size() * 4);
        if (!fix_branches_at.empty()) {
            throw std::logic_error("some labels is unreachable");
        }

        for (const auto &inst_arm : asm_buffer_stream) {
            bytes_asm.emplace_back(inst_arm&0xFF);
            bytes_asm.emplace_back((inst_arm>>8)&0xFF);
            bytes_asm.emplace_back((inst_arm>>16)&0xFF);
            bytes_asm.emplace_back((inst_arm>>24)&0xFF);
        }
        return bytes_asm;
    }

    void ArmV8A_All::label(const std::string &label) {
        labels.emplace(label, get_pc());

        for (auto fix_it = fix_branches_at.begin(); fix_it != fix_branches_at.end(); ) {
            const auto label_it = labels.find(fix_it->first);
            if (label_it == labels.end()) {
                ++fix_it;
                continue;
            }
            asm_buffer_stream[fix_it->second / 4] = ArmV8A_Functions::__B(fix_it->second, label_it->second);
            fix_it = fix_branches_at.erase(fix_it);
        }
    }
}
