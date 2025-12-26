# Use a base image with GCC, CMake, and other build tools
FROM gcc:latest AS builder

# Install CMake and other dependencies
RUN apt-get update && \
    apt-get install -y cmake git zip && \
    git clone https://github.com/microsoft/vcpkg.git /vcpkg && \
    /vcpkg/bootstrap-vcpkg.sh && \
    /vcpkg/vcpkg install cpp-httplib && \
    rm -rf /var/lib/apt/lists/*

# Create and set the working directory
WORKDIR /app

# Copy the source code into the container
COPY . .

# Build the project using CMake
RUN rm -rf build && mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    make 

# Use a minimal base image for the final stage (glibc-based)
FROM ubuntu:latest

# Install required libraries
RUN apt-get update && \
    apt-get install -y libstdc++6 libgcc-s1 && \
    rm -rf /var/lib/apt/lists/*

# Copy the compiled binary from the builder stage
COPY --from=builder app/build/convertbackend /usr/local/bin/

# Run the executable by default
CMD ["convertbackend"]