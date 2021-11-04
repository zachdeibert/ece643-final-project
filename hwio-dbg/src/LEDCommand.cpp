#include <array>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/LEDCommand.hpp>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

LEDCommand LEDCommand::instance;

void LEDCommand::run(HWIO &hwio, const vector<string> &args) {
    int count = args.size();
    int leds;
    if(count >= 1) {
        leds = stoi(args[0], nullptr, 2);
    }

    hwio.led.set(leds, 0, 0, false);
}

LEDCommand::LEDCommand() noexcept : Command("led") {
}
