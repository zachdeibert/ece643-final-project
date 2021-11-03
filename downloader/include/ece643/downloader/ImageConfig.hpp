#ifndef ECE643_DOWNLOADER_IMAGECONFIG_HPP
#define ECE643_DOWNLOADER_IMAGECONFIG_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <ece643/downloader/FIFO.hpp>

namespace ece643 {
    namespace downloader {
        class ImageConfig {
            public:
                ImageConfig() noexcept = default;
                ImageConfig(FIFO<uint8_t> &data) noexcept;

                void exec() const noexcept;

            private:
                std::vector<std::string> env;
                std::vector<std::string> entry;
                std::vector<std::string> cmd;
        };
    }
}

#endif
