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
RUN mkdir -p build && \
    cd build && \
    cmake .. -DCMAKE_TOOLCHAIN_FILE=/vcpkg/scripts/buildsystems/vcpkg.cmake && \
    make && \
    ls -l

RUN cmake --build build --target convertbackend --config Debug

# Verify the location of the binary
RUN cd build && \
    ls -l Debug

# Use a minimal base image for the final stage
FROM alpine:latest

# Copy the compiled binary from the builder stage
COPY --from=builder app/build/Debug/convertbackend /usr/local/bin/

# Run the executable by default
CMD ["convertbackend"]