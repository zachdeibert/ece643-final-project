#include <algorithm>
#include <errno.h>
#include <functional>
#include <initializer_list>
#include <iostream>
#include <memory>
#include <mutex>
#include <stddef.h>
#include <string.h>
#include <string>
#include <sys/select.h>
#include <sys/time.h>
#include <sys/types.h>
#include <tuple>
#include <unistd.h>
#include <unordered_map>
#include <utility>
#include <vector>
#include <curl/curl.h>
#include <ece643/downloader/Curl.hpp>

using namespace std;
using namespace ece643::downloader;

Curl::Option::~Option() noexcept {
}

Curl::Option *Curl::Option::clone() const noexcept {
    return nullptr;
}

CURLcode Curl::Option::clean(CURL *easy) const noexcept {
    return CURLE_OK;
}

Curl::NoProgress::NoProgress(bool value) noexcept : value(value) {
}

CURLcode Curl::NoProgress::apply(CURL *easy) const noexcept {
    return curl_easy_setopt(easy, CURLOPT_NOPROGRESS, value ? 1L : 0L);
}

Curl::UnixSocketPath::UnixSocketPath(const string &value) noexcept : value(value) {
}

CURLcode Curl::UnixSocketPath::apply(CURL *easy) const noexcept {
    if (value.empty()) {
        return CURLE_OK;
    }
    return curl_easy_setopt(easy, CURLOPT_UNIX_SOCKET_PATH, value.c_str());
}

Curl::URL::URL(const string &value) noexcept : value(value) {
}

CURLcode Curl::URL::apply(CURL *easy) const noexcept {
    return curl_easy_setopt(easy, CURLOPT_URL, value.c_str());
}

Curl::WriteData::WriteData(void *value) noexcept : value(value) {
}

CURLcode Curl::WriteData::apply(CURL *easy) const noexcept {
    return curl_easy_setopt(easy, CURLOPT_WRITEDATA, value);
}

Curl::WriteFunction::WriteFunction(size_t (*value)(char *ptr, size_t size, size_t nmemb, void *userdata)) noexcept : value(value) {
}

CURLcode Curl::WriteFunction::apply(CURL *easy) const noexcept {
    return curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, value);
}

Curl::FinishFunction::FinishFunction(const function<void()> &func) noexcept : func(func) {
}

Curl::Option *Curl::FinishFunction::clone() const noexcept {
    return new FinishFunction(*this);
}

CURLcode Curl::FinishFunction::apply(CURL *easy) const noexcept {
    return CURLE_OK;
}

CURLcode Curl::FinishFunction::clean(CURL *easy) const noexcept {
    func();
    return CURLE_OK;
}

Curl::Curl() noexcept : multi(nullptr), stopping(false), thread(&Curl::run, this) {
    unique_lock<std::mutex> lck(mutex);
    while (!multi) {
        workerToMain.wait(lck);
    }
}

Curl::~Curl() noexcept {
    stopping = true;
    check("write", write(mainToWorker[1], "", 1));
    thread.join();
    check("close", close(mainToWorker[0]));
    check("close", close(mainToWorker[1]));
}

void Curl::start(const initializer_list<const Curl::Option *> &opts) noexcept {
    unique_lock<std::mutex> lck(mutex);
    reqs.push(&opts);
    check("write", write(mainToWorker[1], "", 1));
    while (!reqs.empty()) {
        workerToMain.wait(lck);
    }
}

void Curl::run() noexcept {
    unique_lock<std::mutex> lck(mutex);
    check("pipe", pipe(mainToWorker));
    multi = curl_multi_init();
    workerToMain.notify_all();
    unordered_map<CURL *, vector<unique_ptr<Option>>> handles;
    while (!stopping) {
        while (reqs.empty() && !stopping) {
            lck.unlock();
            int dummy;
            check("curl_multi_perform", curl_multi_perform(multi, &dummy));
            for (CURLMsg *msg; msg = curl_multi_info_read(multi, &dummy); ) {
                if (msg->msg == CURLMSG_DONE) {
                    unordered_map<CURL *, vector<unique_ptr<Option>>>::const_iterator mit = handles.find(msg->easy_handle);
                    if (mit != handles.end()) {
                        for (vector<unique_ptr<Option>>::const_iterator vit = mit->second.begin(); vit != mit->second.end(); ++vit) {
                            (*vit)->clean(mit->first);
                        }
                        check("curl_multi_remove_handle", curl_multi_remove_handle(multi, mit->first));
                        curl_easy_cleanup(mit->first);
                        handles.erase(mit);
                    }
                }
            }
            fd_set readFDs;
            FD_ZERO(&readFDs);
            fd_set writeFDs;
            FD_ZERO(&writeFDs);
            fd_set excFDs;
            FD_ZERO(&excFDs);
            int maxFD = -1;
            FD_SET(mainToWorker[0], &readFDs);
            check("curl_multi_fdset", curl_multi_fdset(multi, &readFDs, &writeFDs, &excFDs, &maxFD));
            long timeoutLong;
            check("curl_multi_timeout", curl_multi_timeout(multi, &timeoutLong));
            struct timeval timeout;
            if (timeoutLong < 0) {
                timeoutLong = 980;
            }
            timeout.tv_sec = timeoutLong / 1000;
            timeout.tv_usec = (timeoutLong % 1000) * 1000;
            check("select", select(max(mainToWorker[0], maxFD) + 1, &readFDs, &writeFDs, &excFDs, &timeout));
            if (FD_ISSET(mainToWorker[0], &readFDs)) {
                char buffer[32];
                check("read", read(mainToWorker[0], buffer, sizeof(buffer)));
            }
            lck.lock();
        }
        while (!reqs.empty()) {
            CURL *easy = curl_easy_init();
            const initializer_list<const Option *> *opts = reqs.front();
            vector<unique_ptr<Option>> &cleanup = handles.emplace(piecewise_construct, make_tuple(easy), make_tuple()).first->second;
            for (initializer_list<const Option *>::const_iterator it = opts->begin(); it != opts->end(); ++it) {
                check("curl_easy_setopt", (*it)->apply(easy));
                unique_ptr<Option> opt((*it)->clone());
                if (opt) {
                    cleanup.emplace_back(move(opt));
                }
            }
            check("curl_multi_add_handle", curl_multi_add_handle(multi, easy));
            reqs.pop();
        }
        workerToMain.notify_all();
    }
    for (unordered_map<CURL *, vector<unique_ptr<Option>>>::const_iterator mit = handles.begin(); mit != handles.end(); ++mit) {
        for (vector<unique_ptr<Option>>::const_iterator vit = mit->second.begin(); vit != mit->second.end(); ++vit) {
            (*vit)->clean(mit->first);
        }
        check("curl_multi_remove_handle", curl_multi_remove_handle(multi, mit->first));
        curl_easy_cleanup(mit->first);
    }
    check("curl_multi_cleanup", curl_multi_cleanup(multi));
}

void Curl::check(const char *str, int code) noexcept {
    if (code < 0) {
        int e = errno;
        cerr << str << ": " << strerror(e) << endl;
    }
}

void Curl::check(const char *str, CURLcode code) noexcept {
    if (code != CURLE_OK) {
        cerr << str << ": " << curl_easy_strerror(code) << endl;
    }
}
