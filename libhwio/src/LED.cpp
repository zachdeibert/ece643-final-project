#include <stdexcept>
#include <ece643/libhwio/LED.hpp>
#include <ece643/libhwio/MMap.hpp>

using namespace std;
using namespace ece643::libhwio;

LED::LED(MMap &mmap) noexcept : mmap(&mmap) {
}

void LED::set(int leds, int hours, int minutes, bool pm) {
    if ((leds & ~0x3FF) || hours < 0 || hours >= 12 || minutes < 0 || minutes >= 60) {
        throw invalid_argument("LED::set");
    }
    (*mmap)[0x200020] = leds | (minutes << 16) | (hours << 24) | (pm ? (1 << 28) : 0);
}
