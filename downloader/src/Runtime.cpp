#include <errno.h>
#include <iostream>
#include <stdint.h>
#include <string.h>
#include <string>
#include <thread>
#include <unistd.h>
#include <vector>
#include <rapidjson/document.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/HTTP.hpp>
#include <ece643/downloader/JSON.hpp>
#include <ece643/downloader/Runtime.hpp>

using namespace std;
using namespace rapidjson;
using namespace ece643::downloader;

Runtime::Runtime(Container &container) noexcept {
    HTTP http;
    JSON json;
    http.attach(json);
    Document doc;
    thread t([&doc, &json]() {
        doc.ParseStream(json);
    });
    container.docker().run(http, "/containers/" + container.id() + "/json");
    t.join();
    Value &config = doc.FindMember("Config")->value;
    Value &entry = config.FindMember("Entrypoint")->value;
    Value &cmd = config.FindMember("Cmd")->value;
    int size = 0;
    if (entry.IsArray()) {
        size += entry.Size();
    }
    if (cmd.IsArray()) {
        size += cmd.Size();
    }
    this->cmd.reserve(size);
    if (entry.IsArray()) {
        for (Value::ConstValueIterator it = entry.Begin(); it != entry.End(); ++it) {
            this->cmd.push_back(it->GetString());
        }
    }
    if (cmd.IsArray()) {
        for (Value::ConstValueIterator it = cmd.Begin(); it != cmd.End(); ++it) {
            this->cmd.push_back(it->GetString());
        }
    }
    Value &env = config.FindMember("Env")->value;
    if (env.IsArray()) {
        this->env.reserve(env.Size());
        for (Value::ConstValueIterator it = env.Begin(); it != env.End(); ++it) {
            this->env.push_back(it->GetString());
        }
    }
}

void Runtime::exec() const noexcept {
    vector<vector<char>> argvb;
    argvb.reserve(cmd.size());
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
