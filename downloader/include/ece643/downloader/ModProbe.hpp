#ifndef ECE643_DOWNLOADER_MODPROBE_HPP
#define ECE643_DOWNLOADER_MODPROBE_HPP

#include <memory>
#include <stdint.h>
#include <string>
#include <unordered_set>
#include <vector>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/File.hpp>
#include <ece643/downloader/Sink.hpp>

namespace ece643 {
    namespace downloader {
        class ModProbe {
            public:
                ModProbe(Docker &docker) noexcept;

                void load(const std::string &mod) noexcept;

            private:
                class ModExtractor : public Sink<std::unique_ptr<File>>, private Sink<std::vector<uint8_t>> {
                    public:
                        ModExtractor(const std::string &mod) noexcept;
                        ~ModExtractor() noexcept;

                    private:
                        void consume(const std::unique_ptr<File> &file) noexcept;
                        void consume(const std::vector<uint8_t> &part) noexcept;
                        void detach() noexcept;

                        std::string filename;
                        std::vector<uint8_t> data;
                };

                Docker &docker;
                std::unordered_set<std::string> loaded;
        };
    }
}

#endif
