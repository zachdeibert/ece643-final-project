#ifndef ECE643_LIBHWIO_I2C_HPP
#define ECE643_LIBHWIO_I2C_HPP

#include <stdint.h>
#include <ece643/libhwio/FileDescriptor.hpp>
#include <ece643/libhwio/IPerformSyscalls.hpp>

namespace ece643 {
    namespace libhwio {
        class I2C : private IPerformSyscalls {
            public:
                I2C(uint8_t addr) noexcept;
                I2C(I2C &&move) noexcept;

                I2C &operator =(I2C &&move) noexcept;

                uint8_t read(uint8_t addr) noexcept;
                void read(uint8_t addr, uint8_t *data, uint8_t len) noexcept;
                void write(uint8_t addr, uint8_t value) noexcept;

            private:
                uint8_t addr;
                FileDescriptor fd;
        };
    }
}

#endif
