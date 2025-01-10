cmake_minimum_required(VERSION 3.31.3)
project(LLVM_EXAMPLE LANGUAGES C CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Include LLVM directories
include_directories(${LLVM_INCLUDE_DIRS})
add_definitions(${LLVM_DEFINITIONS})

# Source files
set(SOURCE_FILES
    src/main.cpp
)

# Add executable
add_executable(${PROJECT_NAME} ${SOURCE_FILES})

# Link against LLVM libraries
llvm_map_components_to_libnames(LLVM_LIBS core orcjit native)
target_link_libraries(${PROJECT_NAME} ${LLVM_LIBS})
