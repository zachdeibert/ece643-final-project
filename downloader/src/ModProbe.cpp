#include <errno.h>
#include <exception>
#include <fstream>
#include <iostream>
#include <linux/module.h>
#include <memory>
#include <stddef.h>
#include <stdint.h>
#include <string.h>
#include <string>
#include <sys/syscall.h>
#include <unistd.h>
#include <vector>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/File.hpp>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/ModProbe.hpp>
#include <ece643/downloader/Tarball.hpp>

using namespace std;
using namespace ece643::downloader;

ModProbe::ModProbe(Docker &docker) noexcept : docker(docker) {
    ifstream ifs("/proc/modules");
    while (true) {
        string line;
        getline(ifs, line);
        if (line.empty()) {
            break;
        }
        size_t space = line.find_first_of(' ');
        if (space == string::npos) {
            cerr << "Malformed /proc/modules!" << endl;
            terminate();
        }
        loaded.emplace(line.begin(), line.begin() + space);
    }
}

void ModProbe::load(const string &mod) noexcept {
    if (loaded.insert(mod).second) {
        Image img;
        Tarball tar;
        img.attach(tar);
        ModExtractor ext(mod);
        tar.attach(ext);
        Container container(docker, "ece643-kernel");
        img.run(container);
    }
}

ModProbe::ModExtractor::ModExtractor(const string &mod) noexcept : filename(mod + ".ko") {
}

ModProbe::ModExtractor::~ModExtractor() noexcept {
    if (data.empty()) {
        cerr << "Unable to find module '" << filename << "'." << endl;
        terminate();
    } else {
        if (syscall(SYS_init_module, data.data(), data.size(), "") < 0) {
            int e = errno;
            cerr << "init_module: " << strerror(e) << endl;
            terminate();
        }
    }
}

void ModProbe::ModExtractor::consume(const unique_ptr<File> &file) noexcept {
    if (file->filename == filename) {
        file->attach(*this);
    }
}

void ModProbe::ModExtractor::consume(const vector<uint8_t> &part) noexcept {
    size_t off = data.size();
    data.resize(off + part.size());
    memcpy(data.data() + off, part.data(), part.size());
}

void ModProbe::ModExtractor::detach() noexcept {
}
