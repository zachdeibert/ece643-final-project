#include <stddef.h>
#include <stdint.h>
#include <string>
#include <unistd.h>
#include <ece643/downloader/Curl.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/FIFO.hpp>

using namespace std;
using namespace ece643::downloader;

void Docker::connectUnix(const string &socket) noexcept {
    this->socket = socket;
    this->proto = "http://localhost";
}

void Docker::connectTCP(const string &host) noexcept {
    this->socket = "";
    this->proto = "http://" + host;
}

FIFO<uint8_t> Docker::exportImage(Curl &curl, const string &tagName) noexcept {
    FIFO<uint8_t> *fifo = new FIFO<uint8_t>();
    curl.start(
        Curl::NoProgress(false),
        Curl::UnixSocketPath(socket),
        Curl::URL(proto + "/images/" + tagName + "/get"),
        Curl::WriteData(fifo),
        Curl::WriteFunction(&Docker::writeFunc),
        Curl::FinishFunction([fifo]() {
            fifo->close();
            delete fifo;
        }));
    return *fifo;
}

size_t Docker::writeFunc(char *ptr, size_t size, size_t nmemb, void *userdata) noexcept {
    FIFO<uint8_t> *fifo = (FIFO<uint8_t> *) userdata;
    size_t count = size * nmemb;
    fifo->write((const uint8_t *) ptr, count);
    return count;
}
