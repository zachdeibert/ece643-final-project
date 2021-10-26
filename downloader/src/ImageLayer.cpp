#include <errno.h>
#include <fcntl.h>
#include <iostream>
#include <string.h>
#include <string>
#include <sys/stat.h>
#include <sys/types.h>
#include <unistd.h>
#include <utime.h>
#include <ece643/downloader/ImageLayer.hpp>
#include <ece643/downloader/TarEntry.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace std;
using namespace ece643::downloader;

ImageLayer::ImageLayer(const TarEntry &file) noexcept : TarFile(file.copy()) {
}

void ImageLayer::extract(const string &prefix) const noexcept {
    for (const_iterator it = begin(); it != end(); ++it) {
        string filename = prefix + (*it)->filename();
        bool skip = false;
        struct stat dummy;
        if (lstat(filename.c_str(), &dummy) >= 0) {
            if ((*it)->type() == TarEntry::Directory) {
                continue;
            }
            if (unlink(filename.c_str()) < 0) {
                int e = errno;
                cerr << "unlink(" << filename << "): " << strerror(e) << endl;
            }
        }
        switch ((*it)->type()) {
            case TarEntry::Normal: {
                int fd = creat(filename.c_str(), (*it)->fileMode());
                if (fd < 0) {
                    int e = errno;
                    cerr << "creat(" << filename << "): " << strerror(e) << endl;
                    skip = true;
                    break;
                }
                if (write(fd, (*it)->data(), (*it)->size()) < (*it)->size()) {
                    int e = errno;
                    cerr << "write(" << filename << "): " << strerror(e) << endl;
                    skip = true;
                    break;
                }
                if (close(fd) < 0) {
                    int e = errno;
                    cerr << "close(" << filename << "): " << strerror(e) << endl;
                    skip = true;
                    break;
                }
            } break;
            case TarEntry::HardLink:
            case TarEntry::SymbolicLink: {
                if (!(*it)->isUStar()) {
                    cerr << "Link in non-UStar archive." << endl;
                    skip = true;
                    break;
                }
                if ((*it)->type() == TarEntry::HardLink) {
                    if (link((*it)->linkTarget().c_str(), filename.c_str()) < 0) {
                        int e = errno;
                        cerr << "link(" << filename << "): " << strerror(e) << endl;
                    }
                } else if (symlink((*it)->linkTarget().c_str(), filename.c_str()) < 0) {
                    int e = errno;
                    cerr << "symlink(" << filename << "): " << strerror(e) << endl;
                }
                skip = true;
                break;
            } break;
            case TarEntry::CharacterSpecial:
            case TarEntry::BlockSpecial:
            case TarEntry::FIFO: {
                if (!(*it)->isUStar()) {
                    cerr << "Special node in non-UStar archive." << endl;
                    skip = true;
                    break;
                }
                mode_t type;
                switch ((*it)->type()) {
                    case TarEntry::CharacterSpecial:
                        type = S_IFCHR;
                        break;
                    case TarEntry::BlockSpecial:
                        type = S_IFBLK;
                        break;
                    case TarEntry::FIFO:
                        type = S_IFIFO;
                        break;
                    default:
                        type = 0;
                }
                if (!type) {
                    break;
                }
                type |= (*it)->fileMode();
                if (mknod(filename.c_str(), type, (*it)->deviceNumber()) < 0) {
                    int e = errno;
                    cerr << "mknod(" << filename << "): " << strerror(e) << endl;
                    skip = true;
                }
            } break;
            case TarEntry::Directory:
                if (mkdir(filename.c_str(), (*it)->fileMode()) < 0) {
                    int e = errno;
                    cerr << "mkdir(" << filename << "): " << strerror(e) << endl;
                    skip = true;
                }
                break;
            case TarEntry::GlobalExtendedHeader:
            case TarEntry::ExtendedHeader:
                skip = true;
                break;
            default:
                cerr << "Skipping extraction of entry '" << filename << "' with type '" << (char) (*it)->type() << "'." << endl;
                skip = true;
                break;
        }
        if (skip) {
            continue;
        }
        if (chown(filename.c_str(), (*it)->ownerUID(), (*it)->ownerGID()) < 0) {
            int e = errno;
            cerr << "chown(" << filename << "): " << strerror(e) << endl;
        }
        struct utimbuf times;
        times.actime = times.modtime = (*it)->modTime();
        if (utime(filename.c_str(), &times) < 0) {
            int e = errno;
            cerr << "utime(" << filename << "): " << strerror(e) << endl;
        }
    }
}
