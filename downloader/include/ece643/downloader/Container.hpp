#ifndef ECE643_DOWNLOADER_CONTAINER_HPP
#define ECE643_DOWNLOADER_CONTAINER_HPP

#include <string>
#include <ece643/downloader/Docker.hpp>

namespace ece643 {
    namespace downloader {
        class Container {
            public:
                Container(Docker &docker, const std::string &image) noexcept;
                ~Container() noexcept;

                Docker &docker() noexcept;
                const std::string &id() const noexcept;

            private:
                Docker &mdocker;
                std::string mid;
        };
    }
}

#endif
