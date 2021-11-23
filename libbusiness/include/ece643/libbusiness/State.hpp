#ifndef ECE643_LIBBUSINESS_STATE_HPP
#define ECE643_LIBBUSINESS_STATE_HPP

#include <stdint.h>

namespace ece643 {
    namespace libbusiness {
        class State {
            public:
                virtual operator uint64_t() const = 0;
        };
    }
}

#endif
