#include <ece643/libhwio/FileDescriptor.hpp>

using namespace ece643::libhwio;

FileDescriptor::FileDescriptor(int fd) noexcept {
}

FileDescriptor::FileDescriptor(FileDescriptor &&move) noexcept {
}

FileDescriptor::~FileDescriptor() noexcept {
}

FileDescriptor &FileDescriptor::operator =(int fd) noexcept {
    return *this;
}

FileDescriptor &FileDescriptor::operator =(FileDescriptor &&move) noexcept {
    return *this;
}

FileDescriptor::operator bool() const noexcept {
    return false;
}

FileDescriptor::operator int() const noexcept {
    return 0;
}

void FileDescriptor::close() noexcept {
}
