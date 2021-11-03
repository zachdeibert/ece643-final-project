#include <iostream>
#include <memory>
#include <stdlib.h>
#include <ece643/downloader/Container.hpp>
#include <ece643/downloader/Curl.hpp>
#include <ece643/downloader/Docker.hpp>
#include <ece643/downloader/Extractor.hpp>
#include <ece643/downloader/ImageFIFO.hpp>

using namespace std;
using namespace ece643::downloader;

int main(int argc, const char **argv) {
    Docker docker;
    docker.connectTCP();
    unique_ptr<Curl> curl(new Curl());
    /*
    FIFO<uint8_t> fifo = docker.exportImage(*curl, "ece643-final");
    int total = 0;
    while (!fifo.eof()) {
        uint8_t buffer[4096];
        total += fifo.read(buffer, 1, sizeof(buffer));
    }
    cout << "Length = " << total << endl;
    */
    ImageFIFO img([&docker, &curl]() { return docker.exportImage(*curl, "ece643-final"); });
    while (!img.eof()) {
        *img;
        cout << "Got layer" << endl;
    }
    /*
    if (!Container::enter()) {
        return EXIT_FAILURE;
    }
    ImageFIFO img([&docker]() { return docker.exportImage("ece643-final"); });
    Extractor::extract(img, "/");
    if (!Container::setup()) {
        return EXIT_FAILURE;
    }
    img.config().exec();
    */
    return EXIT_FAILURE;
}
