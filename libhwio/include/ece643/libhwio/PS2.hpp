#ifndef ECE643_LIBHWIO_PS2_HPP
#define ECE643_LIBHWIO_PS2_HPP

#include <chrono>
#include <string>
#include <ece643/libhwio/MMap.hpp>

namespace ece643 {
    namespace libhwio {
        class PS2 {
            public:
                static const std::chrono::microseconds minPeriod;

                PS2(MMap &mmap) noexcept;

                std::string poll();

            private:
                MMap *mmap;
        };
    }
}

#endif
