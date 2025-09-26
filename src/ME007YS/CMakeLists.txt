# 이 디렉토리의 모든 .cpp 파일을 찾는다.
file(GLOB ME007YS_SOURCES "*.cpp")

# 라이브러리에 포함되면 안 되는 'main_ME007YS.cpp' 파일을 목록에서 제거한다.
list(REMOVE_ITEM ME007YS_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_ME007YS.cpp)

# 1. 'me007ys_lib' 라는 이름으로 라이브러리를 생성한다.
add_library(me007ys_lib ${ME007YS_SOURCES})

# 2. 이 라이브러리가 프로젝트 최상위의 include 폴더를 사용하도록 설정한다.
#    PUBLIC으로 설정하여, 이 라이브러리를 사용하는 대상에게도 이 include 경로가 필요하다고 알려준다.
target_include_directories(me007ys_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)