#ifndef ECE643_LIBHWIO_LED_HPP
#define ECE643_LIBHWIO_LED_HPP

#include <ece643/libhwio/MMap.hpp>

namespace ece643 {
    namespace libhwio {
        class LED {
            public:
                LED(MMap &mmap) noexcept;

                void set(int leds, int hours, int minutes, bool pm);

            private:
                MMap *mmap;
        };
    }
}

#endif
