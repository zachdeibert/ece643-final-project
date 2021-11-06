find_program(QEMU_ARM NAMES qemu-arm-static qemu-arm DOC "QEMU Arm Executor")
get_filename_component(QEMU_ARM_NAME ${QEMU_ARM} NAME)
file(COPY ${QEMU_ARM} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

configure_file(Dockerfile Dockerfile)
configure_file(.dockerignore .dockerignore)

add_custom_target(docker ALL
    COMMAND ${CMAKE_COMMAND} -E make_directory bin lib
    COMMAND ${CMAKE_COMMAND} -E copy ../main/lib/* lib
    COMMAND ${CMAKE_COMMAND} -E copy ../main/scripts/main bin
    COMMAND docker build -t ece643-final .
    DEPENDS Dockerfile .dockerignore gradle
    COMMENT "Build Docker Image"
)
