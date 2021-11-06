#ifndef ECE643_DOWNLOADER_DOCKER_HPP
#define ECE643_DOWNLOADER_DOCKER_HPP

#include <string>
#include <ece643/downloader/HTTP.hpp>

namespace ece643 {
    namespace downloader {
        class Docker {
            public:
                Docker(const std::string &socket = "") noexcept;

                void run(HTTP &http, const std::string &url, const std::string &method = "GET", const std::string &body = "") noexcept;

            private:
                std::string socket;
        };
    }
}

#endif
