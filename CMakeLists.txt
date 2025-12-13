cmake_minimum_required(VERSION 3.10)
project(convertback)

set(CMAKE_CXX_STANDARD 17)

# Integrate vcpkg (ATTENTION)
set(CMAKE_TOOLCHAIN_FILE C:/cpp/vcpkg/scripts/buildsystems/vcpkg.cmake)

# Find cpp-httplib
find_package(httplib CONFIG REQUIRED)

# Add your executable
add_executable(convertback server.cpp)

# Link libraries
target_link_libraries(convertback PRIVATE httplib::httplib)
