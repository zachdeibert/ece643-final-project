#ifndef ECE643_DOWNLOADER_EXTRACTOR_HPP
#define ECE643_DOWNLOADER_EXTRACTOR_HPP

#include <string>
#include <ece643/downloader/ImageFIFO.hpp>

namespace ece643 {
    namespace downloader {
        class Extractor {
            public:
                static void extract(ImageFIFO &image, const std::string &prefix) noexcept;
        };
    }
}

#endif
