if (CMAKE_SYSTEM_PROCESSOR STREQUAL arm)

    add_executable(hwio-dbg
        src/AccelCommand.cpp
        src/Command.cpp
        src/ExceptionDebugger.cpp
        src/HelpCommand.cpp
        src/IRQCommand.cpp
        src/LEDCommand.cpp
        src/main.cpp
        src/PS2Command.cpp
        src/QuitCommand.cpp
    )

    target_include_directories(hwio-dbg PUBLIC include)
    target_link_libraries(hwio-dbg PUBLIC hwio)

endif()
