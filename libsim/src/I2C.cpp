#include <stdint.h>
#include <ece643/libhwio/I2C.hpp>
#include <ece643/libsim/JavaEnv.hpp>

using namespace ece643::libhwio;
using namespace ece643::libsim;

I2C::I2C(uint8_t addr) noexcept : fd(0) {
    JavaEnv::init(this);
}

I2C::I2C(I2C &&move) noexcept : fd(0) {
    JavaEnv::init(this);
}

I2C &I2C::operator =(I2C &&move) noexcept {
    return *this;
}

uint8_t I2C::read(uint8_t addr) noexcept {
    return 0;
}

void I2C::read(uint8_t addr, uint8_t *data, uint8_t len) noexcept {
    int *id = (int *) data;
    if (addr == 0) {
        fd = *id;
    } else {
        *id = fd;
    }
}

void I2C::write(uint8_t addr, uint8_t value) noexcept {
}
