#include <iostream>
#include <stdexcept>
#include <string>
#include <vector>
#include <unordered_map>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

void Command::run(HWIO &hwio, const string &command, const vector<string> &args) {
    unordered_map<string, Command *>::iterator it = commands().find(command);
    if (it == commands().end()) {
        throw runtime_error("Unknown command.");
    }
    it->second->run(hwio, args);
}

void Command::printAllHelp() noexcept {
    for (unordered_map<string, Command *>::const_iterator it = commands().begin(); it != commands().end(); ++it) {
        it->second->printHelp();
    }
}

void Command::printHelp() const noexcept {
    cout << name << endl;
}

Command::Command(const string &name) noexcept : name(name) {
    commands().emplace(name, this);
}

unordered_map<string, Command *> &Command::commands() noexcept {
    static unordered_map<string, Command *> buffer;
    return buffer;
}
