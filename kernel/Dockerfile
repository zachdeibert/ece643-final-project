FROM debian:buster

RUN apt update && apt install -y \
        bc \
        build-essential \
        curl \
        lib32z1 \
        libstdc++6-i386-cross \
        xz-utils \
    && rm -rf /var/lib/apt/lists/*

RUN curl -L "https://mirrors.edge.kernel.org/pub/linux/kernel/v4.x/linux-4.5.tar.xz" | tar xJC /
RUN curl -L "http://releases.linaro.org/archive/14.04/components/toolchain/binaries/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux.tar.xz" | tar xJC /

COPY ld.so.i686.conf /etc/ld.so.conf.d/
RUN ldconfig

COPY config /linux-4.5/.config
RUN make -C /linux-4.5/ ARCH=arm CROSS_COMPILE=/gcc-linaro-arm-linux-gnueabihf-4.8-2014.04_linux/bin/arm-linux-gnueabihf- olddefconfig modules

RUN find /linux-4.5/ -name "*.ko" -exec cp {} / \;
FROM scratch
ENTRYPOINT "dummy"
COPY --from=0 /*.ko /
