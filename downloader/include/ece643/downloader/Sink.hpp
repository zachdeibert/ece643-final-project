#ifndef ECE643_DOWNLOADER_SINK_HPP
#define ECE643_DOWNLOADER_SINK_HPP

namespace ece643 {
    namespace downloader {
        template <typename Type>
        class Source;

        template <typename Type>
        class Sink {
            friend class Source<Type>;

            public:
                virtual ~Sink() noexcept {
                }

            private:
                virtual void consume(const Type &obj) noexcept = 0;
                virtual void detach() noexcept = 0;
        };
    }
}

#endif
