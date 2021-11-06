#include <stdint.h>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace ece643::libhwio;
using namespace ece643::libsim;

MMap::MMap(uint32_t addr, uint32_t len) noexcept : fd(-1) {
    JavaEnv::init(this);
}

MMap::MMap(MMap &&move) noexcept : fd(-1) {
    JavaEnv::init(this);
}

MMap::~MMap() noexcept {
}

MMap &MMap::operator =(MMap &&move) noexcept {
    return *this;
}

MMap::operator void *() noexcept {
    return &virt;
}

MMap::operator const void *() const noexcept {
    return &virt;
}

void *MMap::operator +(uint32_t offset) noexcept {
    return nullptr;
}

const void *MMap::operator +(uint32_t offset) const noexcept {
    return nullptr;
}

uint32_t &MMap::operator [](uint32_t offset) noexcept {
    return len;
}

const uint32_t &MMap::operator [](uint32_t offset) const noexcept {
    return len;
}
