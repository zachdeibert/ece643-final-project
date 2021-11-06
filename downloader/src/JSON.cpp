#include <exception>
#include <mutex>
#include <stddef.h>
#include <stdint.h>
#include <vector>
#include <ece643/downloader/JSON.hpp>

using namespace std;
using namespace ece643::downloader;

JSON::JSON() noexcept : mtx(new mutex()), cond(new condition_variable()), done(false), buffer(nullptr) {
}

char JSON::Peek() const noexcept {
    unique_lock<mutex> lck(*mtx);
    while (!done && !buffer) {
        cond->wait(lck);
    }
    if (buffer) {
        return (*buffer)[start];
    }
    return '\0';
}

char JSON::Take() noexcept {
    unique_lock<mutex> lck(*mtx);
    while (!done && !buffer) {
        cond->wait(lck);
    }
    if (buffer) {
        char c = (*buffer)[start];
        if (++start >= buffer->size()) {
            buffer = nullptr;
            cond->notify_all();
        }
        return c;
    }
    return '\0';
}

size_t JSON::Tell() const noexcept {
    unique_lock<mutex> lck(*mtx);
    while (!done && !buffer) {
        cond->wait(lck);
    }
    if (buffer) {
        return buffer->size();
    }
    return 0;
}

char *JSON::PutBegin() noexcept {
    terminate();
    return nullptr;
}

void JSON::Put(char c) noexcept {
    terminate();
}

void JSON::Flush() noexcept {
    terminate();
}

size_t JSON::PutEnd(char *c) noexcept {
    terminate();
    return 0;
}

void JSON::consume(const vector<uint8_t> &buffer) noexcept {
    unique_lock<mutex> lck(*mtx);
    while (this->buffer) {
        cond->wait(lck);
    }
    start = 0;
    this->buffer = &buffer;
    cond->notify_all();
    while (this->buffer) {
        cond->wait(lck);
    }
}

void JSON::detach() noexcept {
    unique_lock<mutex> lck(*mtx);
    done = true;
    cond->notify_all();
}
