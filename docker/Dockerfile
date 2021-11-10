FROM --platform=linux/arm/v7 debian:buster

EXPOSE 5900

COPY @QEMU_ARM_NAME@ @QEMU_ARM@
RUN DEBIAN_FRONTEND="noninteractive" apt-get update -y ;\
    apt-get install -y tigervnc-standalone-server openjdk-11-jre mesa-utils ;\
    rm -rf /var/lib/apt/lists/*

ENTRYPOINT /opt/ece643-final-project/bin/main
COPY bin /opt/ece643-final-project/bin
COPY lib /opt/ece643-final-project/lib
