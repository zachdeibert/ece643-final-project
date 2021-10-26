#ifndef ECE643_DOWNLOADER_IMAGECONFIG_HPP
#define ECE643_DOWNLOADER_IMAGECONFIG_HPP

#include <string>
#include <vector>
#include <ece643/downloader/TarEntry.hpp>

namespace ece643 {
    namespace downloader {
        class ImageConfig {
            public:
                ImageConfig() noexcept = default;
                ImageConfig(const TarEntry &file) noexcept;

                void exec() const noexcept;

            private:
                std::vector<std::string> env;
                std::vector<std::string> entry;
                std::vector<std::string> cmd;
        };
    }
}

#endif
