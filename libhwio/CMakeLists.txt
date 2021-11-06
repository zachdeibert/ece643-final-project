add_library(hwio-headers INTERFACE)

target_include_directories(hwio-headers INTERFACE include)

add_library(hwio STATIC
    src/Accelerometer.cpp
    src/FileDescriptor.cpp
    src/HWIO.cpp
    src/I2C.cpp
    src/Interrupt.cpp
    src/IPerformSyscalls.cpp
    src/LED.cpp
    src/MMap.cpp
    src/PS2.cpp
    src/VGA.cpp
)

target_link_libraries(hwio PUBLIC hwio-headers)
