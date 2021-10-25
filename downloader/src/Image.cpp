#include <iostream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <unordered_map>
#include <vector>
#include <rapidjson/document.h>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/ImageConfig.hpp>
#include <ece643/downloader/ImageLayer.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace std;
using namespace rapidjson;
using namespace ece643::downloader;

Image::Image(const TarFile &tar) noexcept {
    unordered_map<string, TarEntry *> entries;
    for (TarFile::const_iterator it = tar.begin(); it != tar.end(); ++it) {
        entries[(*it)->filename()] = *it;
    }
    Document doc;
    {
        unordered_map<string, TarEntry *>::const_iterator it = entries.find("manifest.json");
        if (it == entries.end()) {
            cerr << "Failed to find manifest.json in Docker image." << endl;
            return;
        }
        doc.Parse((const char *) it->second->data(), it->second->size());
    }
    Value &root = doc[0];
    {
        unordered_map<string, TarEntry *>::const_iterator it = entries.find(root.FindMember("Config")->value.GetString());
        if (it == entries.end()) {
            cerr << "Failed to find config in Docker image." << endl;
            return;
        }
        cfg = ImageConfig(*it->second);
    }
    Value &layers = root.FindMember("Layers")->value;
    this->layers.reserve(layers.Size());
    for (Value::ConstValueIterator it = layers.Begin(); it != layers.End(); ++it) {
        unordered_map<string, TarEntry *>::const_iterator ent = entries.find(it->GetString());
        if (ent == entries.end()) {
            cerr << "Failed to find layer in Docker image." << endl;
            return;
        }
        this->layers.emplace_back(*ent->second);
    }
}

const ImageConfig &Image::config() const noexcept {
    return cfg;
}

void Image::extract(const string &prefix) const noexcept {
    for (vector<ImageLayer>::const_iterator it = layers.begin(); it != layers.end(); ++it) {
        it->extract(prefix);
    }
}
