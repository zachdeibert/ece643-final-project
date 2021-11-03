#include <errno.h>
#include <fcntl.h>
#include <ios>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>
#include <ece643/downloader/Extractor.hpp>
#include <ece643/downloader/ImageFIFO.hpp>
#include <ece643/downloader/TarFIFO.hpp>
#include <ece643/downloader/TarEntryFIFO.hpp>

using namespace std;
using namespace ece643::downloader;

void Extractor::extract(ImageFIFO &image, const string &prefix) noexcept {
    for (; !image.eof(); ++image) {
        for (TarFIFO &layer = *image; !layer.eof(); ++layer) {
            TarEntryFIFO &entry = *layer;
            string filename = prefix + entry.filename;
            bool skip = false;
            struct stat dummy;
            if (lstat(filename.c_str(), &dummy) >= 0) {
                if (entry.type == TarEntryFIFO::Directory) {
                    continue;
                }
                if (unlink(filename.c_str()) < 0) {
                    int e = errno;
                    cerr << "unlink(" << filename << "): " << strerror(e) << endl;
                }
            }
            switch (entry.type) {
                case TarEntryFIFO::Normal: {
                    int fd = creat(filename.c_str(), entry.fileMode);
                    if (fd < 0) {
                        int e = errno;
                        cerr << "creat(" << filename << "): " << strerror(e) << endl;
                        skip = true;
                        break;
                    }
                    uint8_t buffer[4096];
                    while (!entry.eof()) {
                        streamsize count = entry.read(buffer, 1, sizeof(buffer));
                        if (write(fd, buffer, count) < count) {
                            int e = errno;
                            cerr << "write(" << filename << "): " << strerror(e) << endl;
                            skip = true;
                            break;
                        }
                    }
                    if (skip) {
                        break;
                    }
                    if (close(fd) < 0) {
                        int e = errno;
                        cerr << "close(" << filename << "): " << strerror(e) << endl;
                        skip = true;
                        break;
                    }
                } break;
                case TarEntryFIFO::HardLink:
                case TarEntryFIFO::SymbolicLink: {
                    if (!entry.isUStar) {
                        cerr << "Link in non-UStar archive." << endl;
                        skip = true;
                        break;
                    }
                    if (entry.type == TarEntryFIFO::HardLink) {
                        if (link(entry.linkTarget.c_str(), filename.c_str()) < 0) {
                            int e = errno;
                            cerr << "link(" << filename << "): " << strerror(e) << endl;
                        }
                    } else if (symlink(entry.linkTarget.c_str(), filename.c_str()) < 0) {
                        int e = errno;
                        cerr << "symlink(" << filename << "): " << strerror(e) << endl;
                    }
                    skip = true;
                    break;
                } break;
                case TarEntryFIFO::CharacterSpecial:
                case TarEntryFIFO::BlockSpecial:
                case TarEntryFIFO::FIFO: {
                    if (!entry.isUStar) {
                        cerr << "Special node in non-UStar archive." << endl;
                        skip = true;
                        break;
                    }
                    mode_t type;
                    switch (entry.type) {
                        case TarEntryFIFO::CharacterSpecial:
                            type = S_IFCHR;
                            break;
                        case TarEntryFIFO::BlockSpecial:
                            type = S_IFBLK;
                            break;
                        case TarEntryFIFO::FIFO:
                            type = S_IFIFO;
                            break;
                        default:
                            type = 0;
                    }
                    if (!type) {
                        break;
                    }
                    type |= entry.fileMode;
                    if (mknod(filename.c_str(), type, entry.deviceNumber) < 0) {
                        int e = errno;
                        cerr << "mknod(" << filename << "): " << strerror(e) << endl;
                        skip = true;
                    }
                } break;
                case TarEntryFIFO::Directory:
                    if (mkdir(filename.c_str(), entry.fileMode) < 0) {
                        int e = errno;
                        cerr << "mkdir(" << filename << "): " << strerror(e) << endl;
                        skip = true;
                    }
                    break;
                case TarEntryFIFO::GlobalExtendedHeader:
                case TarEntryFIFO::ExtendedHeader:
                    skip = true;
                    break;
                default:
                    cerr << "Skipping extraction of entry '" << filename << "' with type '" << (char) entry.type << "'." << endl;
                    skip = true;
                    break;
            }
            if (skip) {
                continue;
            }
            if (chown(filename.c_str(), entry.ownerUID, entry.ownerGID) < 0) {
                int e = errno;
                cerr << "chown(" << filename << "): " << strerror(e) << endl;
            }
            struct utimbuf times;
            times.actime = times.modtime = entry.modTime;
            if (utime(filename.c_str(), &times) < 0) {
                int e = errno;
                cerr << "utime(" << filename << "): " << strerror(e) << endl;
            }
        }
        image->cancel();
    }
    image.cancel();
}
