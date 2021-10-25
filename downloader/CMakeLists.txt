add_executable(downloader
    src/Curl.cpp
    src/Docker.cpp
    src/main.cpp
    src/TarEntry.cpp
    src/TarFile.cpp
)

target_include_directories(downloader PUBLIC
    include
)

find_package(CURL REQUIRED)

target_link_libraries(downloader PUBLIC
    CURL::libcurl
)
