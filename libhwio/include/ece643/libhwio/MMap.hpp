#ifndef ECE643_LIBHWIO_MMAP_HPP
#define ECE643_LIBHWIO_MMAP_HPP

#include <stdint.h>
#include <ece643/libhwio/FileDescriptor.hpp>
#include <ece643/libhwio/IPerformSyscalls.hpp>

namespace ece643 {
    namespace libhwio {
        class MMap : private IPerformSyscalls {
            public:
                MMap(uint32_t addr, uint32_t len) noexcept;
                MMap(MMap &&move) noexcept;
                ~MMap() noexcept;

                MMap &operator =(MMap &&move) noexcept;

                operator void *() noexcept;
                operator const void *() const noexcept;

                void *operator +(uint32_t offset) noexcept;
                const void *operator +(uint32_t offset) const noexcept;

                uint32_t &operator [](uint32_t offset) noexcept;
                const uint32_t &operator [](uint32_t offset) const noexcept;

            private:
                FileDescriptor fd;
                void *virt;
                uint32_t len;
        };
    }
}

#endif
