@echo off
rm -rf ./build && mkdir build && cd build && cmake -G "MinGW Makefiles" .. && make