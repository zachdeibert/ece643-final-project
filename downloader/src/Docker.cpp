#include <string>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/HTTP.hpp>

using namespace std;
using namespace ece643::downloader;

Docker::Docker(const string &socket) noexcept : socket(socket) {
}

void Docker::run(HTTP &http, const string &url, const string &method, const string &body) noexcept {
    http.run(socket, "http://127.0.0.1:2376" + url, method, body);
}
