#include <errno.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <sched.h>
#include <stack>
#include <string.h>
#include <string>
#include <sys/mount.h>
#include <sys/stat.h>
#include <sys/syscall.h>
#include <sys/types.h>
#include <unistd.h>
#include <ece643/downloader/Filesystem.hpp>

using namespace std;
using namespace ece643::downloader;

Filesystem::Filesystem() noexcept {
    if (setuid(0) < 0) {
        int e = errno;
        cerr << "setuid: " << strerror(e) << endl;
        terminate();
    }
    if (setgid(0) < 0) {
        int e = errno;
        cerr << "setgid: " << strerror(e) << endl;
        terminate();
    }
    if (unshare(CLONE_NEWNS) < 0) {
        int e = errno;
        cerr << "unshare: " << strerror(e) << endl;
        terminate();
    }
    if (mount(nullptr, "/", nullptr, MS_REC | MS_PRIVATE, NULL) < 0) {
        int e = errno;
        cerr << "mount(/): " << strerror(e) << endl;
        terminate();
    }
    if (chdir("/") < 0) {
        int e = errno;
        cerr << "chdir: " << strerror(e) << endl;
        terminate();
    }
    stack<string> mounts;
    {
        ifstream ifs("/proc/mounts");
        string line;
        while (getline(ifs, line)) {
            size_t begin = line.find_first_of(' ');
            if (begin++ == string::npos) {
                cerr << "Malformed /proc/mounts file." << endl;
                terminate();
            }
            size_t end = line.find_first_of(' ', begin);
            if (end == string::npos) {
                cerr << "Malformed /proc/mounts file." << endl;
                terminate();
            }
            mounts.emplace(line.data() + begin, line.data() + end);
        }
    }
    while (!mounts.empty()) {
        if (mounts.top() != "/" && umount(mounts.top().c_str()) < 0) {
            int e = errno;
            cerr << "umount(" << mounts.top() << "): " << strerror(e) << endl;
            terminate();
        }
        mounts.pop();
    }
    if (mount(nullptr, "/tmp", "tmpfs", 0, nullptr) < 0) {
        int e = errno;
        cerr << "mount(/tmp): " << strerror(e) << endl;
        terminate();
    }
    if (mkdir("/tmp/tmp", 0) < 0) {
        int e = errno;
        cerr << "mkdir(/tmp/tmp): " << strerror(e) << endl;
        terminate();
    }
    if (syscall(SYS_pivot_root, "/tmp", "/tmp/tmp") < 0) {
        int e = errno;
        cerr << "pivot_root: " << strerror(e) << endl;
        terminate();
    }
    if (umount("/tmp") < 0) {
        int e = errno;
        cerr << "umount(/tmp): " << strerror(e) << endl;
        terminate();
    }
    if (rmdir("/tmp") < 0) {
        int e = errno;
        cerr << "rmdir(/tmp): " << strerror(e) << endl;
        terminate();
    }
}

void Filesystem::setup() noexcept {
    if (mount(nullptr, "/dev", "devtmpfs", 0, nullptr) < 0) {
        int e = errno;
        cerr << "mount(/dev): " << strerror(e) << endl;
        terminate();
    }
    if (mount(nullptr, "/sys", "sysfs", 0, nullptr) < 0) {
        int e = errno;
        cerr << "mount(/sys): " << strerror(e) << endl;
        terminate();
    }
    if (mount(nullptr, "/proc", "proc", 0, nullptr) < 0) {
        int e = errno;
        cerr << "mount(/proc): " << strerror(e) << endl;
        terminate();
    }
}
