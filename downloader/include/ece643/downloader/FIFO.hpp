#ifndef ECE643_DOWNLOADER_FIFO_HPP
#define ECE643_DOWNLOADER_FIFO_HPP

#include <condition_variable>
#include <iterator>
#include <ios>
#include <memory>
#include <mutex>
#include <queue>
#include <utility>
#include <vector>

namespace ece643 {
    namespace downloader {
        template <typename Type>
        class FIFO : public std::iterator<std::forward_iterator_tag, Type> {
            public:
                class StrongReference {
                    friend class FIFO<Type>;

                    public:
                        Type &operator *() noexcept {
                            return mem->front();
                        }

                        const Type &operator *() const noexcept {
                            return mem->front();
                        }

                        Type *operator ->() noexcept {
                            return &**this;
                        }

                        const Type *operator ->() const noexcept {
                            return &**this;
                        }

                        operator Type &() noexcept {
                            return **this;
                        }

                        operator const Type &() const noexcept {
                            return **this;
                        }

                    private:
                        StrongReference() noexcept {
                        }

                        StrongReference(const std::shared_ptr<std::vector<Type>> &mem) noexcept : mem(mem) {
                        }

                        std::shared_ptr<std::vector<Type>> mem;
                };

                FIFO() noexcept : data(new Data()) {
                }

                bool operator ==(const FIFO &other) noexcept {
                    return data == other.data;
                }

                bool operator !=(const FIFO &other) noexcept {
                    return data != other.data;
                }

                Type &operator *() noexcept {
                    return *operator ->();
                }

                const Type &operator *() const noexcept {
                    return *operator ->();
                }

                Type *operator ->() noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    while (data->blocks.empty() && !data->closed) {
                        data->onWrite.wait(lck);
                    }
                    if (data->blocks.empty()) {
                        return nullptr;
                    }
                    return &*data->currentBlock;
                }

                const Type *operator ->() const noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    while (data->blocks.empty() && !data->closed) {
                        data->onWrite.wait(lck);
                    }
                    if (data->blocks.empty()) {
                        return nullptr;
                    }
                    return &*data->currentBlock;
                }

                FIFO &operator ++() noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    if (data->blocks.empty()) {
                        return *this;
                    }
                    if (++data->currentBlock == data->blocks.front()->end()) {
                        next();
                    }
                    return *this;
                }

                bool eof() const noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    return data->blocks.empty() && data->closed;
                }

                bool empty() const noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    return data->blocks.empty();
                }

                std::streamsize size() const noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    if (data->canceled) {
                        return 0;
                    }
                    typename std::queue<std::shared_ptr<std::vector<Type>>>::const_iterator it = data->blocks.begin();
                    if (it == data->blocks.end()) {
                        return 0;
                    }
                    std::streamsize count = it->end() - data->currentBlock;
                    while (++it != data->blocks.end()) {
                        count += it->size();
                    }
                    return count;
                }

                std::streamsize read(Type *s, std::streamsize min, std::streamsize max) const noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    std::streamsize read = 0;
                    while (read < max) {
                        while (data->blocks.empty()) {
                            if (read >= min || data->closed) {
                                return read;
                            }
                            data->onWrite.wait(lck);
                        }
                        while (read < max && data->currentBlock != data->blocks.front()->end()) {
                            s[read++] = *data->currentBlock++;
                        }
                        if (data->currentBlock == data->blocks.front()->end()) {
                            next();
                        }
                    }
                    return read;
                }

                FIFO &write(const Type *s, std::streamsize n) noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    if (data->canceled) {
                        return *this;
                    }
                    data->blocks.emplace(new std::vector<Type>());
                    data->blocks.back()->reserve(n);
                    if (data->blocks.size() == 1) {
                        data->currentBlock = data->blocks.front()->begin();
                    }
                    for (std::streamsize i = 0; i < n; ++i) {
                        data->blocks.back()->push_back(*s);
                    }
                    data->onWrite.notify_all();
                    return *this;
                }

                template <typename... Args>
                StrongReference emplace(Args &&... args) noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    if (data->canceled) {
                        return StrongReference();
                    }
                    data->blocks.emplace(new std::vector<Type>());
                    data->blocks.back()->reserve(1);
                    if (data->blocks.size() == 1) {
                        data->currentBlock = data->blocks.front()->begin();
                    }
                    data->blocks.back()->emplace_back(std::forward<Args>(args)...);
                    StrongReference ref = data->blocks.back();
                    data->onWrite.notify_all();
                    return ref;
                }

                FIFO &cancel() noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    data->canceled = true;
                    data->blocks = std::queue<std::shared_ptr<std::vector<Type>>>();
                    return *this;
                }

                FIFO &close() noexcept {
                    std::unique_lock<std::mutex> lck(data->mutex);
                    data->closed = true;
                    data->onWrite.notify_all();
                    return *this;
                }

            private:
                class Data {
                    public:
                        Data() : canceled(false), closed(false) {
                        }

                        std::queue<std::shared_ptr<std::vector<Type>>> blocks;
                        typename std::vector<Type>::iterator currentBlock;
                        bool canceled;
                        bool closed;
                        std::mutex mutex;
                        std::condition_variable onWrite;
                };

                void next() const noexcept {
                    data->blocks.pop();
                    if (!data->blocks.empty()) {
                        data->currentBlock = data->blocks.front()->begin();
                    }
                }

                std::shared_ptr<Data> data;
        };
    }
}

#endif
