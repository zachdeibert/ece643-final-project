find_package(JNI REQUIRED)

add_library(main SHARED
    src/libmain.cpp
)

target_include_directories(main PUBLIC
    ${JNI_INCLUDE_DIRS}
)

target_link_libraries(main PUBLIC
    business
    hwio
    ${JNI_LIBRARIES}
)
