
find_program(QEMU_ARM NAMES qemu-arm-static qemu-arm DOC "QEMU Arm Executor")
get_filename_component(QEMU_ARM_NAME ${QEMU_ARM} NAME)
file(COPY ${QEMU_ARM} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file(Dockerfile Dockerfile)
configure_file(entrypoint.sh entrypoint.sh)

add_custom_target(docker-image
    COMMAND docker build -t ece643-final --build-arg qemu_target=${QEMU_ARM_NAME}
    --build-arg qemu_target_path=${QEMU_ARM} .
    DEPENDS Dockerfile entrypoint.sh
    COMMENT "Build Docker Image"
    )
