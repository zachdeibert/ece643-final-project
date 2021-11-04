add_executable(hwio-dbg
    src/AccelCommand.cpp
    src/Command.cpp
    src/ExceptionDebugger.cpp
    src/HelpCommand.cpp
    src/main.cpp
    src/QuitCommand.cpp
)

target_include_directories(hwio-dbg PUBLIC include)
target_link_libraries(hwio-dbg PUBLIC hwio)
