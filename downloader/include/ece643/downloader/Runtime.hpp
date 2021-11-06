#ifndef ECE643_DOWNLOADER_RUNTIME_HPP
#define ECE643_DOWNLOADER_RUNTIME_HPP

#include <string>
#include <vector>
#include <ece643/downloader/Container.hpp>

namespace ece643 {
    namespace downloader {
        class Runtime {
            public:
                Runtime(Container &container) noexcept;

                void exec() const noexcept;

                static void deleteSelf() noexcept;

            private:
                std::vector<std::string> cmd;
                std::vector<std::string> env;
        };
    }
}

#endif
