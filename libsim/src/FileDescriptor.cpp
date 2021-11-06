#include <unistd.h>
#include <ece643/libhwio/FileDescriptor.hpp>

using namespace ece643::libhwio;

FileDescriptor::FileDescriptor(int fd) noexcept : fd(fd) {
}

FileDescriptor::FileDescriptor(FileDescriptor &&move) noexcept : fd(move.fd) {
    move.fd = -1;
}

FileDescriptor::~FileDescriptor() noexcept {
    close();
}

FileDescriptor &FileDescriptor::operator =(int fd) noexcept {
    close();
    this->fd = fd;
    return *this;
}

FileDescriptor &FileDescriptor::operator =(FileDescriptor &&move) noexcept {
    close();
    this->fd = move.fd;
    move.fd = -1;
    return *this;
}

FileDescriptor::operator bool() const noexcept {
    return fd >= 0;
}

FileDescriptor::operator int() const noexcept {
    return fd;
}

void FileDescriptor::close() noexcept {
    if (*this) {
        check(::close(fd));
        fd = -1;
    }
}
