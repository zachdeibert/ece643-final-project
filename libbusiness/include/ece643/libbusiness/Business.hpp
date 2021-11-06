#ifndef ECE643_LIBBUSINESS_BUSINESS_HPP
#define ECE643_LIBBUSINESS_BUSINESS_HPP

#include <ece643/libhwio/HWIO.hpp>

namespace ece643 {
    namespace libbusiness {
        class Business {
            public:
                void run() noexcept;

            private:
                libhwio::HWIO hwio;
        };
    }
}

#endif
