#ifndef ECE643_DOWNLOADER_IMAGELAYER_HPP
#define ECE643_DOWNLOADER_IMAGELAYER_HPP

#include <string>
#include <ece643/downloader/TarEntry.hpp>
#include <ece643/downloader/TarFile.hpp>

namespace ece643 {
    namespace downloader {
        class ImageLayer : public TarFile {
            public:
                ImageLayer(const TarEntry &file) noexcept;

                void extract(const std::string &prefix) const noexcept;
        };
    }
}

#endif
