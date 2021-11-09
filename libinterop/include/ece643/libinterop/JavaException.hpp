#ifndef ECE643_LIBINTEROP_JAVAEXCEPTION_HPP
#define ECE643_LIBINTEROP_JAVAEXCEPTION_HPP

#include <exception>

namespace ece643 {
    namespace libinterop {
        class JavaException : public std::exception {
            public:
                JavaException() noexcept;
        };
    }
}

#endif
