#include <chrono>
#include <string.h>
#include <string>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/PS2.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libhwio;

const microseconds PS2::minPeriod = microseconds(1000000 * 11 / 16768);

PS2::PS2(MMap &mmap) noexcept : mmap(&mmap) {
}

string PS2::poll() {
    uint8_t buffer[0x10];
    memcpy(buffer, *mmap + 0x100010, sizeof(buffer));
    (*mmap)[0x100010] = buffer[1];
    string buf;
    buf.reserve(sizeof(buffer) - 2);
    for (uint8_t i = buffer[0]; i != buffer[1]; i = (i + 1) % (sizeof(buffer) - 2)) {
        buf.push_back((char) buffer[i]);
    }
    return buf;
}
