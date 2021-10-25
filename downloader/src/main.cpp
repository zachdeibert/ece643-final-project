#include <fstream>
#include <iostream>
#include <stdlib.h>
#include <ece643/downloader/Docker.hpp>

using namespace std;
using namespace ece643::downloader;

int main(int argc, const char **argv) {
    Docker docker;
    docker.connectUnix();
    vector<uint8_t> tar = docker.exportImage("ece643-final");
    ofstream f("test.tar");
    f.write((char *) tar.data(), tar.size());
    return EXIT_SUCCESS;
}
