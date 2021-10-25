#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <vector>
#include <curl/curl.h>
#include <ece643/downloader/Docker.hpp>

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

vector<uint8_t> Docker::exportImage(const string &tagName) noexcept {
    curl.reset();
    string url = proto + "/images/" + tagName + "/get";
    vector<uint8_t> buffer;
    curl[CURLOPT_NOPROGRESS] = 0L;
    if (!socket.empty()) {
        curl[CURLOPT_UNIX_SOCKET_PATH] = socket.c_str();
    }
    curl[CURLOPT_URL] = url.c_str();
    curl[CURLOPT_WRITEDATA] = &buffer;
    curl[CURLOPT_WRITEFUNCTION] = &Docker::writeFunc;
    curl.run();
    return buffer;
}

size_t Docker::writeFunc(char *ptr, size_t size, size_t nmemb, void *userdata) noexcept {
    size_t count = size * nmemb;
    vector<uint8_t> *buffer = (vector<uint8_t> *) userdata;
    size_t off = buffer->size();
    buffer->resize(off + count);
    memcpy(buffer->data() + off, ptr, count);
    return count;
}
