#ifndef ECE643_LIBBUSINESS_BUTTONHANDLER_HPP
#define ECE643_LIBBUSINESS_BUTTONHANDLER_HPP

#include <chrono>
#include <ece643/libhwio/Interrupt.hpp>

namespace ece643 {
    namespace libbusiness {
        class ButtonHandler {
            public:
                ButtonHandler(libhwio::Interrupt &irq);
                ~ButtonHandler() noexcept(false);

                bool poll();

            private:
                libhwio::Interrupt &irq;
                std::chrono::steady_clock::time_point lastIRQ[4];
        };
    }
}

#endif
