add_executable(downloader
    src/Curl.cpp
    src/Docker.cpp
    src/main.cpp
)

target_include_directories(downloader PUBLIC
    include
)

find_package(CURL REQUIRED)

target_link_libraries(downloader PUBLIC
    CURL::libcurl
)
