#ifndef ECE643_DOWNLOADER_REST_HPP
#define ECE643_DOWNLOADER_REST_HPP

#include <condition_variable>
#include <initializer_list>
#include <functional>
#include <mutex>
#include <queue>
#include <stddef.h>
#include <string>
#include <thread>
#include <utility>
#include <curl/curl.h>

namespace ece643 {
    namespace downloader {
        class Curl {
            public:
                class Option {
                    friend class Curl;

                    public:
                        virtual ~Option() noexcept;

                    private:
                        virtual Option *clone() const noexcept;
                        virtual CURLcode apply(CURL *easy) const noexcept = 0;
                        virtual CURLcode clean(CURL *easy) const noexcept;
                };

                class NoProgress : public Option {
                    public:
                        NoProgress(bool value) noexcept;

                    private:
                        CURLcode apply(CURL *easy) const noexcept;

                        bool value;
                };

                class UnixSocketPath : public Option {
                    public:
                        UnixSocketPath(const std::string &value) noexcept;

                    private:
                        CURLcode apply(CURL *easy) const noexcept;

                        const std::string &value;
                };

                class URL : public Option {
                    public:
                        URL(const std::string &value) noexcept;

                    private:
                        CURLcode apply(CURL *easy) const noexcept;

                        const std::string &value;
                };

                class WriteData : public Option {
                    public:
                        WriteData(void *value) noexcept;

                    private:
                        CURLcode apply(CURL *easy) const noexcept;

                        void *value;
                };

                class WriteFunction : public Option {
                    public:
                        WriteFunction(size_t (*value)(char *ptr, size_t size, size_t nmemb, void *userdata)) noexcept;

                    private:
                        CURLcode apply(CURL *easy) const noexcept;

                        size_t (*value)(char *ptr, size_t size, size_t nmemb, void *userdata);
                };

                class FinishFunction : public Option {
                    public:
                        FinishFunction(const std::function<void()> &func) noexcept;

                    private:
                        Option *clone() const noexcept;
                        CURLcode apply(CURL *easy) const noexcept;
                        CURLcode clean(CURL *easy) const noexcept;

                        std::function<void()> func;
                };

                Curl() noexcept;
                ~Curl() noexcept;

                void start(const std::initializer_list<const Option *> &opts) noexcept;

                template <typename... Args>
                void start(Args &&... args) noexcept {
                    start({ &args... });
                }

            private:
                void run() noexcept;
                void check(const char *str, int code) noexcept;
                void check(const char *str, CURLcode code) noexcept;

                CURLM *multi;
                bool stopping;
                std::condition_variable workerToMain;
                int mainToWorker[2];
                std::mutex mutex;
                std::queue<const std::initializer_list<const Option *> *> reqs;
                std::thread thread;
        };
    }
}

#endif
