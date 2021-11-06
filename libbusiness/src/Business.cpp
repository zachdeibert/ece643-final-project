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
    while (true) {
        vncClient.poll(microseconds(10000));
    }
}
