#include <errno.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <unistd.h>
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
    if (env.IsArray()) {
        this->env.reserve(env.Size());
        for (Value::ConstValueIterator it = env.Begin(); it != env.End(); ++it) {
            this->env.push_back(it->GetString());
        }
    }
    Value &entry = config.FindMember("Entrypoint")->value;
    if (entry.IsArray()) {
        this->entry.reserve(entry.Size());
        for (Value::ConstValueIterator it = entry.Begin(); it != entry.End(); ++it) {
            this->entry.push_back(it->GetString());
        }
    }
    Value &cmd = config.FindMember("Cmd")->value;
    if (cmd.IsArray()) {
        this->cmd.reserve(cmd.Size());
        for (Value::ConstValueIterator it = cmd.Begin(); it != cmd.End(); ++it) {
            this->cmd.push_back(it->GetString());
        }
    }
}

void ImageConfig::exec() const noexcept {
    vector<vector<char>> argvb;
    argvb.reserve(entry.size() + cmd.size());
    for (vector<string>::const_iterator it = entry.begin(); it != entry.end(); ++it) {
        argvb.emplace_back(it->begin(), it->end() + 1);
    }
    for (vector<string>::const_iterator it = cmd.begin(); it != cmd.end(); ++it) {
        argvb.emplace_back(it->begin(), it->end() + 1);
    }
    vector<char *> argv;
    argv.reserve(argvb.size() + 1);
    for (vector<vector<char>>::iterator it = argvb.begin(); it != argvb.end(); ++it) {
        argv.push_back(it->data());
    }
    argv.push_back(nullptr);
    vector<vector<char>> envpb;
    envpb.reserve(env.size());
    for (vector<string>::const_iterator it = env.begin(); it != env.end(); ++it) {
        envpb.emplace_back(it->begin(), it->end() + 1);
    }
    vector<char *> envp;
    envp.reserve(envpb.size() + 1);
    for (vector<vector<char>>::iterator it = envpb.begin(); it != envpb.end(); ++it) {
        envp.push_back(it->data());
    }
    envp.push_back(nullptr);
    if (*argv[0] == '/') {
        execvpe(argv[0], argv.data(), envp.data());
        int e = errno;
        cerr << "execvpe: " << strerror(e) << endl;
    } else {
        for (vector<string>::const_iterator it = env.begin(); it != env.end(); ++it) {
            if (it->substr(0, 5) == "PATH=") {
                vector<char> path(it->begin() + 5, it->end() + 1);
                const char *prefix = strtok(path.data(), ":");
                while (prefix) {
                    string file = string(prefix) + "/" + argv[0];
                    execvpe(file.c_str(), argv.data(), envp.data());
                    int e = errno;
                    if (e != ENOENT) {
                        cerr << "execvpe: " << strerror(e) << endl;
                        return;
                    }
                    prefix = strtok(nullptr, ":");
                }
                cerr << "Unable to find executable '" << argv[0] << "' in PATH '" << *it << "'." << endl;
                return;
            }
        }
        cerr << "PATH not set and absolute path to executable not specified." << endl;
    }
}
