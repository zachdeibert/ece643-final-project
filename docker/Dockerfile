FROM arm32v7/debian:bullseye

COPY @QEMU_ARM_NAME@ @QEMU_ARM@
COPY entrypoint.sh /opt/ece643-final-project/

RUN DEBIAN_FRONTEND="noninteractive" apt-get update -y ;\
    apt-get install -y x11vnc openjdk-17-jre ;\
    rm -rf /var/lib/apt/lists/*

ENTRYPOINT /opt/ece643-final-project/entrypoint.sh
