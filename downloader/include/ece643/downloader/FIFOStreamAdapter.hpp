#ifndef ECE643_DOWNLOADER_FIFOSTREAMADAPTER_HPP
#define ECE643_DOWNLOADER_FIFOSTREAMADAPTER_HPP

#include <assert.h>
#include <stddef.h>
#include <ece643/downloader/FIFO.hpp>

namespace ece643 {
    namespace downloader {
        template <typename TypeIn, typename TypeOut>
        class FIFOStreamAdapter {
            public:
                using Ch = TypeOut;

                FIFOStreamAdapter(FIFO<TypeIn> &fifo, const TypeOut &eof) noexcept : count(0), fifo(fifo), eof(eof) {
                }

                TypeOut Peek() const {
                    if (fifo.eof()) {
                        return eof;
                    }
                    return (TypeOut) *fifo;
                }

                TypeOut Take() {
                    if (fifo.eof()) {
                        return eof;
                    }
                    ++count;
                    TypeOut val = (TypeOut) *fifo;
                    ++fifo;
                    return val;
                }

                size_t Tell() {
                    return count;
                }

                TypeOut *PutBegin() {
                    assert(false);
                    return nullptr;
                }

                void Put(TypeOut e) {
                    assert(false);
                }

                void Flush() {
                    assert(false);
                }

                size_t PutEnd(TypeOut *e) {
                    assert(false);
                    return 0;
                }

            private:
                size_t count;
                FIFO<TypeIn> &fifo;
                TypeOut eof;
        };
    }
}

#endif
