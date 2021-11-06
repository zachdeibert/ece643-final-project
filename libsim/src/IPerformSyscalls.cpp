#include <errno.h>
#include <exception>
#include <iostream>
#include <string.h>
#include <ece643/libhwio/IPerformSyscalls.hpp>

using namespace std;
using namespace ece643::libhwio;

void IPerformSyscalls::check(int ret) noexcept {
    if (ret == -1) {
        int e = errno;
        cerr << "Syscall returned failure: " << strerror(e) << endl;
        terminate();
    }
}

void IPerformSyscalls::check(void *ret) noexcept {
    check((int) (long) ret);
}
