#include <arpa/inet.h>
#include <chrono>
#include <errno.h>
#include <exception>
#include <iostream>
#include <netinet/in.h>
#include <stdint.h>
#include <string.h>
#include <sys/select.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <sys/types.h>
#include <unistd.h>
#include <ece643/libbusiness/VNCClient.hpp>
#include <ece643/libbusiness/VNCServer.hpp>
#include <ece643/libhwio/VGA.hpp>

using namespace std;
using namespace std::chrono;
using namespace ece643::libbusiness;
using namespace ece643::libhwio;

VNCClient::VNCClient(VGA &vga) noexcept : fd(socket(AF_INET, SOCK_STREAM, 0)), vga(vga) {
    check(fd);
    struct sockaddr_in addr;
    memset(&addr, 0, sizeof(addr));
    addr.sin_family = AF_INET;
    addr.sin_port = htons(VNCServer::vncPort);
    addr.sin_addr.s_addr = htonl(0x7F000001);
    int e;
    do {
        e = connect(fd, (struct sockaddr *) &addr, sizeof(addr));
    } while (e < 0 && errno == ECONNREFUSED);
    check(e);
    uint8_t buf[27];
    check(read(fd, buf, 12) - 12);
    if (memcmp(buf, "RFB 003.008\n", 12)) {
        cerr << "Invalid handshake message" << endl;
        terminate();
    }
    check(write(fd, buf, 12) - 12);
    check(read(fd, buf, 2) - 2);
    if (memcmp(buf, "\x01\x01", 2)) {
        cerr << "Invalid security type message" << endl;
        terminate();
    }
    check(write(fd, buf, 1) - 1);
    check(read(fd, buf, 4) - 4);
    if (memcmp(buf, "\0\0\0", 4)) {
        cerr << "Invalid authentication result" << endl;
        terminate();
    }
    check(write(fd, "\x01", 1) - 1);
    check(read(fd, buf, 27) - 27);
    if (memcmp(buf, "\x02\x80\x01\xE0 \x18\0\x01\0\xFF\0\xFF\0\xFF\x10\x08\0\0\0\0\0\0\0\x03x11", 27)) {
        cerr << "Invalid framebuffer parameters" << endl;
        terminate();
    }
    check(write(fd, "\x03\0\0\0\0\0\x02\x80\x01\xE0", 10));
}

void VNCClient::poll(microseconds maxDelay) noexcept {
    fd_set reads;
    fd_set writes;
    fd_set excepts;
    FD_ZERO(&reads);
    FD_ZERO(&writes);
    FD_ZERO(&excepts);
    FD_SET(((int) fd), &reads);
    struct timeval timeout;
    timeout.tv_sec  = maxDelay.count() / 1000000;
    timeout.tv_usec = maxDelay.count() % 1000000;
    check(select(1 + (int) fd, &reads, &writes, &excepts, &timeout));
    if (FD_ISSET(((int) fd), &reads)) {
        check(read(fd, vga.buffer(), VGA::maxPacket));
        check(write(fd, "\x03\x01\0\0\0\0\x02\x80\x01\xE0", 10));
    }
}
