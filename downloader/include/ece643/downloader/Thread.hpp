#ifndef ECE643_DOWNLOADER_THREAD_HPP
#define ECE643_DOWNLOADER_THREAD_HPP

#include <functional>
#include <pthread.h>

namespace ece643 {
    namespace downloader {
        class Thread {
            public:
                Thread(const std::function<void()> &func) noexcept;
                ~Thread() noexcept;
                void join() noexcept;

            private:
                static void *start(void *arg) noexcept;

                std::function<void()> func;
                pthread_t thread;
        };
    }
}

#endif
