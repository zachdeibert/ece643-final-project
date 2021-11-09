#ifndef ECE643_LIBBUSINESS_BUTTONHANDLER_HPP
#define ECE643_LIBBUSINESS_BUTTONHANDLER_HPP

#include <chrono>
#include <ece643/libhwio/Interrupt.hpp>

namespace ece643 {
    namespace libbusiness {
        class ButtonHandler {
            public:
                ButtonHandler(libhwio::Interrupt &irq) noexcept;
                ~ButtonHandler() noexcept;

                bool poll() noexcept;

            private:
                libhwio::Interrupt &irq;
                std::chrono::steady_clock::time_point lastIRQ[4];
        };
    }
}

#endif
