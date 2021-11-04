#include <fcntl.h>
#include <i2c/smbus.h>
#include <linux/i2c-dev.h>
#include <stdint.h>
#include <string.h>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utility>
#include <ece643/libhwio/I2C.hpp>

using namespace ece643::libhwio;

I2C::I2C(uint8_t addr) noexcept : addr(addr), fd(open("/dev/i2c-0", O_RDWR)) {
    check(fd);
}

I2C::I2C(I2C &&move) noexcept : addr(move.addr), fd(std::move(move.fd)) {
}

I2C &I2C::operator =(I2C &&move) noexcept {
    addr = move.addr;
    fd = std::move(move.fd);
    return *this;
}

uint8_t I2C::read(uint8_t addr) noexcept {
    uint8_t val;
    read(addr, &val, 1);
    return val;
}

void I2C::read(uint8_t addr, uint8_t *data, uint8_t len) noexcept {
    i2c_msg msgs[2];
    memset(msgs, 0, sizeof(msgs));
    msgs[0].addr = addr;
    msgs[0].buf = &addr;
    msgs[0].len = 1;
    msgs[1].buf = data;
    msgs[1].flags = I2C_M_RD | I2C_M_NOSTART;
    msgs[1].len = len;
    i2c_rdwr_ioctl_data msgset;
    memset(&msgset, 0, sizeof(msgset));
    msgset.msgs = msgs;
    msgset.nmsgs = sizeof(msgs) / sizeof(msgs[0]);
    check(ioctl(fd, I2C_RDWR, &msgset));
}

void I2C::write(uint8_t addr, uint8_t value) noexcept {
    i2c_msg msgs[2];
    memset(msgs, 0, sizeof(msgs));
    msgs[0].addr = addr;
    msgs[0].buf = &addr;
    msgs[0].len = 1;
    msgs[1].buf = &value;
    msgs[1].flags = I2C_M_NOSTART;
    msgs[1].len = 1;
    i2c_rdwr_ioctl_data msgset;
    memset(&msgset, 0, sizeof(msgset));
    msgset.msgs = msgs;
    msgset.nmsgs = sizeof(msgs) / sizeof(msgs[0]);
    check(ioctl(fd, I2C_RDWR, &msgset));
}
