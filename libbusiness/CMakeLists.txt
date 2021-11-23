add_library(business STATIC
    src/Business.cpp
    src/ButtonHandler.cpp
    src/SwitchHandler.cpp
    src/VNCClient.cpp
    src/VNCServer.cpp
)

target_include_directories(business PUBLIC include)

target_link_libraries(business PUBLIC hwio-headers)
