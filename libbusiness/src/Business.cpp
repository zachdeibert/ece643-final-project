#include <chrono>
#include <ece643/libbusiness/Business.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;

Business::Business() noexcept : vncClient(hwio.vga) {
}

void Business::run() noexcept {
    hwio.accelerometer.enable();
    hwio.accelerometer.disable();
    int counter = 0;
    while (true) {
        hwio.led.set(++counter & 0x3FF, (counter / 600) % 12, (counter / 10) % 60, ((counter / 600) % 24) >= 12);
        vncClient.poll(microseconds(10000));
    }
}
