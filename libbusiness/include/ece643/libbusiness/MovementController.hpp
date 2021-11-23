#ifndef ECE643_LIBBUSINESS_MOVEMENTCONTROLLER_HPP
#define ECE643_LIBBUSINESS_MOVEMENTCONTROLLER_HPP

#include <stdint.h>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Accelerometer.hpp>

namespace ece643 {
    namespace libbusiness {
        class MovementController {
            public:
                MovementController(VNCClient &vnc, libhwio::Accelerometer &accel);
                ~MovementController() noexcept(false);

                void poll();

            private:
                VNCClient &vnc;
                libhwio::Accelerometer &accel;
                uint32_t sdown;
                uint32_t xdown;
                uint32_t ydown;
                uint32_t zdown;
        };
    }
}

#endif
