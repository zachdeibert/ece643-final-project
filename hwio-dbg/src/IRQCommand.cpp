#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/IRQCommand.hpp>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

IRQCommand IRQCommand::instance;

void IRQCommand::run(HWIO &hwio, const vector<string> &args) {
    uint32_t mask = 0xFFFFFFFF;
    int secs = 10;
    if (args.size() >= 1) {
        mask = stoul(args[0], nullptr, 16);
    }
    if (args.size() >= 2) {
        secs = stoi(args[1]);
    }
    steady_clock::time_point stop = steady_clock::now() + seconds(secs);
    hwio.interrupt.enable(mask);
    while (true) {
        uint32_t irq;
        do {
            if (steady_clock::now() >= stop) {
                hwio.interrupt.disable(mask);
                return;
            }
        } while (!(irq = hwio.interrupt.poll(mask)));
        cout << "IRQ: " << hex << setw(8) << irq << resetiosflags << endl;
    }
}

IRQCommand::IRQCommand() noexcept : Command("irq") {
}
