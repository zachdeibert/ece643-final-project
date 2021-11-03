#include <ios>
#include <stddef.h>
#include <stdint.h>
#include <ece643/downloader/FIFO.hpp>
#include <ece643/downloader/TarFIFO.hpp>

using namespace std;
using namespace ece643::downloader;

TarFIFO::TarFIFO(const FIFO<uint8_t> &input) noexcept : input(input), thread(&TarFIFO::decode, this) {
}

void TarFIFO::decode() noexcept {
    uint8_t buf[512];
    while (!input.eof()) {
        streamsize count = input.read(buf, 512, 512);
        if (count < 512) {
            break;
        }
        StrongReference entry = emplace(buf);
        for (size_t blocks = (entry->size + 511) / 512; blocks > 0; --blocks) {
            streamsize count = input.read(buf, 512, 512);
            if (count < 512) {
                break;
            }
            entry->write(buf, 512);
        }
        entry->close();
    }
    close();
}
