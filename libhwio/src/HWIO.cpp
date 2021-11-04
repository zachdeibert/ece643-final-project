#include <utility>
#include <ece643/libhwio/HWIO.hpp>

using namespace ece643::libhwio;

HWIO::HWIO() noexcept : mmap(0xC0000000, 0x200024), interrupt(mmap), led(mmap), ps2(mmap), vga(mmap) {
}

HWIO::HWIO(HWIO &&move) noexcept : mmap(std::move(move.mmap)), accelerometer(std::move(move.accelerometer)), interrupt(mmap), led(mmap), ps2(mmap), vga(mmap) {
}

HWIO &HWIO::operator =(HWIO &&move) noexcept {
    mmap = std::move(move.mmap);
    accelerometer = std::move(move.accelerometer);
    interrupt = Interrupt(mmap);
    led = LED(mmap);
    ps2 = PS2(mmap);
    vga = VGA(mmap);
    return *this;
}
