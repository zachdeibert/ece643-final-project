#ifndef ECE643_LIBBUSINESS_VNCCLIENT_HPP
#define ECE643_LIBBUSINESS_VNCCLIENT_HPP

#include <chrono>
#include <stdint.h>
#include <ece643/libhwio/IPerformSyscalls.hpp>
#include <ece643/libhwio/FileDescriptor.hpp>
#include <ece643/libhwio/VGA.hpp>

namespace ece643 {
    namespace libbusiness {
        class VNCClient : private libhwio::IPerformSyscalls {
            public:
                VNCClient(libhwio::VGA &vga) noexcept;

                void poll(std::chrono::microseconds maxDelay);

                void key(bool down, uint32_t code);
                void mouse(uint8_t buttons, uint16_t x, uint16_t y);

            private:
                libhwio::FileDescriptor fd;
                libhwio::VGA &vga;
                int rectsLeft;
                int rectBytesLeft;
                uint8_t *buf;
        };
    }
}

#endif
