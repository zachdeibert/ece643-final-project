#include <algorithm>
#include <chrono>
#include <ece643/libbusiness/ButtonHandler.hpp>
#include <ece643/libhwio/Interrupt.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;
using namespace ece643::libhwio;

ButtonHandler::ButtonHandler(Interrupt &irq) : irq(irq) {
    irq.enable(0x000F0000);
}

ButtonHandler::~ButtonHandler() noexcept(false) {
    irq.disable(0x000F0000);
}

bool ButtonHandler::poll() {
    steady_clock::time_point now = steady_clock::now();
    int buttons = irq.poll(0x000F0000);
    if (buttons & 0x00010000) {
        lastIRQ[0] = now;
    }
    if (buttons & 0x00020000) {
        lastIRQ[1] = now;
    }
    if (buttons & 0x00040000) {
        lastIRQ[2] = now;
    }
    if (buttons & 0x00080000) {
        lastIRQ[3] = now;
    }
    return !(buttons && now - min({ lastIRQ[0], lastIRQ[1], lastIRQ[2], lastIRQ[3] }) < seconds(2));
}
