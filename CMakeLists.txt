cmake_minimum_required(VERSION 3.10)
project(convertbackend)

set(CMAKE_CXX_STANDARD 17)

# Integrate vcpkg (CAUTION to your path !)
set(CMAKE_TOOLCHAIN_FILE vcpkg/vcpkg/scripts/buildsystems/vcpkg.cmake) # C:/cpp/



# Add your executable
add_executable(convertbackend src/server.cpp)

# Link libraries
# Find cpp-httplib
find_package(httplib CONFIG REQUIRED)
target_link_libraries(convertbackend PRIVATE httplib::httplib)