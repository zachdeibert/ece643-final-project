#include <stdlib.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/Extractor.hpp>
#include <ece643/downloader/Filesystem.hpp>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/Runtime.hpp>
#include <ece643/downloader/Tarball.hpp>

using namespace ece643::downloader;

int main(int argc, const char **argv) noexcept {
    Image img;
    Tarball tar;
    img.attach(tar);
    Docker docker;
    Container container(docker, "ece643-final");
    Runtime rt(container);
    Extractor ext;
    Filesystem fs;
    tar.attach(ext);
    img.run(container);
    fs.setup();
    rt.exec();
    return EXIT_FAILURE;
}
