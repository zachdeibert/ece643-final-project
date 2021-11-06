#include <errno.h>
#include <fcntl.h>
#include <ios>
#include <iostream>
#include <memory>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>
#include <ece643/downloader/Extractor.hpp>
#include <ece643/downloader/File.hpp>

using namespace std;
using namespace ece643::downloader;

void Extractor::consume(const std::unique_ptr<File> &file) noexcept {
    if (file->filename.empty()) {
        return;
    }
    struct stat dummy;
    if (lstat(file->filename.c_str(), &dummy) >= 0) {
        if (file->type == File::Directory) {
            return;
        }
        if (unlink(file->filename.c_str()) < 0) {
            int e = errno;
            cerr << "unlink(" << file->filename << "): " << strerror(e) << endl;
        }
    }
    switch (file->type) {
        case File::Normal: {
            int fd = creat(file->filename.c_str(), file->fileMode);
            if (fd < 0) {
                int e = errno;
                cerr << "creat(" << file->filename << "): " << strerror(e) << endl;
                return;
            }
            file->attach(*new FileExtractor(fd));
        } break;
        case File::HardLink:
        case File::SymbolicLink: {
            if (!file->isUStar) {
                cerr << "Link in non-UStar archive." << endl;
                return;
            }
            if (file->type == File::HardLink) {
                if (link(file->linkTarget.c_str(), file->filename.c_str()) < 0) {
                    int e = errno;
                    cerr << "link(" << file->filename << "): " << strerror(e) << endl;
                }
            } else if (symlink(file->linkTarget.c_str(), file->filename.c_str()) < 0) {
                int e = errno;
                cerr << "symlink(" << file->filename << "): " << strerror(e) << endl;
            }
            return;
        } break;
        case File::CharacterSpecial:
        case File::BlockSpecial:
        case File::FIFO: {
            if (!file->isUStar) {
                cerr << "Special node in non-UStar archive." << endl;
                return;
            }
            mode_t type;
            switch (file->type) {
                case File::CharacterSpecial:
                    type = S_IFCHR;
                    break;
                case File::BlockSpecial:
                    type = S_IFBLK;
                    break;
                case File::FIFO:
                    type = S_IFIFO;
                    break;
                default:
                    type = 0;
            }
            if (!type) {
                break;
            }
            type |= file->fileMode;
            if (mknod(file->filename.c_str(), type, file->deviceNumber) < 0) {
                int e = errno;
                cerr << "mknod(" << file->filename << "): " << strerror(e) << endl;
                return;
            }
        } break;
        case File::Directory:
            if (mkdir(file->filename.c_str(), file->fileMode) < 0) {
                int e = errno;
                cerr << "mkdir(" << file->filename << "): " << strerror(e) << endl;
                return;
            }
            break;
        case File::GlobalExtendedHeader:
        case File::ExtendedHeader:
            return;
        default:
            cerr << "Skipping extraction of entry '" << file->filename << "' with type '" << (char) file->type << "'." << endl;
            return;
    }
    if (chown(file->filename.c_str(), file->ownerUID, file->ownerGID) < 0) {
        int e = errno;
        cerr << "chown(" << file->filename << "): " << strerror(e) << endl;
    }
    struct utimbuf times;
    times.actime = times.modtime = file->modTime;
    if (utime(file->filename.c_str(), &times) < 0) {
        int e = errno;
        cerr << "utime(" << file->filename << "): " << strerror(e) << endl;
    }
}

void Extractor::detach() noexcept {
}

Extractor::FileExtractor::FileExtractor(int fd) noexcept : fd(fd) {
}

void Extractor::FileExtractor::consume(const vector<uint8_t> &buffer) noexcept {
    if (write(fd, buffer.data(), buffer.size()) < buffer.size()) {
        int e = errno;
        cerr << "write: " << strerror(e) << endl;
    }
}

void Extractor::FileExtractor::detach() noexcept {
    if (close(fd) < 0) {
        int e = errno;
        cerr << "close: " << strerror(e) << endl;
    }
    delete this;
}
