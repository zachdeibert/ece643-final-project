add_executable(downloader
    src/Container.cpp
    src/Curl.cpp
    src/Docker.cpp
    src/Extractor.cpp
    src/ImageConfig.cpp
    src/ImageFIFO.cpp
    src/main.cpp
    src/TarEntryFIFO.cpp
    src/TarFIFO.cpp
)

target_include_directories(downloader PUBLIC
    include
)

find_package(CURL REQUIRED)
find_package(RapidJSON REQUIRED)
find_package(Threads REQUIRED)

target_link_libraries(downloader PUBLIC
    CURL::libcurl
    Threads::Threads
)

configure_file(src/Launch.sh "${CMAKE_BINARY_DIR}/Launch.sh")
configure_file(src/Upload.sh "${CMAKE_BINARY_DIR}/Upload.sh")
