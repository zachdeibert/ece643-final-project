#ifndef ECE643_LIBBUSINESS_BUSINESS_HPP
#define ECE643_LIBBUSINESS_BUSINESS_HPP

#include <ece643/libbusiness/ButtonHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libbusiness/VNCServer.hpp>
#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace libbusiness {
        class Business {
            public:
                Business();
                ~Business() noexcept(false);

                void run();

            private:
                libhwio::HWIO hwio;
                ButtonHandler buttons;
                VNCServer vncServer;
                VNCClient vncClient;
        };
    }
}

#endif
