#ifndef ECE643_HWIO_DBG_EXCEPTIONDEBUGGER_HPP
#define ECE643_HWIO_DBG_EXCEPTIONDEBUGGER_HPP

#include <functional>

namespace ece643 {
    namespace hwiodbg {
        class ExceptionDebugger {
            public:
                static void printExceptions(const std::function<void()> &func);
        };
    }
}

#endif
