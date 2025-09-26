# 이 디렉토리의 모든 .cpp 파일을 찾음
file(GLOB US-016_SOURCES "*.cpp")

# main 파일을 라이브러리에서 제외
list(REMOVE_ITEM US-016_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_US-016.cpp)

# 'us016_lib' 라이브러리 생성
add_library(US-016_lib ${US016_SOURCES})

# include 디렉토리 경로 설정
target_include_directories(US-016_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# (중요) SPI 통신을 위해 wiringPi 라이브러리와 연결
target_link_libraries(US-016_lib PUBLIC wiringPi)