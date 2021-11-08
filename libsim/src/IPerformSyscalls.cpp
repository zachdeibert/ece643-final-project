#include <errno.h>
#include <exception>
#include <iostream>
#include <string.h>
#include <ece643/libhwio/IPerformSyscalls.hpp>

using namespace std;
using namespace ece643::libhwio;

void IPerformSyscalls::check(int ret) noexcept {
    if (ret < 0) {
        int e = errno;
        cerr << "Syscall returned failure: " << strerror(e) << endl;
        terminate();
    }
}

void IPerformSyscalls::check(void *ret) noexcept {
    if (-1 == (int) (long) ret) {
        int e = errno;
        cerr << "Syscall returned failure: " << strerror(e) << endl;
        terminate();
    }
}
