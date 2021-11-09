add_library(interop STATIC
    src/JavaException.cpp
)

target_include_directories(interop PUBLIC include)
