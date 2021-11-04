#ifndef ECE643_LIBHWIO_FILEDESCRIPTOR_HPP
#define ECE643_LIBHWIO_FILEDESCRIPTOR_HPP

#include <ece643/libhwio/IPerformSyscalls.hpp>

namespace ece643 {
    namespace libhwio {
        class FileDescriptor : private IPerformSyscalls {
            public:
                FileDescriptor(int fd) noexcept;
                FileDescriptor(FileDescriptor &&move) noexcept;
                ~FileDescriptor() noexcept;

                FileDescriptor &operator =(int fd) noexcept;
                FileDescriptor &operator =(FileDescriptor &&move) noexcept;

                operator bool() const noexcept;
                operator int() const noexcept;

                void close() noexcept;

            private:
                int fd;
        };
    }
}

#endif
