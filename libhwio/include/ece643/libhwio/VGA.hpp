#ifndef ECE643_LIBHWIO_VGA_HPP
#define ECE643_LIBHWIO_VGA_HPP

#include <stdint.h>
#include <ece643/libhwio/MMap.hpp>

namespace ece643 {
    namespace libhwio {
        class VGA {
            public:
                static const int width = 640;
                static const int height = 480;
                static const uint32_t maxPacket = 0x200000;

                VGA(MMap &mmap) noexcept;

                void *buffer();
                void write(int x, int y, int width, int height, void *data);

            private:
                MMap *mmap;
        };
    }
}

#endif
