FROM gcc:5

RUN apt-get update && apt-get install -y cmake

ADD rivlib-2_5_0-x86_64-linux-gcc55.tgz /
ADD . /rivlib-utils

RUN rm -rf /rivlib-utils/build && \
    mkdir /rivlib-utils/build && \
    cd /rivlib-utils/build && \
    cmake .. -DCMAKE_BUILD_TYPE=Release -DRiVLib_DIR=/rivlib-2_5_0-x86_64-linux-gcc55 && \
    make && \
    make install && \
    rm -rf /rivlib-utils
