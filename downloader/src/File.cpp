#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <sys/types.h>
#include <vector>
#include <ece643/downloader/File.hpp>

using namespace std;
using namespace ece643::downloader;

File::File(uint8_t *header) noexcept
    : filename((const char *) header, strlen(header, 100))
    , fileMode(octal32(header + 100))
    , ownerUID(octal32(header + 108))
    , ownerGID(octal32(header + 116))
    , size(octal64(header + 124))
    , modTime(octal64(header + 136))
    , checksum(octal32(header + 148))
    , type(header[156] ? (Type) header[156] : Normal)
    , linkTarget((const char *) (header + 157), strlen(header + 157, 100))
    , isUStar(!memcmp(header + 257, "ustar\0""00\0", 10))
    , ownerUser((const char *) (header + 265), strlen(header + 265, 32))
    , ownerGroup((const char *) (header + 297), strlen(header + 297, 32))
    , deviceNumber((((dev_t) octal32(header + 337)) << 4) | (dev_t) octal32(header + 329))
    , filePrefix((const char *) (header + 345), strlen(header + 345, 155))
{
}

size_t File::strlen(uint8_t *str, size_t max) noexcept {
    if (str[max - 1]) {
        return max;
    } else {
        return ::strlen((const char *) str);
    }
}

uint32_t File::octal32(uint8_t *str) noexcept {
    char buf[9];
    memcpy(buf, str, 8);
    buf[8] = '\0';
    uint32_t val;
    sscanf(buf, "%o", &val);
    return val;
}

uint64_t File::octal64(uint8_t *str) noexcept {
    char buf[13];
    memcpy(buf, str, 12);
    buf[12] = '\0';
    uint64_t val;
    sscanf(buf, "%lo", &val);
    return val;
}

void File::consume(const vector<uint8_t> &buffer) noexcept {
    produce(buffer);
}

void File::detach() noexcept {
    finish();
}
