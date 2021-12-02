#ifndef ECE643_LIBBUSINESS_MOVEMENTCONTROLLER_HPP
#define ECE643_LIBBUSINESS_MOVEMENTCONTROLLER_HPP

#include <chrono>
#include <stdint.h>
#include <ece643/libbusiness/ButtonHandler.hpp>
#include <ece643/libbusiness/SwitchHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Accelerometer.hpp>

namespace ece643 {
    namespace libbusiness {
        class MovementController {
            public:
                MovementController(VNCClient &vnc, libhwio::Accelerometer &accel, ButtonHandler &buttons, SwitchHandler &switches);
                ~MovementController() noexcept(false);

                void poll();

            private:
                enum State {
                    PauseDown,
                    PauseUp,
                    MouseSet,
                    ResumeDown,
                    ResumeUp,
                    Normal
                };

                VNCClient &vnc;
                libhwio::Accelerometer &accel;
                ButtonHandler &buttons;
                SwitchHandler &switches;
                State state;
                std::chrono::steady_clock::time_point nextState;
                uint32_t sdown;
                uint32_t xdown;
                uint32_t ydown;
                uint32_t zdown;
                uint8_t lastBtn;
                bool moved;
                uint16_t mx;
                uint16_t my;
        };
    }
}

#endif
