
# Specify the minimum CMake version required
cmake_minimum_required(VERSION 3.0)

# Set the project name and version
project(PathTracer VERSION 1.0)

# Specify the C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Add all .c, - files under src/ directory
file(GLOB SOURCES_C "src/*.c")
# Add all .cpp, - files under src/ directory
file(GLOB SOURCES_CPP "src/*.cpp")
# Add all .hpp, - files under src/ directory
file(GLOB SOURCES_HPP "inc/*.hpp")
# Add all .h, - files under src/ directory
file(GLOB SOURCES_H "inc/*.h")

# Add an executable target
add_executable(${PROJECT_NAME} src/main.cpp)

# Optionally, you can specify additional include directories if needed
# target_include_directories(MyApp PUBLIC ${CMAKE_SOURCE_DIR}/include)
include_directories(inc)

# Optionally, you can link external libraries
target_link_libraries(${PROJECT_NAME} PUBLIC 
${CMAKE_SOURCE_DIR}/libs/SFML-2.5.1/lib/libsfml-graphics.so
)
# Optionally, you can set compiler-specific options or flags
# target_compile_options(MyApp PRIVATE -Wall -Wextra)

# Optionally, you can specify additional source files
# add_executable(MyApp main.cpp additional_source.cpp)

# Optionally, you can organize your source files into subdirectories
# add_subdirectory(subdirectory_name)

# Optionally, you can add tests using CTest
# enable_testing()
# add_test(NAME MyTest COMMAND MyApp)
