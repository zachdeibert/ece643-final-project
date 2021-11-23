#include <ece643/libbusiness/SwitchHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Interrupt.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libhwio;

SwitchHandler::SwitchHandler(VNCClient &vnc, Interrupt &irq) : vnc(vnc), irq(irq), led(0), down(0) {
    irq.enable(0x000003FE);
}

SwitchHandler::~SwitchHandler() noexcept(false) {
    irq.disable(0x000003FE);
}

void SwitchHandler::poll() {
    if (down) {
        vnc.key(false, down);
        down = 0;
    }
    int irq = this->irq.poll(0x000003FE);
    for (int i = 1; i < 10; ++i) {
        int mask = 1 << i;
        if (irq & mask) {
            led = mask;
            down = '0' + (10 - i) % 10;
            vnc.key(true, down);
            break;
        }
    }
}

int SwitchHandler::leds() const noexcept {
    return led;
}
