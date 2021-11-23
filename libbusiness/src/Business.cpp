#include <chrono>
#include <stdint.h>
#include <ece643/libbusiness/Business.hpp>
#include <ece643/libbusiness/State.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;

/*
 * Controls:
 *
 * Select Hotbar - Left 9 switches
 * Inventory - Leftmost button
 * Drop - Left center button
 * Pause - Rightmost button
 * Attack - Left mouse button
 * Use Item - Right mouse button
 * Move - Tilt accelerometer
 * Jump - Jerk accelerometer up
 * Sneak - Low accelerometer tilt
 */

Business::Business(State &state)
    : state(state),
      vncClient(hwio.vga),
      buttons(vncClient, hwio.interrupt),
      switches(vncClient, hwio.interrupt),
      movement(vncClient, hwio.accelerometer) {
}

Business::~Business() noexcept(false) {
}

void Business::run() {
    hwio.interrupt.poll(0xFFFFFFFF);
    while (buttons.poll()) {
        switches.poll();
        movement.poll();
        uint64_t state = this->state;
        if (state == 0xFFFFFF) {
            break;
        }
        int hours = state / 1000;
        int minutes = (state - hours * 1000) * 3 / 50;
        hwio.led.set(switches.leds(), (hours + 6) % 12, minutes, (hours + 6) % 24 >= 12);
        vncClient.poll(microseconds(10000));
    }
}
