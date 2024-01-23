#!/bin/bash
# uWebSockets
wget https://github.com/uNetworking/uWebSockets/archive/refs/tags/v20.56.0.tar.gz # git clone https://github.com/uNetworking/uWebSockets.git
tar -xzf v20.56.0.tar.gz
rm v20.56.0.tar.gz
# error if include does not exists
mv uWebSockets-20.56.0 include/uWebSockets
# uSockets
rm -r include/uWebSockets/uSockets
wget https://github.com/uNetworking/uSockets/archive/refs/tags/v0.8.7.tar.gz # git clone https://github.com/uNetworking/uSockets.git
tar -xzf v0.8.7.tar.gz # -C uSockets
rm v0.8.7.tar.gz
mv uSockets-0.8.7/ include/uWebSockets/uSockets
cp configs/usocket-cmake.txt include/uWebSockets/uSockets/CMakeLists.txt


# add install -clean
# do install check