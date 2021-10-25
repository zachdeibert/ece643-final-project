#include <new>
#include <stdint.h>
#include <vector>
#include <ece643/downloader/TarEntry.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace std;
using namespace ece643::downloader;

TarFile::TarFile(const vector<uint8_t> &data) noexcept : data(data) {
    uint8_t *it = this->data.data();
    uint8_t *end = it + this->data.size();
    while (it < end) {
        TarEntry *ent = new (it) TarEntry();
        if (ent->filename().empty()) {
            break;
        }
        entries.push_back(ent);
        it += 512 * ((ent->size() + 1023) / 512);
    }
}

vector<TarEntry *>::const_iterator TarFile::begin() const noexcept {
    return entries.begin();
}

vector<TarEntry *>::const_iterator TarFile::end() const noexcept {
    return entries.end();
}
