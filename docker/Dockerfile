FROM arm32v7/debian:bullseye

ARG qemu_target
ARG qemu_target_path

COPY $qemu_target $qemu_target_path
COPY entrypoint.sh /opt/ece643-final-project/

RUN DEBIAN_FRONTEND="noninteractive" apt-get update -y ;\
	DEBIAN_FRONTEND="noninteractive" apt-get install -y x11vnc openjdk-17-jre

ENTRYPOINT /opt/ece643-final-project/entrypoint.sh
