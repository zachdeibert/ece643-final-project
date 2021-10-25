#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/types.h>
#include <ece643/downloader/TarEntry.hpp>

using namespace std;
using namespace ece643::downloader;

string TarEntry::filename() const noexcept {
    char buf[101];
    memcpy(buf, this, 100);
    buf[100] = '\0';
    return string(buf);
}

mode_t TarEntry::fileMode() const noexcept {
    char buf[9];
    memcpy(buf, ((const uint8_t *) this) + 100, 8);
    buf[8] = '\0';
    mode_t mode;
    sscanf(buf, "%o", &mode);
    return mode;
}

uid_t TarEntry::ownerUID() const noexcept {
    char buf[9];
    memcpy(buf, ((const uint8_t *) this) + 108, 8);
    buf[8] = '\0';
    uid_t uid;
    sscanf(buf, "%o", &uid);
    return uid;
}

gid_t TarEntry::ownerGID() const noexcept {
    char buf[9];
    memcpy(buf, ((const uint8_t *) this) + 116, 8);
    buf[8] = '\0';
    gid_t gid;
    sscanf(buf, "%o", &gid);
    return gid;
}

size_t TarEntry::size() const noexcept {
    char buf[13];
    memcpy(buf, ((const uint8_t *) this) + 124, 12);
    buf[12] = '\0';
    size_t size;
    sscanf(buf, "%lo", &size);
    return size;
}

time_t TarEntry::modTime() const noexcept {
    char buf[13];
    memcpy(buf, ((const uint8_t *) this) + 136, 12);
    buf[12] = '\0';
    time_t time;
    sscanf(buf, "%lo", &time);
    return time;
}

uint32_t TarEntry::checksum() const noexcept {
    char buf[9];
    memcpy(buf, ((const uint8_t *) this) + 148, 8);
    buf[8] = '\0';
    uint32_t sum;
    sscanf(buf, "%o", &sum);
    return sum;
}

TarEntry::Type TarEntry::type() const noexcept {
    Type t = (Type) ((const uint8_t *) this)[156];
    if (!t) {
        t = Normal;
    }
    return t;
}

string TarEntry::linkTarget() const noexcept {
    char buf[101];
    memcpy(buf, ((const uint8_t *) this) + 157, 100);
    buf[100] = '\0';
    return string(buf);
}

bool TarEntry::isUStar() const noexcept {
    return !memcmp(((const uint8_t *) this) + 257, "ustar", 6);
}

int TarEntry::ustarVersion() const noexcept {
    if (!isUStar()) {
        return -1;
    }
    if (!memcmp(((const uint8_t *) this) + 263, "00", 2)) {
        return 0;
    }
    return -1;
}

string TarEntry::ownerUser() const noexcept {
    if (!isUStar()) {
        return "";
    }
    char buf[33];
    memcpy(buf, ((const uint8_t *) this) + 265, 32);
    buf[32] = '\0';
    return string(buf);
}

string TarEntry::ownerGroup() const noexcept {
    if (!isUStar()) {
        return "";
    }
    char buf[33];
    memcpy(buf, ((const uint8_t *) this) + 297, 32);
    buf[32] = '\0';
    return string(buf);
}

dev_t TarEntry::deviceNumber() const noexcept {
    if (!isUStar()) {
        return 0;
    }
    char buf[9];
    buf[8] = '\0';
    memcpy(buf, ((const uint8_t *) this) + 329, 8);
    uint32_t lower;
    sscanf(buf, "%o", &lower);
    memcpy(buf, ((const uint8_t *) this) + 337, 8);
    uint32_t upper;
    sscanf(buf, "%o", &upper);
    return (((dev_t) upper) << (sizeof(dev_t) / 2)) | ((dev_t) lower);
}

string TarEntry::filePrefix() const noexcept {
    if (!isUStar()) {
        return "";
    }
    char buf[156];
    memcpy(buf, ((const uint8_t *) this) + 345, 155);
    buf[155] = '\0';
    return string(buf);
}
