# 이 디렉토리의 모든 .cpp 파일을 찾음
file(GLOB AJSR04M_SOURCES "*.cpp")

# main 파일을 라이브러리에서 제외
list(REMOVE_ITEM AJSR04M_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_AJ-SR04M.cpp)

# 'ajsr04m_lib' 라이브러리 생성
add_library(ajsr04m_lib ${AJSR04M_SOURCES})

# include 디렉토리 경로 설정
target_include_directories(ajsr04m_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)

#  wiringPi 라이브러리와 연결
target_link_libraries(ajsr04m_lib PUBLIC wiringPi)