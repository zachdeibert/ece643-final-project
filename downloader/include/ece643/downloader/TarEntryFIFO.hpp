#ifndef ECE643_DOWNLOADER_TARENTRYFIFO_HPP
#define ECE643_DOWNLOADER_TARENTRYFIFO_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <sys/types.h>
#include <ece643/downloader/FIFO.hpp>

namespace ece643 {
    namespace downloader {
        class TarEntryFIFO : public FIFO<uint8_t> {
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

                TarEntryFIFO(uint8_t *header) noexcept;

                const std::string filename;
                const mode_t fileMode;
                const uid_t ownerUID;
                const gid_t ownerGID;
                const size_t size;
                const time_t modTime;
                const uint32_t checksum;
                const Type type;
                const std::string linkTarget;
                const bool isUStar;
                const std::string ownerUser;
                const std::string ownerGroup;
                const dev_t deviceNumber;
                const std::string filePrefix;

            private:
                size_t strlen(uint8_t *str, size_t max) noexcept;
                uint32_t octal32(uint8_t *str) noexcept;
                uint64_t octal64(uint8_t *str) noexcept;
        };
    }
}

#endif
