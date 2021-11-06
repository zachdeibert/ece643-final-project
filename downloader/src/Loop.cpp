#include <errno.h>
#include <exception>
#include <fcntl.h>
#include <iostream>
#include <linux/loop.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>
#include <ece643/downloader/Loop.hpp>

using namespace std;
using namespace ece643::downloader;

Loop::Loop(const string &file, uint64_t start, uint64_t length) noexcept {
    int fd = open("/dev/loop-control", O_RDWR);
    if (fd < 0) {
        int e = errno;
        cerr << "open(/dev/loop-control): " << strerror(e) << endl;
        terminate();
    }
    int dev = ioctl(fd, LOOP_CTL_GET_FREE);
    if (dev < 0) {
        int e = errno;
        cerr << "ioctl(LOOP_CTL_GET_FREE): " << strerror(e) << endl;
        terminate();
    }
    if (close(fd) < 0) {
        int e = errno;
        cerr << "close(/dev/loop-control): " << strerror(e) << endl;
        terminate();
    }
    this->file = "/dev/loop" + to_string(dev);
    this->fd = open(this->file.c_str(), O_RDWR);
    if (this->fd < 0) {
        int e = errno;
        cerr << "open(" << this->file << "): " << strerror(e) << endl;
        terminate();
    }
    fd = open(file.c_str(), O_RDWR);
    if (fd < 0) {
        int e = errno;
        cerr << "open(" << file << "): " << strerror(e) << endl;
        terminate();
    }
    if (ioctl(this->fd, LOOP_SET_FD, fd) < 0) {
        int e = errno;
        cerr << "ioctl(LOOP_SET_FD): " << strerror(e) << endl;
        terminate();
    }
    struct loop_info64 info;
    memset(&info, 0, sizeof(info));
    info.lo_flags = LO_FLAGS_AUTOCLEAR;
    info.lo_offset = start;
    info.lo_sizelimit = length;
    strncpy((char *) info.lo_file_name, file.c_str(), sizeof(info.lo_file_name) - 1);
    if (ioctl(this->fd, LOOP_SET_STATUS64, &info) < 0) {
        int e = errno;
        cerr << "ioctl(LOOP_SET_STATUS64): " << strerror(e) << endl;
        terminate();
    }
    if (close(fd) < 0) {
        int e = errno;
        cerr << "close(" << file << "): " << strerror(e) << endl;
        terminate();
    }
}

Loop::~Loop() noexcept {
    if (close(fd) < 0) {
        int e = errno;
        cerr << "close(" << file << "): " << strerror(e) << endl;
        terminate();
    }
}

void Loop::format(const string &type) const noexcept {
    pid_t pid = fork();
    if (pid < 0) {
        int e = errno;
        cerr << "fork() " << strerror(e) << endl;
        terminate();
    }
    if (pid == 0) {
        execl("/sbin/mkfs", "/sbin/mkfs", "-F", "-t", type.c_str(), file.c_str(), nullptr);
        int e = errno;
        cerr << "execl() " << strerror(e) << endl;
        terminate();
    }
    if (waitid(P_PID, pid, nullptr, WEXITED) < 0) {
        int e = errno;
        cerr << "waitid() " << strerror(e) << endl;
        terminate();
    }
}

const string &Loop::path() const noexcept {
    return file;
}
