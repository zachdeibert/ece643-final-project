#include <stdint.h>
#include <string>
#include <vector>
#include <rapidjson/document.h>
#include <ece643/downloader/ImageConfig.hpp>
#include <ece643/downloader/TarEntry.hpp>

using namespace std;
using namespace rapidjson;
using namespace ece643::downloader;

ImageConfig::ImageConfig(const TarEntry &file) noexcept {
    Document doc;
    doc.Parse((const char *) file.data(), file.size());
    Value &config = doc.FindMember("config")->value;
    Value &env = config.FindMember("Env")->value;
    this->env.reserve(env.Size());
    for (Value::ConstValueIterator it = env.Begin(); it != env.End(); ++it) {
        this->env.push_back(it->GetString());
    }
    Value &entry = config.FindMember("Entrypoint")->value;
    this->entry.reserve(entry.Size());
    for (Value::ConstValueIterator it = entry.Begin(); it != entry.End(); ++it) {
        this->entry.push_back(it->GetString());
    }
    Value &cmd = config.FindMember("Cmd")->value;
    this->cmd.reserve(cmd.Size());
    for (Value::ConstValueIterator it = cmd.Begin(); it != cmd.End(); ++it) {
        this->cmd.push_back(it->GetString());
    }
}

const vector<string> &ImageConfig::environment() const noexcept {
    return env;
}

const vector<string> &ImageConfig::entrypoint() const noexcept {
    return entry;
}

const vector<string> &ImageConfig::command() const noexcept {
    return cmd;
}
