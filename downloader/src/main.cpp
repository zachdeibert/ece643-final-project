#include <stdlib.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/TarFile.hpp>

using namespace ece643::downloader;

int main(int argc, const char **argv) {
    Docker docker;
    docker.connectUnix();
    Image img = TarFile(docker.exportImage("ece643-final"));
    if (!Container::enter()) {
        return EXIT_FAILURE;
    }
    img.extract("/");
    if (!Container::setup()) {
        return EXIT_FAILURE;
    }
    img.config().exec();
    return EXIT_FAILURE;
}
