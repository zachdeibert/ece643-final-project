#include <array>
#include <chrono>
#include <stdint.h>
#include <utility>
#include <ece643/libhwio/Accelerometer.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libhwio;

const microseconds Accelerometer::minPeriod = microseconds(1000000 / 50);

Accelerometer::Accelerometer() noexcept : i2c(0b01010011) {
    i2c.write(0x31, 0x08);
    i2c.write(0x2C, 0x09);
    i2c.write(0x2E, 0x80);
    disable();
}

Accelerometer::Accelerometer(Accelerometer &&move) noexcept : i2c(std::move(move.i2c)) {
}

Accelerometer &Accelerometer::operator =(Accelerometer &&move) noexcept {
    i2c = std::move(move.i2c);
    return *this;
}

void Accelerometer::enable() noexcept {
    i2c.write(0x2D, 0x08);
}

void Accelerometer::disable() noexcept {
    i2c.write(0x2D, 0x00);
}

bool Accelerometer::ready() noexcept {
    return i2c.read(0x30) & 0x80;
}

array<int16_t, 3> Accelerometer::read() noexcept {
    uint8_t buffer[6];
    i2c.read(0x32, buffer, sizeof(buffer));
    array<int16_t, 3> data;
    data[0] = (buffer[1] << 8) | buffer[0];
    data[1] = (buffer[3] << 8) | buffer[2];
    data[2] = (buffer[5] << 8) | buffer[4];
    return data;
}
