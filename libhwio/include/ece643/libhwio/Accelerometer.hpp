#ifndef ECE643_LIBHWIO_ACCELEROMETER_HPP
#define ECE643_LIBHWIO_ACCELEROMETER_HPP

#include <array>
#include <chrono>
#include <stdint.h>
#include <ece643/libhwio/I2C.hpp>

namespace ece643 {
    namespace libhwio {
        class Accelerometer {
            public:
                static const std::chrono::microseconds minPeriod;

                Accelerometer() noexcept;
                Accelerometer(Accelerometer &&move) noexcept;

                Accelerometer &operator =(Accelerometer &&move) noexcept;

                void enable() noexcept;
                void disable() noexcept;
                bool ready() noexcept;
                std::array<int16_t, 3> read() noexcept;

            private:
                I2C i2c;
        };
    }
}

#endif
