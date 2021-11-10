#include <memory>
#include <stdlib.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/Extractor.hpp>
#include <ece643/downloader/Filesystem.hpp>
#include <ece643/downloader/Image.hpp>
#include <ece643/downloader/Loop.hpp>
#include <ece643/downloader/Runtime.hpp>
#include <ece643/downloader/Tarball.hpp>

using namespace std;
using namespace ece643::downloader;

int main(int argc, const char **argv) noexcept {
    Runtime::deleteSelf();
    unique_ptr<Runtime> rt;
    {
        Image img;
        Tarball tar;
        img.attach(tar);
        Docker docker;
        Container container(docker, "ece643-main");
        rt.reset(new Runtime(container));
        Extractor ext;
        Loop loop("/dev/mmcblk0", 8LL * 1024 * 1024 * 1024);
        loop.format("ext4");
        Filesystem fs("ext4", loop);
        tar.attach(ext);
        img.run(container);
        fs.setup();
    }
    rt->exec();
    return EXIT_FAILURE;
}
