#ifndef ECE643_LIBHWIO_INTERRUPT_HPP
#define ECE643_LIBHWIO_INTERRUPT_HPP

#include <stdint.h>
#include <ece643/libhwio/MMap.hpp>

namespace ece643 {
    namespace libhwio {
        class Interrupt {
            public:
                Interrupt(MMap &mmap) noexcept;

                void enable(uint32_t mask) noexcept;
                void disable(uint32_t mask) noexcept;
                uint32_t poll(uint32_t mask) noexcept;

            private:
                uint32_t mask;
                MMap *mmap;
        };
    }
}

#endif
