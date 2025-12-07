cmake_minimum_required(VERSION 3.10)
project(OpenFlare-Server)

find_package(Boost REQUIRED COMPONENTS system filesystem)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

include_directories(${CMAKE_SOURCE_DIR}/src)

add_executable(openflare-server
    src/main.cpp
    src/configfactory/nginx.cpp
    src/node/config.cpp
)

target_link_libraries(openflare-server Boost::system Boost::filesystem)

set(EXECUTABLE_OUTPUT_PATH ${CMAKE_BINARY_DIR}/bin)