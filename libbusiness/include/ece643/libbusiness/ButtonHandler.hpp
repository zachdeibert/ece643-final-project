#ifndef ECE643_LIBBUSINESS_BUTTONHANDLER_HPP
#define ECE643_LIBBUSINESS_BUTTONHANDLER_HPP

#include <chrono>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Interrupt.hpp>

namespace ece643 {
    namespace libbusiness {
        class ButtonHandler {
            public:
                ButtonHandler(VNCClient &vnc, libhwio::Interrupt &irq);
                ~ButtonHandler() noexcept(false);

                bool poll();
                bool attack() const noexcept;

            private:
                VNCClient &vnc;
                libhwio::Interrupt &irq;
                std::chrono::steady_clock::time_point lastIRQ[4];
                bool down[4];
        };
    }
}

#endif
