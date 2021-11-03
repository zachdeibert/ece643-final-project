#include <condition_variable>
#include <functional>
#include <iostream>
#include <mutex>
#include <queue>
#include <stdint.h>
#include <string>
#include <rapidjson/document.h>
#include <ece643/downloader/FIFO.hpp>
#include <ece643/downloader/FIFOStreamAdapter.hpp>
#include <ece643/downloader/ImageFIFO.hpp>
#include <ece643/downloader/TarFIFO.hpp>
#include <ece643/downloader/TarEntryFIFO.hpp>

using namespace std;
using namespace rapidjson;
using namespace ece643::downloader;

ImageFIFO::ImageFIFO(const function<FIFO<uint8_t>()> &input) noexcept : input(input), cfgValid(false), cfgMutex(new mutex()), onCfg(new condition_variable()), thread(&ImageFIFO::decode, this) {
}

const ImageConfig &ImageFIFO::config() const noexcept {
    unique_lock<mutex> lck(*cfgMutex);
    while (!cfgValid) {
        onCfg->wait(lck);
    }
    return cfg;
}

void ImageFIFO::decode() noexcept {
    string configFile;
    queue<string> layerFiles;
    while (!cfgValid || !layerFiles.empty()) {
        bool anyUsed = false;
        for (TarFIFO top = input(); !top.eof(); ++top) {
            TarEntryFIFO &entry = *top;
            if (configFile.empty() && entry.filename == "manifest.json") {
                Document doc;
                FIFOStreamAdapter<uint8_t, char> adapter(entry, '\0');
                doc.ParseStream(adapter);
                Value &root = doc[0];
                configFile = root.FindMember("Config")->value.GetString();
                Value &layers = root.FindMember("Layers")->value;
                for (Value::ConstValueIterator it = layers.Begin(); it != layers.End(); ++it) {
                    layerFiles.push(it->GetString());
                }
            } else if (!cfgValid && entry.filename == configFile) {
                cfg = ImageConfig(entry);
                cfgValid = true;
                onCfg->notify_all();
            } else if (entry.filename == layerFiles.front()) {
                layerFiles.pop();
                //emplace(entry);
            } else {
                continue;
            }
            anyUsed = true;
        }
        if (!anyUsed) {
            cerr << "Failed to decode Docker image" << endl;
            break;
        }
    }
    close();
}
