#include <functional>
#include <pthread.h>
#include <ece643/downloader/Thread.hpp>

using namespace std;
using namespace ece643::downloader;

Thread::Thread(const function<void()> &func) noexcept : func(func) {
    pthread_create(&thread, nullptr, &Thread::start, this);
}

Thread::~Thread() noexcept {
    join();
}

void Thread::join() noexcept {
    pthread_join(thread, nullptr);
}

void *Thread::start(void *arg) noexcept {
    ((Thread *) arg)->func();
    return nullptr;
}
