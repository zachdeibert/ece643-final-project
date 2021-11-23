find_package(JNI REQUIRED)

add_library(interop STATIC
    src/JavaException.cpp
    src/JavaState.cpp
)

target_include_directories(interop PUBLIC
    include
    ${JNI_INCLUDE_DIRS}
)

target_link_libraries(interop PUBLIC
    business
    ${JNI_LIBRARIES}
)
