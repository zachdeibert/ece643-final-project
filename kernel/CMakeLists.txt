add_custom_target(kernel ALL
    COMMAND docker build -t ece643-kernel "${CMAKE_CURRENT_SOURCE_DIR}"
    DEPENDS Dockerfile config ld.so.i686.conf
    COMMENT "Build Kernel Modules"
)
