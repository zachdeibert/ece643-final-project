#include <string>
#include <thread>
#include <rapidjson/document.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/HTTP.hpp>
#include <ece643/downloader/JSON.hpp>

using namespace std;
using namespace rapidjson;
using namespace ece643::downloader;

Container::Container(Docker &docker, const string &image) noexcept : mdocker(docker) {
    HTTP http;
    JSON json;
    http.attach(json);
    Document doc;
    thread t([&doc, &json]() {
        doc.ParseStream(json);
    });
    docker.run(http, "/containers/create", "POST", "{\"Image\":\"" + image + "\"}");
    t.join();
    mid = doc.FindMember("Id")->value.GetString();
}

Container::~Container() noexcept {
    HTTP http;
    mdocker.run(http, "/containers/" + mid, "DELETE");
}

Docker &Container::docker() noexcept {
    return mdocker;
}

const string &Container::id() const noexcept {
    return mid;
}
