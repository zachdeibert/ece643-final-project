#include <algorithm>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <ece643/downloader/TarEntryFIFO.hpp>

using namespace std;
using namespace ece643::downloader;

TarEntryFIFO::TarEntryFIFO(uint8_t *header) noexcept
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

size_t TarEntryFIFO::strlen(uint8_t *str, size_t max) noexcept {
    if (str[max - 1]) {
        return max;
    } else {
        return ::strlen((const char *) str);
    }
}

uint32_t TarEntryFIFO::octal32(uint8_t *str) noexcept {
    char buf[9];
    memcpy(buf, str, 8);
    buf[8] = '\0';
    uint32_t val;
    sscanf(buf, "%o", &val);
    return val;
}

uint64_t TarEntryFIFO::octal64(uint8_t *str) noexcept {
    char buf[13];
    memcpy(buf, str, 12);
    buf[12] = '\0';
    uint64_t val;
    sscanf(buf, "%lo", &val);
    return val;
}
