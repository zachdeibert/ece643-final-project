#include <stdlib.h>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace std;
using namespace ece643::downloader;

int main(int argc, const char **argv) {
    Docker docker;
    docker.connectUnix();
    Image img = TarFile(docker.exportImage("ece643-final"));
    img.extract("test/");
    return EXIT_SUCCESS;
}
