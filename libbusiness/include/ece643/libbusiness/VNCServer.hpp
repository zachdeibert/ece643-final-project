#ifndef ECE643_LIBBUSINESS_VNCSERVER_HPP
#define ECE643_LIBBUSINESS_VNCSERVER_HPP

#include <stdint.h>
#include <sys/types.h>
#include <ece643/libhwio/IPerformSyscalls.hpp>

namespace ece643 {
    namespace libbusiness {
        class VNCServer : private libhwio::IPerformSyscalls {
            public:
                static const uint16_t vncPort = 5901;

                VNCServer() noexcept;
                ~VNCServer() noexcept;

            private:
                pid_t server;
        };
    }
}

#endif
