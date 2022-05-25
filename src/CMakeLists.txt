cmake_minimum_required(VERSION 3.21)
project(ct)

set(CMAKE_CXX_STANDARD 17)
link_directories(${PROJECT_SOURCE_DIR}/lib)
include_directories(${PROJECT_SOURCE_DIR}/include)
add_executable(ct main.cpp)

target_link_libraries(ct wsock32 ws2_32 wininet  libctdepends libctEditor libctTrans libEncryptor.a libPDiary)

