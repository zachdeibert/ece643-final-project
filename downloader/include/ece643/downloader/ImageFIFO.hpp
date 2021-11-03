#ifndef ECE643_DOWNLOADER_IMAGEFIFO_HPP
#define ECE643_DOWNLOADER_IMAGEFIFO_HPP

#include <condition_variable>
#include <functional>
#include <memory>
#include <mutex>
#include <stdint.h>
#include <ece643/downloader/FIFO.hpp>
#include <ece643/downloader/ImageConfig.hpp>
#include <ece643/downloader/TarFIFO.hpp>

namespace ece643 {
    namespace downloader {
        class ImageFIFO : public FIFO<TarFIFO> {
            public:
                ImageFIFO(const std::function<FIFO<uint8_t>()> &input) noexcept;

                const ImageConfig &config() const noexcept;

            private:
                void decode() noexcept;

                std::function<FIFO<uint8_t>()> input;
                ImageConfig cfg;
                bool cfgValid;
                std::unique_ptr<std::mutex> cfgMutex;
                std::unique_ptr<std::condition_variable> onCfg;
                std::thread thread;
        };
    }
}

#endif
