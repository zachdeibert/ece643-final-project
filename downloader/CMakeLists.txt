if (CMAKE_SYSTEM_PROCESSOR STREQUAL arm)

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
        src/ModProbe.cpp
        src/Runtime.cpp
        src/Tarball.cpp
        src/Thread.cpp
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

    configure_file(src/Clean.sh "${CMAKE_BINARY_DIR}/Clean.sh")
    configure_file(src/Upload.sh "${CMAKE_BINARY_DIR}/Upload.sh")

    add_dependencies(downloader docker kernel)

endif()
