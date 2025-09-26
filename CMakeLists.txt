cmake_minimum_required(VERSION 3.10)
project(perception_demo)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

if(CMAKE_COMPILER_IS_GNUCXX OR CMAKE_CXX_compiler_ID MATCHES "Clang")
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

# 'src/US-016' 디렉토리의 라이브러리를 빌드하도록 지시
add_subdirectory(src/US-016)


add_executable(perception_demo src/US-016/main_US016.cpp)


target_link_libraries(perception_demo PRIVATE us016_lib)