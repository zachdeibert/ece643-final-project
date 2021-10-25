#ifndef ECE643_DOWNLOADER_TARFILE_HPP
#define ECE643_DOWNLOADER_TARFILE_HPP

#include <stdint.h>
#include <vector>
#include <ece643/downloader/TarEntry.hpp>

namespace ece643 {
    namespace downloader {
        class TarFile {
            public:
                TarFile(const std::vector<uint8_t> &data) noexcept;

                std::vector<TarEntry *>::const_iterator begin() const noexcept;
                std::vector<TarEntry *>::const_iterator end() const noexcept;

            private:
                std::vector<uint8_t> data;
                std::vector<TarEntry *> entries;
        };
    }
}

#endif
