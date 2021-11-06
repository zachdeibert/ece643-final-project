#ifndef ECE643_DOWNLOADER_IMAGE_HPP
#define ECE643_DOWNLOADER_IMAGE_HPP

#include <stdint.h>
#include <vector>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Sink.hpp>
#include <ece643/downloader/Source.hpp>

namespace ece643 {
    namespace downloader {
        class Image : public Source<std::vector<uint8_t>>, private Sink<std::vector<uint8_t>> {
            public:
                void run(Container &container) noexcept;

            private:
                void consume(const std::vector<uint8_t> &obj) noexcept;
                void detach() noexcept;
        };
    }
}

#endif
