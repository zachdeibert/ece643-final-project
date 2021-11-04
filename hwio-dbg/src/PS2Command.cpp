#include <chrono>
#include <iomanip>
#include <ios>
#include <iostream>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/PS2Command.hpp>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

PS2Command PS2Command::instance;

void PS2Command::run(HWIO &hwio, const vector<string> &args) {
    int secs = 10;
    if (args.size() >= 1) {
        secs = stoi(args[0]);
    }
    steady_clock::time_point stop = steady_clock::now() + seconds(secs);
    hwio.interrupt.enable(1 << 24);
    while (true) {
        do {
            if (steady_clock::now() >= stop) {
                hwio.interrupt.disable(1 << 24);
                return;
            }
        } while (!hwio.interrupt.poll(1 << 24));
        string data = hwio.ps2.poll();
        cout << "PS/2 data:" << hex << showbase;
        for (string::const_iterator it = data.begin(); it != data.end(); ++it) {
            cout << " " << setw(2) << (int) *it << endl;
        }
        cout << resetiosflags;
    }
}

PS2Command::PS2Command() noexcept : Command("ps2") {
}
