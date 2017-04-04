FROM debian

ADD rivlib-2_4_0-x86_64-linux-gcc44.tgz /

RUN apt-get update && \
    apt-get install -y \
        build-essential \
        cmake \
        git

RUN git clone --depth=1 https://github.com/gadomski/rivlib-utils && \
    mkdir rivlib-utils/build && \
    cd rivlib-utils/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DRiVLib_DIR=/rivlib-2_4_0-x86_64-linux-gcc44 && \
    make && \
    make install && \
    cd / && \
    rm -rf /rivlib-utils
