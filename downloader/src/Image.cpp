#include <stdint.h>
#include <vector>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/HTTP.hpp>
#include <ece643/downloader/Image.hpp>

using namespace std;
using namespace ece643::downloader;

void Image::run(Container &container) noexcept {
    HTTP http;
    http.attach(*this);
    container.docker().run(http, "/containers/" + container.id() + "/export");
}

void Image::consume(const vector<uint8_t> &obj) noexcept {
    produce(obj);
}

void Image::detach() noexcept {
    finish();
}
