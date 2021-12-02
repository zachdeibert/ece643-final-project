#include <algorithm>
#include <chrono>
#define XK_MISCELLANY
#include <X11/keysymdef.h>
#include <ece643/libbusiness/ButtonHandler.hpp>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libhwio/Interrupt.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;
using namespace ece643::libhwio;

ButtonHandler::ButtonHandler(VNCClient &vnc, Interrupt &irq) : vnc(vnc), irq(irq) {
    down[0] = false;
    down[1] = false;
    down[2] = false;
    down[3] = false;
    irq.enable(0x000F0000);
}

ButtonHandler::~ButtonHandler() noexcept(false) {
    irq.disable(0x000F0000);
}

bool ButtonHandler::poll() {
    steady_clock::time_point now = steady_clock::now();
    int buttons = irq.poll(0x000F0000);
    for (int i = 0; i < 4; ++i) {
        if (buttons & (1 << (i + 16))) {
            lastIRQ[i] = now;
            down[i] = !down[i];
            switch (i) {
                case 0:
                    vnc.key(down[0], XK_Escape);
                    break;
                case 1:
                    vnc.key(down[1], XK_F3);
                    break;
                case 2:
                    vnc.key(down[2], 'e');
                    break;
            }
        }
    }
    return !(buttons && now - min({ lastIRQ[0], lastIRQ[1], lastIRQ[2], lastIRQ[3] }) < seconds(2));
}

bool ButtonHandler::attack() const noexcept {
    return down[3];
}
