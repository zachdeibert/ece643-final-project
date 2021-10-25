#ifndef ECE643_DOWNLOADER_TARENTRY_HPP
#define ECE643_DOWNLOADER_TARENTRY_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <sys/types.h>

namespace ece643 {
    namespace downloader {
        class TarEntry final {
            public:
                enum Type {
                    Normal = '0',
                    HardLink = '1',
                    SymbolicLink = '2',
                    CharacterSpecial = '3',
                    BlockSpecial = '4',
                    Directory = '5',
                    FIFO = '6',
                    ContiguousFile = '7',
                    GlobalExtendedHeader = 'g',
                    ExtendedHeader = 'x'
                };

                std::string filename() const noexcept;
                mode_t fileMode() const noexcept;
                uid_t ownerUID() const noexcept;
                gid_t ownerGID() const noexcept;
                size_t size() const noexcept;
                time_t modTime() const noexcept;
                uint32_t checksum() const noexcept;
                Type type() const noexcept;
                std::string linkTarget() const noexcept;
                bool isUStar() const noexcept;
                int ustarVersion() const noexcept;
                std::string ownerUser() const noexcept;
                std::string ownerGroup() const noexcept;
                dev_t deviceNumber() const noexcept;
                std::string filePrefix() const noexcept;
        };
    }
}

#endif
