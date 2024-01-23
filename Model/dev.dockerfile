FROM ubuntu:latest

# install mlpack und uwebsockets dev
RUN apt-get update && apt-get install -y \
    g++
	
RUN apt-get update && apt-get install -y \
    cmake \
    git

# install necessary dev dependencies
RUN apt-get update && apt-get install -y \
    libopenblas-dev \
    wget \
    xz-utils \
    gdb doxygen

# mlpack dependency
RUN apt update && \
    apt-get install -y \
    libmlpack-dev \
    libarmadillo-dev

# install uwebsockets dependency
RUN apt-get update && apt-get install -y zlib1g-dev

# install postgres lib
RUN apt-get update && apt-get install -y libpqxx-dev

# Download uWebSockets und uSockets
WORKDIR /installation
RUN wget https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.56.0.tar.gz && \
    tar -xzf v20.56.0.tar.gz && \
    rm v20.56.0.tar.gz && \
    mv uWebSockets-20.56.0 uWebSockets && \
    cd uWebSockets && \
    rm -r uSockets/ && \
    wget https://github.com/uNetworking/uSockets/archive/refs/tags/v0.8.7.tar.gz && \
    tar -xzf v0.8.7.tar.gz && \
    rm v0.8.7.tar.gz && \
    mv uSockets-0.8.7/ uSockets && \
    make install


WORKDIR /installation/uWebSockets
COPY tests/*.cpp .

# MLPACK FLAGS -> -O3 -std=c++17 -larmadillo -lmlpack -fopenmp
# uWebSockets FLAGS -> g++ -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -IuWebSockets/src -IuSockets/src -flto  uSockets/*.o -lz
# postgres flag -> -lpqxx -lpq

RUN make -C uSockets && \
    g++ -march=native -O3 -Wpedantic -Wall -Wextra -Wsign-conversion -Wconversion -std=c++20 -Isrc -IuSockets/src -flto devcontainer_test.cpp uSockets/*.o -lz -lpqxx -lpq -larmadillo -lmlpack -fopenmp -o devcontainer_test

# Set the default command to run when the container starts.
CMD ["/bin/bash"]