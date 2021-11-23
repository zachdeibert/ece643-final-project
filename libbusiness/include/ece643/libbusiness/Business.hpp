#ifndef ECE643_LIBBUSINESS_BUSINESS_HPP
#define ECE643_LIBBUSINESS_BUSINESS_HPP

#include <ece643/libbusiness/ButtonHandler.hpp>
#include <ece643/libbusiness/MovementController.hpp>
#include <ece643/libbusiness/State.hpp>
#include <ece643/libbusiness/SwitchHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libbusiness/VNCServer.hpp>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace libbusiness {
        class Business {
            public:
                Business(State &state);
                ~Business() noexcept(false);

                void run();

            private:
                State &state;
                VNCServer vncServer;
                VNCClient vncClient;
                libhwio::HWIO hwio;
                ButtonHandler buttons;
                SwitchHandler switches;
                MovementController movement;
        };
    }
}

#endif
