# 이 디렉토리의 모든 .cpp 파일을 찾음
file(GLOB SEN0388_SOURCES "*.cpp")

# main 파일을 라이브러리에서 제외
list(REMOVE_ITEM SEN0388_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_SEN0388.cpp)

# 'sen0388_lib' 라이브러리 생성
add_library(sen0388_lib ${SEN0388_SOURCES})

# include 디렉토리 경로 설정
target_include_directories(sen0388_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

# (중요) wiringPi 라이브러리와 연결
target_link_libraries(sen0388_lib PUBLIC wiringPi)