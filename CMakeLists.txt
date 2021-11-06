cmake_minimum_required(VERSION 3.0)
project(ece643-final)

set(CMAKE_BUILD_TYPE Debug)
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wno-psabi")
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

if (NOT CMAKE_SYSTEM_PROCESSOR STREQUAL arm)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
    set(CMAKE_LINKER_FLAGS "${CMAKE_LINKER_FLAGS} -fno-omit-frame-pointer -fsanitize=address")
endif()

add_subdirectory(downloader)
add_subdirectory(docker)
add_subdirectory(hwio-dbg)
add_subdirectory(libbusiness)
add_subdirectory(libmain)
add_subdirectory(libsim)
add_subdirectory(libhwio)

add_custom_target(gradle ALL
    COMMAND ./gradlew "-Dorg.gradle.project.buildDir=${CMAKE_CURRENT_BINARY_DIR}" build
    DEPENDS main sim
    WORKING_DIRECTORY "${CMAKE_CURRENT_SOURCE_DIR}"
    COMMENT "Build Gradle Projects"
    VERBATIM
)
