#ifndef ECE643_DOWNLOADER_SOURCE_HPP
#define ECE643_DOWNLOADER_SOURCE_HPP

#include <ece643/downloader/Sink.hpp>

namespace ece643 {
    namespace downloader {
        template <typename Type>
        class Source {
            public:
                Source() noexcept : sink(nullptr) {
                }

                virtual ~Source() noexcept {
                }

                void attach(Sink<Type> &sink) noexcept {
                    this->sink = &sink;
                }

            protected:
                void produce(const Type &obj) noexcept {
                    if (sink) {
                        sink->consume(obj);
                    }
                }

                void finish() noexcept {
                    if (sink) {
                        sink->detach();
                    }
                }

            private:
                Sink<Type> *sink;
        };
    }
}

#endif
