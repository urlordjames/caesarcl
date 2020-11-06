cmake_minimum_required(VERSION "3.7")

project("caesarcl")

# include OpenCL
find_package(OpenCL REQUIRED)
include_directories(${OpenCL_INCLUDE_DIRS})

# include clhelper
add_subdirectory(clhelper)
include_directories(clhelper/include)

add_executable(${PROJECT_NAME} src/main.cpp)

# link clhelper
target_link_libraries(${PROJECT_NAME} clhelper)

# link OpenCL
target_link_libraries(${PROJECT_NAME} ${OpenCL_LIBRARY})
