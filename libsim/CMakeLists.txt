find_package(JNI REQUIRED)

add_library(sim SHARED
    src/Accelerometer.cpp
    src/FileDescriptor.cpp
    src/HWIO.cpp
    src/I2C.cpp
    src/Interrupt.cpp
    src/IPerformSyscalls.cpp
    src/JavaEnv.cpp
    src/LED.cpp
    src/libsim.cpp
    src/MMap.cpp
    src/PS2.cpp
    src/VGA.cpp
)

target_include_directories(sim PUBLIC
    include
    ${JNI_INCLUDE_DIRS}
)

target_link_libraries(sim PUBLIC
    business
    hwio-headers
    interop
    ${JNI_LIBRARIES}
)
