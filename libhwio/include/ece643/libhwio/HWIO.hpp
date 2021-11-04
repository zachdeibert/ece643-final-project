#ifndef ECE643_LIBHWIO_HWIO_HPP
#define ECE643_LIBHWIO_HWIO_HPP

#include <ece643/libhwio/Accelerometer.hpp>
#include <ece643/libhwio/Interrupt.hpp>
#include <ece643/libhwio/LED.hpp>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/PS2.hpp>
#include <ece643/libhwio/VGA.hpp>

namespace ece643 {
    namespace libhwio {
        class HWIO {
            public:
                HWIO() noexcept;
                HWIO(HWIO &&move) noexcept;
                HWIO &operator =(HWIO &&move) noexcept;

            private:
                MMap mmap;

            public:
                Accelerometer accelerometer;
                Interrupt interrupt;
                LED led;
                PS2 ps2;
                VGA vga;
        };
    }
}

#endif
