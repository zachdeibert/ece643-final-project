#ifndef ECE643_DOWNLOADER_REST_HPP
#define ECE643_DOWNLOADER_REST_HPP

#include <iostream>
#include <curl/curl.h>

namespace ece643 {
    namespace downloader {
        class Curl {
            public:
                class CurlOption {
                    friend class Curl;

                    public:
                        template <typename Arg>
                        const Arg &operator =(const Arg &arg) {
                            CURLcode res = curl_easy_setopt(curl.curl, opt, arg);
                            if (res != CURLE_OK) {
                                std::cerr << "curl_easy_setopt(" << opt << "): " << res << std::endl;
                            }
                            return arg;
                        }

                    private:
                        CurlOption(Curl &curl, CURLoption opt);

                        Curl &curl;
                        CURLoption opt;
                };

                Curl() noexcept;
                ~Curl() noexcept;

                void reset() noexcept;
                CurlOption operator [](CURLoption opt) noexcept;
                bool run() noexcept;

            private:
                CURL *curl;
        };
    }
}

#endif
