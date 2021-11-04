#include <iostream>
#include <memory>
#include <sstream>
#include <stdlib.h>
#include <string>
#include <vector>
#include <ece643/hwio-dbg/Command.hpp>
#include <ece643/hwio-dbg/ExceptionDebugger.hpp>
#include <ece643/hwio-dbg/QuitException.hpp>
#include <ece643/libhwio/HWIO.hpp>

using namespace std;
using namespace ece643::hwiodbg;
using namespace ece643::libhwio;

int main(int argc, const char **argv) {
    unique_ptr<HWIO> hwio;
    ExceptionDebugger::printExceptions([&hwio]() {
        //hwio.reset(new HWIO());
    });
    cout << "HWIO initialized." << endl;
    vector<string> args;
    try {
        while (true) {
            cout << "> ";
            string line;
            getline(cin, line);
            istringstream oss(line);
            string cmd;
            oss >> cmd;
            args.clear();
            while (!oss.eof()) {
                string arg;
                oss >> arg;
                if (!arg.empty()) {
                    args.push_back(arg);
                }
            }
            ExceptionDebugger::printExceptions([&hwio, &cmd, &args]() {
                Command::run(*hwio, cmd, args);
            });
        }
    } catch (const QuitException &) {
    }
    return EXIT_SUCCESS;
}
