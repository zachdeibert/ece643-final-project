#ifndef ECE643_DOWNLOADER_HTTP_HPP
#define ECE643_DOWNLOADER_HTTP_HPP

#include <stddef.h>
#include <stdint.h>
#include <string>
#include <vector>
#include <ece643/downloader/Source.hpp>

namespace ece643 {
    namespace downloader {
        class HTTP : public virtual Source<std::vector<uint8_t>> {
            public:
                void run(const std::string &socket, const std::string &url, const std::string &method = "GET", const std::string &body = "") noexcept;

            private:
                static size_t writeFunc(char *ptr, size_t size, size_t nmemb, void *userdata) noexcept;
        };
    }
}

#endif
