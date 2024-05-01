FROM ubuntu:latest as build

# this needed in both build and deploy stages
RUN apt-get update && apt install libarmadillo-dev zlib1g-dev -y

# Build stage
RUN apt install libcereal-dev\
    binutils-dev\
    libensmallen-dev\
    wget\
    libmlpack-dev\
    cmake\
    g++ -y

WORKDIR /install
RUN wget https://github.com/mlpack/mlpack/archive/refs/tags/4.3.0.tar.gz &&\
    tar -xzf 4.3.0.tar.gz &&\
    mv mlpack-4.3.0 mlpack && \
    rm -r 4.3.0.tar.gz &&\
    cd mlpack; mkdir build; cd build &&\
    cmake -DDOWNLOAD_DEPENDENCIES=OFF -DBUILD_CLI_EXECUTABLES=OFF .. &&\
    make; make install

WORKDIR /app
COPY ./Model/MLServer/. .

RUN wget https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.56.0.tar.gz && \
    tar -xzf v20.56.0.tar.gz && \
    rm v20.56.0.tar.gz && \
    mv uWebSockets-20.56.0 include/uWebSockets && \
    cd include/uWebSockets && \
    rm -r uSockets/ && \
    wget https://github.com/uNetworking/uSockets/archive/refs/tags/v0.8.7.tar.gz && \
    tar -xzf v0.8.7.tar.gz && \
    rm v0.8.7.tar.gz && \
    mv uSockets-0.8.7/ uSockets && \
    make install && \
    cp ../../configs/usocket-cmake.txt uSockets/CMakeLists.txt

WORKDIR /app
RUN mkdir build && cd build &&\
    cmake -DCMAKE_BUILD_TYPE=Release .. &&\
    make

# Deploy stage
FROM ubuntu:latest as deploy

# this needed in both build and deploy stages
RUN apt-get update && apt-get install libarmadillo-dev zlib1g-dev -y &&\
    rm -rf /var/lib/apt/lists/*


WORKDIR /app
COPY --from=build /app/ .

EXPOSE 3000

ENTRYPOINT [ "/app/out/senti_mlserver" ]