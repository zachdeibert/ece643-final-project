#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/hwio-dbg/QuitCommand.hpp>
#include <ece643/hwio-dbg/QuitException.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

QuitCommand QuitCommand::instance;

void QuitCommand::run(HWIO &hwio, const vector<string> &args) {
    throw QuitException();
}

QuitCommand::QuitCommand() noexcept : Command("quit") {
}
