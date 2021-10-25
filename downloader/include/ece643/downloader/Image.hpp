#ifndef ECE643_DOWNLOADER_IMAGE_HPP
#define ECE643_DOWNLOADER_IMAGE_HPP

#include <string>
#include <vector>
#include <ece643/downloader/ImageConfig.hpp>
#include <ece643/downloader/ImageLayer.hpp>
#include <ece643/downloader/TarFile.hpp>

namespace ece643 {
    namespace downloader {
        class Image {
            public:
                Image(const TarFile &tar) noexcept;

                const ImageConfig &config() const noexcept;
                void extract(const std::string &prefix) const noexcept;

            private:
                ImageConfig cfg;
                std::vector<ImageLayer> layers;
        };
    }
}

#endif
