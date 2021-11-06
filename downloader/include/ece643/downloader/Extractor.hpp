#ifndef ECE643_DOWNLOADER_EXTRACTOR_HPP
#define ECE643_DOWNLOADER_EXTRACTOR_HPP

#include <memory>
#include <stdint.h>
#include <vector>
#include <ece643/downloader/File.hpp>
#include <ece643/downloader/Sink.hpp>

namespace ece643 {
    namespace downloader {
        class Extractor : public Sink<std::unique_ptr<File>> {
            public:
                void consume(const std::unique_ptr<File> &file) noexcept;
                void detach() noexcept;

            private:
                class FileExtractor : public Sink<std::vector<uint8_t>> {
                    public:
                        FileExtractor(int fd) noexcept;

                        void consume(const std::vector<uint8_t> &buffer) noexcept;
                        void detach() noexcept;

                    private:
                        int fd;
                };
        };
    }
}

#endif
