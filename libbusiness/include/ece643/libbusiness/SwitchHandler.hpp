#ifndef ECE643_LIBBUSINESS_SWITCHHANDLER_HPP
#define ECE643_LIBBUSINESS_SWITCHHANDLER_HPP

#include <stdint.h>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Interrupt.hpp>

namespace ece643 {
    namespace libbusiness {
        class SwitchHandler {
            public:
                SwitchHandler(VNCClient &vnc, libhwio::Interrupt &irq);
                ~SwitchHandler() noexcept(false);

                void poll();
                int leds() const noexcept;

            private:
                VNCClient &vnc;
                libhwio::Interrupt &irq;
                int led;
                uint32_t down;
        };
    }
}

#endif
