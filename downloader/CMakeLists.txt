add_executable(downloader
    src/Container.cpp
    src/Curl.cpp
    src/Docker.cpp
    src/Image.cpp
    src/ImageConfig.cpp
    src/ImageLayer.cpp
    src/main.cpp
    src/TarEntry.cpp
    src/TarFile.cpp
)

target_include_directories(downloader PUBLIC
    include
)

find_package(CURL REQUIRED)
find_package(RapidJSON REQUIRED)

target_link_libraries(downloader PUBLIC
    CURL::libcurl
)

configure_file(src/Launch.sh "${CMAKE_BINARY_DIR}/Launch.sh")
configure_file(src/Upload.sh "${CMAKE_BINARY_DIR}/Upload.sh")
