add_executable(downloader
    src/downloader.cpp
)

add_executable(uploader
    src/uploader.cpp
)

target_include_directories(downloader PUBLIC
    include
)

target_include_directories(uploader PUBLIC
    include
)

target_link_libraries(downloader PUBLIC
    -static
)
