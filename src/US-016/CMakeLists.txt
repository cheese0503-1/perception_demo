
file(GLOB US016_SOURCES "*.cpp")


list(REMOVE_ITEM US016_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/main_US016.cpp)


add_library(us016_lib ${US016_SOURCES})

# 'us016_lib'에 대한 설정
target_include_directories(us016_lib PUBLIC ${CMAKE_SOURCE_DIR}/include)
target_link_libraries(us016_lib PUBLIC wiringPi)