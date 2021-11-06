
find_program(QEMU_ARM NAMES qemu-arm-static qemu-arm DOC "QEMU Arm Executor")
get_filename_component(QEMU_ARM_NAME ${QEMU_ARM} NAME)
file(COPY ${QEMU_ARM} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file(Dockerfile Dockerfile)
configure_file(entrypoint.sh entrypoint.sh)

add_custom_target(docker-image ALL
    COMMAND docker build -t ece643-final .
    DEPENDS Dockerfile entrypoint.sh
    COMMENT "Build Docker Image"
    )
