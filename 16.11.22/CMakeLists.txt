cmake_minimum_required(VERSION 3.2)
project(domashkae CXX)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)

set(HEADER_FILES
        z8_0.h
        )

set(SOURCE_FILES
        z8_0.cpp
        main.cpp
        )

add_executable(podroozhki ${SOURCE_FILES} ${HEADER_FILES})
