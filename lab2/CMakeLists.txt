cmake_minimum_required(VERSION 3.15)
project(CalculatorProject LANGUAGES CXX)

# Set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Optionally enable warnings as errors
add_compile_options(-Wall -Werror)

# Create static library from calculator.cpp
add_library(calculator STATIC calculator.cpp)

# Create executable
add_executable(calc main.cpp)

# Link executable with the library
target_link_libraries(calc PRIVATE calculator)

# Optional: run cppcheck if you want
find_program(CPPCHECK cppcheck)
if(CPPCHECK)
    add_custom_target(check
        COMMAND cppcheck --enable=performance,unusedFunction --error-exitcode=1 ${PROJECT_SOURCE_DIR}/*.cpp
        COMMENT "Running cppcheck..."
    )
endif()

