#include <stdint.h>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/Interrupt.hpp>

using namespace ece643::libhwio;

Interrupt::Interrupt(MMap &mmap) noexcept : mask(0), mmap(&mmap) {
}

void Interrupt::enable(uint32_t mask) noexcept {
    (*mmap)[0x200004] = this->mask |= mask;
}

void Interrupt::disable(uint32_t mask) noexcept {
    (*mmap)[0x200004] = this->mask &= ~mask;
    poll(~this->mask);
}

uint32_t Interrupt::poll(uint32_t mask) noexcept {
    return (*mmap)[0x200008] = (*mmap)[0x200000] & mask;
}