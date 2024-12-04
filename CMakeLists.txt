
cmake_minimum_required(VERSION 3.10)
project(AOC_2024)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED True)

set(TEXT_SOURCE_DIR "${CMAKE_SOURCE_DIR}/data_source")  # Path to your text source folder
set(TEXT_DEST_DIR "${CMAKE_BINARY_DIR}/data_source")

set(CMAKE_CXX_FLAGS_DEBUG "${CMAKE_CXX_FLAGS_DEBUG} -g")
set(CMAKE_C_FLAGS_DEBUG "${CMAKE_C_FLAGS_DEBUG} -g")

# Add the executable
file(GLOB SOURCES "*.cpp")
add_executable(AOC_2024 ${SOURCES})

add_custom_command(
    TARGET ${PROJECT_NAME} POST_BUILD  # Run after the target is built
    COMMAND ${CMAKE_COMMAND} -E copy_directory
            ${TEXT_SOURCE_DIR} ${CMAKE_CURRENT_BINARY_DIR}/${CMAKE_BUILD_TYPE}/data_source
    COMMENT "Copying text source data to build directory: ${CMAKE_CURRENT_BINARY_DIR}"
)