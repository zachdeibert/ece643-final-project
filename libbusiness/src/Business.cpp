#include <chrono>
#include <stdint.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libbusiness/State.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;

Business::Business(State &state) : state(state), buttons(hwio.interrupt), vncClient(hwio.vga) {
}

Business::~Business() noexcept(false) {
}

void Business::run() {
    hwio.interrupt.poll(0xFFFFFFFF);
    hwio.interrupt.enable(0x000003FF);
    int switches = 0;
    while (buttons.poll()) {
        uint64_t state = this->state;
        if (state == 0xFFFFFF) {
            break;
        }
        int hours = state / 1000;
        int minutes = (state - hours * 1000) * 3 / 50;
        hwio.led.set(switches, (hours + 6) % 12, minutes, (hours + 6) % 24 >= 12);
        switches ^= hwio.interrupt.poll(0x000003FF);
        vncClient.poll(microseconds(10000));
    }
    hwio.interrupt.disable(0x000003FF);
}
