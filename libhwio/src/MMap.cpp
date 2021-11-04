#include <fcntl.h>
#include <stdint.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <utility>
#include <ece643/libhwio/MMap.hpp>

using namespace ece643::libhwio;

MMap::MMap(uint32_t addr, uint32_t len) noexcept : fd(open("/dev/mem", O_RDWR | O_SYNC)), len(len) {
    check(fd);
    check(virt = mmap(nullptr, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, addr));
}

MMap::MMap(MMap &&move) noexcept : fd(std::move(move.fd)), virt(move.virt), len(move.len) {
}

MMap::~MMap() noexcept {
    if (fd) {
        check(munmap(virt, len));
    }
}

MMap &MMap::operator =(MMap &&move) noexcept {
    fd = std::move(move.fd);
    virt = move.virt;
    len = move.len;
    move.virt = nullptr;
    move.len = 0;
    return *this;
}

MMap::operator void *() noexcept {
    return virt;
}

MMap::operator const void *() const noexcept {
    return virt;
}

void *MMap::operator +(uint32_t offset) noexcept {
    return ((uint8_t *) virt) + offset;
}

const void *MMap::operator +(uint32_t offset) const noexcept {
    return ((const uint8_t *) virt) + offset;
}

uint32_t &MMap::operator [](uint32_t offset) noexcept {
    return *(uint32_t *) (*this + offset);
}

const uint32_t &MMap::operator [](uint32_t offset) const noexcept {
    return *(const uint32_t *) (*this + offset);
}
