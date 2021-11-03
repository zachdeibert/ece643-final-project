#ifndef ECE643_DOWNLOADER_DOCKER_HPP
#define ECE643_DOWNLOADER_DOCKER_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <ece643/downloader/Curl.hpp>
#include <ece643/downloader/FIFO.hpp>

namespace ece643 {
    namespace downloader {
        class Docker {
            public:
                void connectUnix(const std::string &socket = "/var/run/docker.sock") noexcept;
                void connectTCP(const std::string &host = "127.0.0.1:2376") noexcept;

                FIFO<uint8_t> exportImage(Curl &curl, const std::string &tagName) noexcept;

            private:
                static size_t writeFunc(char *ptr, size_t size, size_t nmemb, void *userdata) noexcept;

                std::string socket;
                std::string proto;
        };
    }
}

#endif
