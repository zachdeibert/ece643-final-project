#ifndef ECE643_DOWNLOADER_CONTAINER_HPP
#define ECE643_DOWNLOADER_CONTAINER_HPP

namespace ece643 {
    namespace downloader {
        class Container {
            public:
                static bool enter() noexcept;
                static bool setup() noexcept;
        };
    }
}

#endif
