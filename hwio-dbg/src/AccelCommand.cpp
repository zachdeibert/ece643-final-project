#include <array>
#include <iostream>
#include <stdint.h>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/AccelCommand.hpp>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

AccelCommand AccelCommand::instance;

void AccelCommand::run(HWIO &hwio, const vector<string> &args) {
    int count = 10;
    if (args.size() >= 1) {
        count = stoi(args[0]);
    }
    hwio.accelerometer.enable();
    for (int i = 0; i < count; ++i) {
        while (!hwio.accelerometer.ready());
        array<int16_t, 3> data = hwio.accelerometer.read();
        cout << "Accelerometer sample " << i << ": <" << data[0] << ", " << data[1] << ", " << data[2] << ">" << endl;
    }
    hwio.accelerometer.disable();
}

AccelCommand::AccelCommand() noexcept : Command("accel") {
}
