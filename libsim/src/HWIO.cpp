#include <ece643/libhwio/HWIO.hpp>

using namespace ece643::libhwio;

HWIO::HWIO() noexcept : mmap(0, 0), interrupt(mmap), led(mmap), ps2(mmap), vga(mmap) {
}

HWIO::HWIO(HWIO &&move) noexcept : mmap(0, 0), interrupt(mmap), led(mmap), ps2(mmap), vga(mmap) {
}

HWIO &HWIO::operator =(HWIO &&move) noexcept {
    return *this;
}
