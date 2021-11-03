#ifndef ECE643_DOWNLOADER_TARFIFO_HPP
#define ECE643_DOWNLOADER_TARFIFO_HPP

#include <stdint.h>
#include <thread>
#include <ece643/downloader/FIFO.hpp>
#include <ece643/downloader/TarEntryFIFO.hpp>

namespace ece643 {
    namespace downloader {
        class TarFIFO : public FIFO<TarEntryFIFO> {
            public:
                TarFIFO(const FIFO<uint8_t> &input) noexcept;

            private:
                void decode() noexcept;

                FIFO<uint8_t> input;
                std::thread thread;
        };
    }
}

#endif
