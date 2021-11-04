#ifndef ECE643_HWIO_QUITEXCEPTION_HPP
#define ECE643_HWIO_QUITEXCEPTION_HPP

#include <exception>

namespace ece643 {
    namespace hwiodbg {
        class QuitException : public std::exception {
        };
    }
}

#endif
