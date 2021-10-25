#include <iostream>
#include <curl/curl.h>
#include <ece643/downloader/Curl.hpp>

using namespace std;
using namespace ece643::downloader;

Curl::CurlOption::CurlOption(Curl &curl, CURLoption opt) : curl(curl), opt(opt) {
}

Curl::Curl() noexcept : curl(curl_easy_init()) {
}

Curl::~Curl() noexcept {
    if (curl) {
        curl_easy_cleanup(curl);
        curl = nullptr;
    }
}

void Curl::reset() noexcept {
    curl_easy_reset(curl);
}

Curl::CurlOption Curl::operator [](CURLoption opt) noexcept {
    return CurlOption(*this, opt);
}

bool Curl::run() noexcept {
    CURLcode res = curl_easy_perform(curl);
    if (res != CURLE_OK) {
        cerr << "curl_easy_perform(): " << res << endl;
        return false;
    }
    return true;
}
