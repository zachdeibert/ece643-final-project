#include <iostream>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/hwio-dbg/HelpCommand.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

HelpCommand HelpCommand::instance;

void HelpCommand::run(HWIO &hwio, const vector<string> &args) {
    cout << "Valid commands:" << endl;
    Command::printAllHelp();
}

HelpCommand::HelpCommand() noexcept : Command("help") {
}
