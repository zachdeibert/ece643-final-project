
find_program(QEMU_ARM NAMES qemu-arm-static qemu-arm DOC "QEMU Arm Executor")
get_filename_component(QEMU_ARM_NAME ${QEMU_ARM} NAME)
file(COPY ${QEMU_ARM} DESTINATION ${CMAKE_CURRENT_BINARY_DIR})

add_custom_command(OUTPUT Dockerfile
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/Dockerfile
	Dockerfile
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/Dockerfile)

add_custom_target(copy-dockerfile DEPENDS Dockerfile)

add_custom_command(OUTPUT entrypoint.sh
	COMMAND ${CMAKE_COMMAND} -E copy ${CMAKE_CURRENT_SOURCE_DIR}/entrypoint.sh
	entrypoint.sh
	DEPENDS ${CMAKE_CURRENT_SOURCE_DIR}/entrypoint.sh)

add_custom_target(copy-entrypoint DEPENDS entrypoint.sh)

add_custom_command(OUTPUT ece643-final.docker
	COMMAND docker build -t ece643-final --build-arg qemu_target=${QEMU_ARM_NAME}
	--build-arg qemu_target_path=${QEMU_ARM} .
	DEPENDS copy-entrypoint copy-dockerfile
	COMMENT "Build Docker Image")
SET_SOURCE_FILES_PROPERTIES(ece643-final.docker PROPERTIES SYMBOLIC TRUE)

add_custom_target(docker-image DEPENDS ece643-final.docker)
