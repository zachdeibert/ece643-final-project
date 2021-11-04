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
    int leds = 0;
    int hours = 0;
    int minutes = 0;
    bool pm = false;
    if(count >= 1) {
        leds = stoi(args[0], nullptr, 2);
    }
    if (count >= 2) {
        hours = stoi(args[1]);
    }
    if (count >= 3) {
        minutes = stoi(args[2]);
    }
    if (count >= 4) {
        pm = args[3] == "PM";
    }

    hwio.led.set(leds, hours, minutes, pm);
}

/*
 * LEDCommand::printHelp()
 * Prints the help message for the LED command.
 */
void LEDCommand::printHelp() const noexcept {
    cout << "Usage: led <leds> <hours> <minutes> <AM|PM>\n";
    cout << "leds: a binary string of length 10, where each bit represents a LED\n";
    cout << "Example: led 10101010\n";
}

LEDCommand::LEDCommand() noexcept : Command("led") {
}
