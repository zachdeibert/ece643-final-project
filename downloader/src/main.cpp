#include <iostream>
#include <stdlib.h>
#include <vector>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/TarEntry.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace std;
using namespace ece643::downloader;

int main(int argc, const char **argv) {
    Docker docker;
    docker.connectUnix();
    TarFile tar = docker.exportImage("ece643-final");
    for (vector<TarEntry *>::const_iterator it = tar.begin(); it != tar.end(); ++it) {
        cout << (*it)->filename() << endl;
    }
    return EXIT_SUCCESS;
}
