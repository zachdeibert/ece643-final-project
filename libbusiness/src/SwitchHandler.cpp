#include <ece643/libbusiness/SwitchHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Interrupt.hpp>

using namespace ece643::libbusiness;
using namespace ece643::libhwio;

SwitchHandler::SwitchHandler(VNCClient &vnc, Interrupt &irq) : vnc(vnc), irq(irq), led(0x00000200), down(0), rightClick(false) {
    irq.enable(0x000003FF);
}

SwitchHandler::~SwitchHandler() noexcept(false) {
    irq.disable(0x000003FF);
}

void SwitchHandler::poll() {
    if (down) {
        vnc.key(false, down);
        down = 0;
    }
    int irq = this->irq.poll(0x000003FF);
    for (int i = 0; i < 10; ++i) {
        int mask = 1 << i;
        if (irq & mask) {
            if (i > 0) {
                if (led & mask) {
                    if (pan()) {
                        rightClick = true;
                    } else {
                        down = 'q';
                        vnc.key(true, down);
                    }
                } else {
                    led = ((led & 1) | mask);
                    down = '0' + (10 - i) % 10;
                    vnc.key(true, down);
                }
            } else {
                led ^= 1;
            }
            break;
        }
    }
}

int SwitchHandler::leds() const noexcept {
    return led;
}

bool SwitchHandler::pan() const noexcept {
    return led & 1;
}

bool SwitchHandler::use() noexcept {
    if (rightClick) {
        rightClick = false;
        return true;
    } else {
        return false;
    }
}
