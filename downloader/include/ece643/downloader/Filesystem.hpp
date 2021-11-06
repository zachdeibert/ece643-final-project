#ifndef ECE643_DOWNLOADER_FILESYSTEM_HPP
#define ECE643_DOWNLOADER_FILESYSTEM_HPP

#include <string>
#include <ece643/downloader/Loop.hpp>

namespace ece643 {
    namespace downloader {
        class Filesystem {
            public:
                Filesystem(const std::string &rootType, const Loop &rootPart) noexcept;

                void setup() noexcept;
        };
    }
}

#endif
