#ifndef ECE643_DOWNLOADER_TARBALL_HPP
#define ECE643_DOWNLOADER_TARBALL_HPP

#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <ece643/downloader/File.hpp>
#include <ece643/downloader/Sink.hpp>
#include <ece643/downloader/Source.hpp>

namespace ece643 {
    namespace downloader {
        class Tarball : public Sink<std::vector<uint8_t>>, public Source<std::unique_ptr<File>> {
            public:
                Tarball() noexcept;

            private:
                void consume(const std::vector<uint8_t> &buffer) noexcept;
                void detach() noexcept;
                const std::vector<uint8_t> &quickCopy(const std::vector<uint8_t> &source, std::vector<uint8_t> &tmp, size_t start, size_t length) noexcept;

                uint8_t header[512];
                size_t bytesToFile;
                size_t bytesToSector;
                std::unique_ptr<File> currentFile;
        };
    }
}

#endif
