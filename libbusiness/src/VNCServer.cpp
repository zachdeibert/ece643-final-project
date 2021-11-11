#include <exception>
#include <signal.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <thread>
#include <unistd.h>
#include <ece643/libbusiness/VNCServer.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;

VNCServer::VNCServer() noexcept {
    check(server = fork());
    if (server == 0) {
        check(execl("/usr/bin/Xvnc", "/usr/bin/Xvnc", "-geometry", "640x480", "-depth", "32", "-pixelformat", "RGB888", "-securitytypes", "None", ":2", nullptr));
        terminate();
    }
}

VNCServer::~VNCServer() noexcept {
    check(kill(server, SIGINT));
    check(waitid(P_PID, server, nullptr, WEXITED));
}
