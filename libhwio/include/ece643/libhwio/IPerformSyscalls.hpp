#ifndef ECE643_LIBHWIO_IPERFORMSYSCALLS_HPP
#define ECE643_LIBHWIO_IPERFORMSYSCALLS_HPP

namespace ece643 {
    namespace libhwio {
        class IPerformSyscalls {
            protected:
                static void check(int ret) noexcept;
                static void check(void *ret) noexcept;
        };
    }
}

#endif
