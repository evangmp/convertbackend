cmake_minimum_required(VERSION 3.10)
project(convertbackend)

set(CMAKE_CXX_STANDARD 17)

# Integrate vcpkg (CAUTION to your path !)
set(CMAKE_TOOLCHAIN_FILE C:/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Find cpp-httplib
find_package(httplib CONFIG REQUIRED)

# Add your executable
add_executable(convertbackend server.cpp)

# Link libraries
target_link_libraries(convertbackend PRIVATE httplib::httplib)