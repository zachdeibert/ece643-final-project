#include <iostream>
#include <stddef.h>
#include <string.h>
#include <string>
#include <curl/curl.h>
#include <ece643/downloader/HTTP.hpp>

using namespace std;
using namespace ece643::downloader;

static void check(const char *func, CURLcode code) noexcept;

void HTTP::run(const string &socket, const string &url, const string &method, const string &body) noexcept {
    CURL *easy = curl_easy_init();
    if (!socket.empty()) {
        check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_UNIX_SOCKET_PATH, socket.c_str()));
    }
    curl_slist *headers = nullptr;
    if (!body.empty()) {
        headers = curl_slist_append(headers, "Content-Type: application/json");
        check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_POST, 1L));
        check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_POSTFIELDS, body.c_str()));
    }
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_HTTPHEADER, headers));
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_CUSTOMREQUEST, method.c_str()));
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_NOPROGRESS, 0L));
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_WRITEDATA, this));
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_WRITEFUNCTION, &HTTP::writeFunc));
    check("curl_easy_setopt", curl_easy_setopt(easy, CURLOPT_URL, url.c_str()));
    check("curl_easy_perform", curl_easy_perform(easy));
    curl_slist_free_all(headers);
    curl_easy_cleanup(easy);
    finish();
}

size_t HTTP::writeFunc(char *ptr, size_t size, size_t nmemb, void *userdata) noexcept {
    size_t count = size * nmemb;
    HTTP *http = (HTTP *) userdata;
    vector<uint8_t> buffer;
    buffer.resize(count);
    memcpy(buffer.data(), ptr, count);
    http->produce(buffer);
    return count;
}

static void check(const char *func, CURLcode code) noexcept {
    if (code != CURLE_OK) {
        cerr << func << ": " << curl_easy_strerror(code) << endl;
    }
}
