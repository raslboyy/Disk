FROM ubuntu:latest
ARG DEBIAN_FRONTEND=noninteractive
# Install required build dependencies
RUN apt-get -y update && apt-get install -y
RUN apt-get -y install g++ cmake git libboost-dev libboost-program-options-dev libboost-all-dev libblkid-dev e2fslibs-dev libaudit-dev

RUN apt-get update && apt-get -y --no-install-recommends install \
    build-essential \
    clang \
    cmake \
    gdb \
    wget

RUN cd ${HOME} && \
    wget --no-check-certificate --quiet \
        https://boostorg.jfrog.io/artifactory/main/release/1.80.0/source/boost_1_80_0.tar.gz && \
        tar xzf ./boost_1_80_0.tar.gz && \
        cd ./boost_1_80_0 && \
        ./bootstrap.sh && \
        ./b2 install && \
        cd .. && \
        rm -rf ./boost_1_80_0

COPY . /app/src
COPY configs/config.json /app/build/config.json
#RUN rm app/build/backup.json
WORKDIR /app/build
# Run cmake configure & build process
RUN cmake -S ../src -B . -D CMAKE_BUILD_TYPE=Release
RUN cmake --build .
# Launch built application
CMD ["./Disk"]