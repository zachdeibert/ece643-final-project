#include <stdexcept>
#include <string.h>
#include <ece643/libhwio/MMap.hpp>
#include <ece643/libhwio/VGA.hpp>

using namespace std;
using namespace ece643::libhwio;

VGA::VGA(MMap &mmap) noexcept : mmap(&mmap) {
}

void *VGA::buffer() {
    return *mmap + 0x000000;
}

void VGA::write(int x, int y, int width, int height, void *data) {
    if (x < 0 || x + width >= VGA::width || y < 0 || y + height >= VGA::height) {
        throw invalid_argument("VGA::write");
    }
    uint16_t header[6];
    header[0] = (uint16_t) x;
    header[1] = (uint16_t) y;
    header[2] = (uint16_t) width;
    header[3] = (uint16_t) height;
    header[4] = 0;
    header[5] = 0;
    memcpy(buffer(), header, sizeof(header));
    memcpy(((uint8_t *) buffer()) + 0xC, data, width * height * 4);
}
