#include <algorithm>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <vector>
#include <ece643/downloader/File.hpp>
#include <ece643/downloader/Tarball.hpp>

using namespace std;
using namespace ece643::downloader;

Tarball::Tarball() noexcept : bytesToSector(512) {
}

void Tarball::consume(const vector<uint8_t> &buffer) noexcept {
    vector<uint8_t> tmp;
    size_t start = 0;
    size_t length = buffer.size();
    while (length > 0) {
        if (currentFile) {
            if (bytesToFile > 0) {
                size_t len = min(length, bytesToFile);
                currentFile->produce(quickCopy(buffer, tmp, start, len));
                start += len;
                length -= len;
                bytesToFile -= len;
                bytesToSector -= len;
                if (bytesToFile <= 0) {
                    currentFile->finish();
                }
            } else {
                size_t len = min(length, bytesToSector);
                start += len;
                length -= len;
                bytesToSector -= len;
                if (bytesToSector <= 0) {
                    bytesToSector = 512;
                    currentFile.reset();
                }
            }
        } else {
            size_t len = min(length, bytesToSector);
            memcpy(header + sizeof(header) - bytesToSector, buffer.data() + start, len);
            start += len;
            length -= len;
            bytesToSector -= len;
            if (bytesToSector <= 0) {
                currentFile.reset(new File(header));
                bytesToFile = currentFile->size;
                bytesToSector = (bytesToFile + 511) / 512 * 512;
                produce(currentFile);
            }
        }
    }
}

void Tarball::detach() noexcept {
    finish();
}

const vector<uint8_t> &Tarball::quickCopy(const vector<uint8_t> &source, vector<uint8_t> &tmp, size_t start, size_t length) noexcept {
    if (start == 0 && length == source.size()) {
        return source;
    }
    tmp.resize(length);
    memcpy(tmp.data(), source.data() + start, length);
    return tmp;
}
