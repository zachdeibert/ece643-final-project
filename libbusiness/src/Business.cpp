#include <chrono>
#include <ece643/libbusiness/Business.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;

Business::Business() : buttons(hwio.interrupt), vncClient(hwio.vga) {
}

Business::~Business() noexcept(false) {
}

void Business::run() {
    hwio.interrupt.poll(0xFFFFFFFF);
    hwio.interrupt.enable(0x000003FF);
    int counter = 0;
    int switches = 0;
    while (buttons.poll()) {
        switches ^= hwio.interrupt.poll(0x000003FF);
        hwio.led.set(switches, (counter / 600) % 12, (counter / 10) % 60, ((counter / 600) % 24) >= 12);
        vncClient.poll(microseconds(10000));
        ++counter;
    }
    hwio.interrupt.disable(0x000003FF);
}
