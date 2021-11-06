add_executable(downloader
    src/Container.cpp
    src/Docker.cpp
    src/Extractor.cpp
    src/File.cpp
    src/Filesystem.cpp
    src/HTTP.cpp
    src/Image.cpp
    src/JSON.cpp
    src/Loop.cpp
    src/main.cpp
    src/Runtime.cpp
    src/Tarball.cpp
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
