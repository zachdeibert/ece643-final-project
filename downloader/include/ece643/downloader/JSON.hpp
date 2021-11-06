#ifndef ECE643_DOWNLOADER_JSON_HPP
#define ECE643_DOWNLOADER_JSON_HPP

#include <condition_variable>
#include <memory>
#include <mutex>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <ece643/downloader/Sink.hpp>

namespace ece643 {
    namespace downloader {
        class JSON : public Sink<std::vector<uint8_t>> {
            public:
                using Ch = char;

                JSON() noexcept;

                char Peek() const noexcept;
                char Take() noexcept;
                size_t Tell() const noexcept;
                char *PutBegin() noexcept;
                void Put(char c) noexcept;
                void Flush() noexcept;
                size_t PutEnd(char *c) noexcept;

                void consume(const std::vector<uint8_t> &buffer) noexcept;
                void detach() noexcept;

            private:
                std::unique_ptr<std::mutex> mtx;
                std::unique_ptr<std::condition_variable> cond;
                bool done;
                const std::vector<uint8_t> *buffer;
                size_t start;
        };
    }
}

#endif
