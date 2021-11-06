#ifndef ECE643_DOWNLOADER_LOOP_HPP
#define ECE643_DOWNLOADER_LOOP_HPP

#include <stdint.h>
#include <string>

namespace ece643 {
    namespace downloader {
        class Loop {
            public:
                Loop(const std::string &file, uint64_t start = 0, uint64_t length = 0) noexcept;
                ~Loop() noexcept;

                void format(const std::string &type) const noexcept;

                const std::string &path() const noexcept;

            private:
                int fd;
                std::string file;
        };
    }
}

#endif
