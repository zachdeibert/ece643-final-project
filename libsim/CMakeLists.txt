find_package(JNI REQUIRED)

add_library(sim SHARED
    src/libsim.cpp
)

target_include_directories(sim PUBLIC
    ${JNI_INCLUDE_DIRS}
)

target_link_libraries(sim PUBLIC
    business
    hwio-headers
    ${JNI_LIBRARIES}
)
